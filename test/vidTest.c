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
    // writeMP4(laplacianVideo(vid20), "vid_20_laplace.mp4");

    // writeMP4(v, "v.mp4");

    char const filename_melee[] = "melee.mp4";

    Video *melee = fromMP4(filename_melee);
    printVideoInfo(melee);

    // writeMP4(filterVideo(melee, 100), "melee_100.mp4");
    // writeMP4(filterVideo(melee, 200), "melee_200.mp4");
    // writeMP4(filterVideo(melee, 150), "melee_150.mp4");

    // test the diff_u8 function

    printf("%u \n", diff_u8(255, 0));
    
    // Video *melee

    // writeMP4(gradientXVideo(melee), "melee_Ix.mp4");
    // writeMP4(gradientYVideo(melee), "melee_Iy.mp4");
    // writeMP4(gradientTVideo(melee), "melee_It.mp4");
    // writeMP4(laplacianVideo(melee), "melee_la.mp4");
    // writeMP4(filterVideo(gradientTVideo(melee), 150), "melee_It_150.mp4");

    // writeMP4(hornSchunckVideo(melee, 20, 0.5), "melee_hs.mp4");

    // printf("Trying to load 'melee_move.mp4'\n");
    // Video *movement = fromMP4("melee_move.mp4");
    // printVideoInfo(movement);
    // writeMP4(filterVideo(movement, 40), "melee_move_40.mp4");

    // writeMP4(hornSchunckVideo(movement, 20, 0.5), "melee_move_hs.mp4");
    // writeMP4(filterVideo(hornSchunckVideo(movement, 20, 0.5), 50), "melee_move_hs_filter.mp4");

    // Video *csgo_bots = fromMP4("csgo_bots.mp4");
    // printVideoInfo(csgo_bots);

    // writeMP4(gradientTVideo(csgo_bots), "csgo_It.mp4");
    // writeMP4(filterVideo(gradientTVideo(csgo_bots), 134), "csgo_It_7.mp4");

    // writeMP4(hornSchunckVideo(csgo_bots, 10, 0.25), "csgo_hs.mp4");
    // writeMP4(filterVideo(hornSchunckVideo(csgo_bots, 10, 0.25), 15), "csgo_hs_15.mp4");
    // writeMP4(laplacianVideo(filterVideo(hornSchunckVideo(csgo_bots, 10, 0.25), 15)), "csgo_la_hs_15.mp4");

    // writeMP4(hornSchunckVideo(v, 10, 0.25), "v_hs.mp4");

    fprintf(stderr, "chess_long.mp4..\n");
    Video *chess_long = fromMP4("chess_long.mp4");
    printVideoInfo(chess_long);

    // // Video *chess_500 = takeFrames(chess_long, 500);
    // Video *chess_500 = fromMP4("chess_500.mp4");

    // writeMP4(hornSchunckVideo(chess_500, 10, 0.3), "chess_500_hs.mp4");
    // writeMP4(chess_500, "chess_500.mp4");

    // Video *chess_arcade = fromMP4("chess_arcade.mp4");
    // Video *chess_400 = takeFrames(chess_arcade, 400);
    // Video *chess_400 = fromMP4("chess_arcade_400.mp4");
    // // writeMP4(chess_400, "chess_arcade_400.mp4");

    // // writeMP4(hornSchunckVideo(chess_400, 30, 0.5), "chess_arcade_hs_a10.mp4");
    // writeMP4(filterVideo(hornSchunckVideo(chess_400, 30, 0.5), 50), "chess_arcade_hs_filter.mp4");

    // writeMP4(laplacianVideo(chess_400), "chess_arcade_la");
    // writeMP4(gradientXVideo(chess_400), "chess_arcade_ix");
    // writeMP4(gradientYVideo(chess_400), "chess_arcade_iy");
    // writeMP4(gradientTVideo(chess_400), "chess_arcade_it");

    // Try and load in an avi file

    /**========================================================================
     *!                           Draco 0
     *========================================================================**/
    // const char draco[] = "draco.avi";

    // printf("fps: %d\n", ffmpeg_get_fps(draco));
    // printf("res: %dx%d\n", ffmpeg_get_w(draco), ffmpeg_get_w(draco));

    // Video *v_draco = fromMP4(draco);
    // v_draco->fps = 30;
    // printVideoInfo(v_draco);

    // writeMP4(v_draco, "draco.mp4");

    // Video *v_draco_200 = filterVideo(v_draco, 200);

    // // now apply horn and shunk to v_draco
    // writeMP4(v_draco_200, "draco_200.mp4"); 

    // writeMP4(hornSchunckVideo(v_draco_200, 20, 0.5), "draco_200_hs.mp4"); 


    /**========================================================================
     *!                           Draco 1
     *========================================================================**/
    Video *draco2 = fromMP4("draco2.avi");
    draco2->fps = 10;
    Video *f100_draco2 = filterVideo(draco2, 100);
    Video *f200_draco2 = filterVideo(draco2, 200);

    // writeMP4(draco2, "draco2.mp4");
    // writeMP4(f100_draco2, "draco2_f100.mp4");
    // writeMP4(f200_draco2, "draco2_f200.mp4");

    // writeMP4(hornSchunckVideo(draco2, 30, 0.5), "draco2_hs.mp4");

    // get the pixel averages of the world video
    writePGM(pixelAverages_b(v), "test_averages.pgm");

    Video *still = frameToVideo(examineFrame(v, 100), 30, 10);
    printVideoInfo(still);

    writePGM(pixelAverages_b(still), "v_f100_avg.pgm");

    // writeMP4(frameToVideo(examineFrame(v, 100), 30, 5), "v_f100.mp4");
    writeMP4(still, "v_f100.mp4");

    /**========================================================================
     *!                           Draco 3 this one is crazy
     *========================================================================**/
    Video *draco3 = fromMP4("draco3.avi");
    // I have to remember to set the framerate really slow for .avi
    draco3->fps = 20;

    Video *draco3_f220 = filterVideo(draco3, 220); 
    draco3_f220->fps = 10;
    // writeMP4(filterVideo(draco3, 220), "draco3_f220.mp4");
    writeMP4(filterVideo(draco3, 230), "draco3_f230.mp4");
    // writeMP4(filterVideo(draco3, 200), "draco3_f200.mp4");
    // writeMP4(hornSchunckVideo(draco3_f220, 10, 0.5), "draco3_220_hs.mp4");

    Video *draco3_f220_smooth = smoothVideo(filterVideo(draco3, 230));
    Video *draco3_f220_smooth_f200 = filterVideo(draco3_f220_smooth, 200);
    // I want to transform draco3_f230 and remove the noise by using local averages
    writeMP4(smoothVideo(filterVideo(draco3, 230)), "draco3_f230_smooth.mp4");
    writeMP4(filterVideo(smoothVideo(filterVideo(draco3, 230)), 200), "draco3_f230_smooth_f200.mp4");

    // Now let's perform horn schunck on draco3_f220_smooth_f200;
    // writeMP4(filterVideo(hornSchunckVideo(draco3_f220_smooth_f200, 50, 0.05), 50), "draco3_mod_hs.mp4");

    // nice smooth capture of things that have a higher magnitude than 50 
    Video *d3_hs_smooth = filterVideo(hornSchunckVideo(draco3_f220_smooth_f200, 50, 0.05), 50);

    writePGM(pixelAverages_b(d3_hs_smooth), "draco3_smooth_avg.pgm");




    return 0;
}