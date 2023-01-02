/**========================================================================
 * ?                          ejovo_vid.h
 * @brief   : Provide functionality to load in mp4 videos as a "video" object
 * @details : 
 * @author  : Evan Voyles
 * @email   : ejovo13@yahoo.com
 * @date    : 2022-12-31
 *========================================================================**/

// We primarily would need two different video types, one just grayscale and another 
// that has three channels.

#ifndef EJOVO_VID_H
#define EJOVO_VID_H

#ifdef __cplusplus
extern "C" {
#endif

#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>

#ifdef __cplusplus
}
#endif

#include "ejovo_matrix_generic.h"
#include "ejovo_color.h"
#include "ejovo_string.h"
#include "ejovo_img.h"

// Now we have access to all the matrix types, but we really only need to work with integers here


// We also know that a video is simply a list of frames.
// We will use ffmpeg to get a pipe of raw pixel data

typedef struct Video {

    Matrix_b** frames;
    int n_frames;
    int width;
    int height;
    int fps;

} Video;

// 
Video *newVideo(int w, int h, int n_frames, int fps);

void writeMP4(const Video *video, const char *filename);

Video *filterVideo(const Video *video, uint8_t luminosity);

// filter a video in place
Video *filterVideo_(Video *video, uint8_t luminosity);

// Apply the x gradient to an entire sequence of images
Video *gradientXVideo(const Video *video);

Video *gradientYVideo(const Video *video);

Video *laplacianVideo(const Video *video);

Video *cloneVideo(const Video *video);

Video *hornSchunckVideo(const Video *video, int nb_iter, double alpha);

Video *smoothVideo(const Video *video);

// Take n frames from a video
Video *takeFrames(const Video *video, int __n);

// Need a function to compute the time difference.
// All we really have to do is subtract the next frame with 
// this frame
Video *gradientTVideo(const Video *video);

Matrix_b *pixelAverages_b(const Video* video);

Video *frameToVideo(const Matrix_b *frame, int fps, double s);

// Compute the number of bytes held by a single frame of this video
static inline int frameSize(const Video* video) {
    return video->width * video->height;
}

static inline void printVideoInfo(const Video* video) {
    printf("%dx%d, %d frames, %d fps\n", video->width, video->height, video->n_frames, video->fps);
}

Video *fromMP4(const char *filename);

// These functions currently only work for .mp4
int ffmpeg_get_w(const char *filename);
int ffmpeg_get_h(const char *filename);
int ffmpeg_get_n_frames(const char *filename);
int ffmpeg_get_fps(const char *filename);


// Return the nth frame from a video, peeking 
// at the frame instead of copying it
static inline const Matrix_b *examineFrame(const Video *video, int n) {
    return video->frames[n];
}

// Convert frames to integer matrices so

// When I perform the subtraction, I can just map the result by dividing by 2 and then adding 255 / 2 = 127.5


#endif // EJOVO_VID_H
