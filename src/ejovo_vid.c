#include "ejovo_vid.h"

#define _GNU_SOURCE
#include <stdio.h>

Video *newVideo(int w, int h, int n_frames, int fps) {

    Video *video = (Video *) malloc(sizeof(*video));

    // Need to create an array of Matrix_i* types.
    video->frames = (Matrix_b **) malloc(sizeof(*(video->frames)) * n_frames);
    video->n_frames = n_frames;
    video->width = w;
    video->height = h;
    video->fps = fps;

    return video;
}

Video *fromMP4(const char *filename) {

    int w = ffmpeg_get_w(filename);
    int h = ffmpeg_get_h(filename);
    int n_frames = ffmpeg_get_n_frames(filename);
    int fps = ffmpeg_get_fps(filename);

    // Allocate space for a new video
    // we have only allocated space for an array of frames,
    // but none of the frames have been allocated
    Video *video = newVideo(w, h, n_frames, fps);

    // Now I want to load in a single frame 
    const char format[] = "ffmpeg -i %s -f image2pipe -vcodec rawvideo -pix_fmt gray -loglevel quiet -";

    char command[1000] = {0};

    // allocate space for a buffer
    uint8_t *buffer = (uint8_t *) malloc(w * h * sizeof(*buffer));

    sprintf(command, format, filename);

    FILE *pipein = popen(command, "r");

    // let's just get the first w * h bytes
    fread(buffer, w * h, 1, pipein);

    // Let's load exactly one frame and then maybe print it

    int count = 0;
    int i = 0;

    while(1) {

        video->frames[i] = Matrix_from_b(buffer, h, w);
        count = fread(buffer, 1, w * h, pipein);
        // If we didn't get a frame of video, we're probably at the end
        if (count != w * h) break;
        i++;
    }

    printf("%d frames read\n", i + 1);

    // Matrix_print_b(frame1);

    // Now read the rest of the content or something

    fflush(pipein);
    // pclose(pipein);

    fprintf(stderr, "pipes flushed\n");

    free(buffer);
    printf("'%s' succesfully read\n", filename);

    return video;
}

Video *fromAVI(const char *filename);



Video *takeFrames(const Video *video, int __n) {

    int n = __n < video->n_frames ? __n : video->n_frames;

    Video *out = newVideo(video->width, video->height, n, video->fps);
    for (int i = 0; i < n; i++) {
        out->frames[i] = Matrix_clone_b(video->frames[i]);
    }

    return out;
}

// Take a video object and write it to .mp4 using ffmpeg
// and using a grayscale video
void writeMP4(const Video *video, const char *filename) {

    const char format[] = "ffmpeg -y -f rawvideo -vcodec rawvideo -pix_fmt gray -s %dx%d -r %d -i - -f mp4 -q:v 5 -an -vcodec mpeg4 -loglevel quiet %s";

    char command[1000] = {0};

    sprintf(command, format, video->width, video->height, video->fps, filename);

    FILE *pipeout = popen(command, "w");

    // Now write out the frames 
    for (int i = 0; i < video->n_frames; i++) {
        fwrite(video->frames[i]->data, 1, frameSize(video), pipeout);
    }

    fflush(pipeout);
    pclose(pipeout);
}

Video *filterVideo(const Video *video, uint8_t luminosity) {
    return filterVideo_(cloneVideo(video), luminosity);
}

// filter a video in place
Video *filterVideo_(Video *video, uint8_t luminosity) {
    // Apply the image filter to all of the frames in a video
    for (int i = 0; i < video->n_frames; i++) {
        filterImage_(video->frames[i], luminosity);   
    }
    return video;
}

Video *cloneVideo(const Video *video) {

    Video *out = newVideo(video->width, video->height, video->n_frames, video->fps);

    // Now clone the frame, one by one
    for (int i = 0; i < video->n_frames; i++) {
        out->frames[i] = Matrix_clone_b(video->frames[i]);
    }

    return out;
}

Video *gradientXVideo(const Video *video) {

    Video *out = newVideo(video->width, video->height, video->n_frames, video->fps);

    // now let's create the individual frames

    for (int i = 0; i < video->n_frames; i++) {
        out->frames[i] = gradientX(video->frames[i]);
    }

    return out;
}

Video *gradientYVideo(const Video *video) {

    Video *out = newVideo(video->width, video->height, video->n_frames, video->fps);

    // now let's create the individual frames

    for (int i = 0; i < video->n_frames; i++) {
        out->frames[i] = gradientY(video->frames[i]);
    }

    return out;
}

// Compute the gradient in time of two fra.es
Video *gradientTVideo(const Video *video) {

    Video *out = newVideo(video->width, video->height, video->n_frames - 1, video->fps);

    // now let's create the individual frames

    for (int i = 0; i < video->n_frames - 1; i++) {
        out->frames[i] = gradientT(video->frames[i], video->frames[i + 1]);
    }

    return out;

}

Video *laplacianVideo(const Video *video) {

    Video *out = newVideo(video->width, video->height, video->n_frames, video->fps);

    // now let's create the individual frames

    for (int i = 0; i < video->n_frames; i++) {
        out->frames[i] = laplacian(video->frames[i]);
    }

    return out;
}

