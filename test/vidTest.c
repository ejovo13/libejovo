#include "ejovo.h"

int main() {

    const char filename[] = "test.mp4";
    // const char filename[] = "test.avi";
    printf("Trying to query video: \n");
    printf(filename);
    printf("\n");

    ffmpeg_get_w(filename);
    ffmpeg_get_h(filename);
    ffmpeg_get_n_frames(filename);
    printf("FPS: %d\n", ffmpeg_get_fps(filename));

    // test using the uint8_t matrix
    Video *v = fromMP4(filename);
    printVideoInfo(v);

    // let's extract a frame
    const Matrix_b *frame = examineFrame(v, 10);

    writePGM(filterImage(frame, 200), "test_frame_200.pgm");
    writePGM(filterImage(frame, 100), "test_frame_100.pgm");
    writePGM(filterImage(frame, 50), "test_frame_50.pgm");
    writePGM(filterImage(frame, 25), "test_frame_25.pgm");
    
    // What's interesting is this gives me a way to create a video from a single frame, slowly turning "on" the lights

    // writeMP4(v, "test_gray.mp4");
    // writeMP4(filterVideo(v, 100), "test_100.mp4");
    // writeMP4(filterVideo(v, 25), "test_25.mp4");
    // writeMP4(filterVideo(v, 50), "test_50.mp4");
    // writeMP4(filterVideo(v, 30), "test_30.mp4");
    // writeMP4(filterVideo(v, 35), "test_35.mp4");
    // writeMP4(filterVideo(v, 40), "test_40.mp4");
    // writeMP4(filterVideo(v, 45), "test_45.mp4");

    // Let's filter a video with a high luminosity value and then compute 
    // the x gradients

    // Video *vid = filterVideo(v, 35);
    // Video *vid50 = filterVideo(v, 50);
    // Video *vid40 = filterVideo(v, 40);
    Video *vid20 = filterVideo(v, 20);

    // Video *vid_x = gradientXVideo(vid);
    // Video *vid_y = gradientYVideo(vid);

    // writeMP4(vid_x, "vid_x.mp4");
    // writeMP4(vid_y, "vid_y.mp4");

    // writeMP4(gradientXVideo(v), "vid_x_no_filter.mp4");
    // writeMP4(gradientYVideo(v), "vid_y_no_filter.mp4");
    // writeMP4(laplacianVideo(v), "vid_laplace_no_filter.mp4");
    // writeMP4(laplacianVideo(vid), "vid_laplace.mp4");
    // writeMP4(laplacianVideo(vid50), "vid_50_laplace.mp4");
    // writeMP4(laplacianVideo(vid40), "vid_40_laplace.mp4");
    writeMP4(laplacianVideo(vid20), "vid_20_laplace.mp4");

    // writeMP4(v, "v.mp4");

    return 0;
}