Video *hornSchunckVideo(const Video *video, int nb_iter, double alpha) {
    Video *out = newVideo(video->width, video->height, video->n_frames - 1, video->fps);

    for (int i = 0; i < video->n_frames - 1; i++) {
        out->frames[i] = hornSchunckMagnitude(video->frames[i], video->frames[i + 1], nb_iter, alpha);
    }

    return out;
}


// Load a single frame of data starting with 
// All I really need is to convert a stream of bytes into a matrix. 



int ffmpeg_get_w(const char *filename) {

    FILE *fp;
    char path[1035];

    char command[1000] = {0};

    const char format[] = "ffprobe -v error -select_streams v:0 -show_entries stream=width,height -of csv=s=x:p=0 %s | cut -d 'x' -f 1";

    sprintf(command, format, filename);


    /* Open the command for reading. */
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to open pipe\n" );
        exit(1);
    }

    int w = -1;

    /* Read the output a line at a time - output it. */
    while (fgets(path, sizeof(path), fp) != NULL) {
        // fprintf(stderr, "Video width:  %s", path);
        w = atoi(path);
    }

    if (w == -1) {
        fprintf(stderr, "Big problems bucko\n");
        exit(2);
    }
    // Now I have a string containing the integer, and all 
    // I have to do is convert it to a string

    /* close */
    pclose(fp);

    return w;
}

int ffmpeg_get_h(const char *filename) {

    FILE *fp;
    char path[1035];

    char command[1000] = {0};

    const char format[] = "ffprobe -v error -select_streams v:0 -show_entries stream=width,height -of csv=s=x:p=0 %s | cut -d 'x' -f 2";

    sprintf(command, format, filename);


    /* Open the command for reading. */
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to open pipe\n" );
        exit(1);
    }

    int h = -1;

    /* Read the output a line at a time - output it. */
    while (fgets(path, sizeof(path), fp) != NULL) {
        // fprintf(stderr, "Video height: %s", path);
        h = atoi(path);
    }

    if (h == -1) {
        fprintf(stderr, "Big problems bucko\n");
        exit(2);
    }
    // Now I have a string containing the integer, and all 
    // I have to do is convert it to a string

    /* close */
    pclose(fp);

    return h;
}

int ffmpeg_get_fps(const char *filename) {

    const char format[] = "ffprobe -v error -select_streams v -of default=noprint_wrappers=1:nokey=1 -show_entries stream=r_frame_rate %s | cut -d '/' -f 1";

    char command[1000] = {0};
    sprintf(command, format, filename);

    FILE *fp = popen(command, "r");
    char path[1035];

    if (fp == NULL) {
        printf("Failed to open pipe\n" );
        exit(1);
    }

    int fps = -1;

    /* Read the output a line at a time - output it. */
    while (fgets(path, sizeof(path), fp) != NULL) {
        // fprintf(stderr, "Video frames: %s", path);
        fps = atoi(path);
    }

    if (fps == -1) {
        fprintf(stderr, "Big problems bucko\n");
        exit(2);
    }
    // Now I have a string containing the integer, and all 
    // I have to do is convert it to a string

    /* close */
    pclose(fp);

    return fps;

}

int ffmpeg_get_n_frames(const char *filename) {

    const char format[] = "ffprobe -v error -select_streams v:0 -count_packets -show_entries stream=nb_read_packets -of csv=p=0 %s";

    char command[1000] = {0};

    sprintf(command, format, filename);

    FILE *fp = popen(command, "r");
    char path[1035];

    if (fp == NULL) {
        printf("Failed to open pipe\n" );
        exit(1);
    }

    int n_frames = -1;

    /* Read the output a line at a time - output it. */
    while (fgets(path, sizeof(path), fp) != NULL) {
        // fprintf(stderr, "Video frames: %s", path);
        n_frames = atoi(path);
    }

    if (n_frames == -1) {
        fprintf(stderr, "Big problems bucko\n");
        exit(2);
    }
    // Now I have a string containing the integer, and all 
    // I have to do is convert it to a string

    /* close */
    pclose(fp);

    return n_frames;
}

// Let's get some video analysis functions that can compute, for example, the variance of each pixel.
// To compute the variance of every single pixel, first we are going to go ahead and compute a static matrix that contains the average value for each pixel across time.

// get the average value of a pixel across time
Matrix_b *pixelAverages_b(const Video* video) {
    // Initialize a byte matrix to store the average
    Matrix_b *out = Matrix_new_b(video->height, video->width);
    FORIJ(out, int sum = 0;
    ,
        // across t, sum up the pixels)
        for (int t = 0; t < video->n_frames; t++) {
            sum += matat_b(video->frames[t], i, j);
        }

        *matacc_b(out, i, j) = sum / (double) video->n_frames;
        // printf("avg(%d, %d) = %lf, sum = %d\n", i, j, sum / (double) video->n_frames, sum);
    ,
    )

    return out;
}

// Take a single frame and turn it into a video
Video *frameToVideo(const Matrix_b *frame, int fps, double s) {

    Video *out = newVideo(frame->ncols, frame->nrows, fps * s, fps);

    // now just clone the frame n_frames times
    for (int i = 0; i < out->n_frames; i++) {
        out->frames[i] = Matrix_clone_b(frame);
    }

    return out;
}

