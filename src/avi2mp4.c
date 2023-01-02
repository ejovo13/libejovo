/**========================================================================
 * ?                          avi2mp4.c
 * @brief   : Convert an avi to mp4
 * @details : 
 * @author  : Evan Voyles
 * @email   : ejovo13@yahoo.com
 * @date    : 2023-01-02
 *========================================================================**/

#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <err.h>

#include "ejovo.h"


// What arguments do I need for this program?
typedef struct {

    int argc;
    char ** argv;
    char *file_in;
    char *file_out;
    double duration_s;
    double out_fps;
    Video *input;
    Video *output;
    bool should_smooth;
    bool should_filter;

} args_t;


// I need to know 
args_t *new_args(int argc, char **argv) {

    args_t *arg = (args_t *) malloc(sizeof(*arg));

    arg->argc = argc;
    arg->argv = argv;
    arg->file_in = NULL;
    arg->file_out = "out.mp4";
    arg->out_fps = -1;
    arg->duration_s = -1;
    arg->input = NULL;
    arg->output = NULL;
    arg->should_smooth = false;
    arg->should_filter = false;

    return arg;
}


void usage(char ** argv)
{
    printf("%s [OPTIONS]\n\n", argv[0]);
    printf("Options:\n\n");
    printf("--in <file.avi>         .avi file to convert\n");
    printf("--out <out.mp4>         .mp4 output file \n");
    printf("--out-fps <fps>         frames per second of output file \n");
    printf("--out-dur <s>           .mp4 output file \n");
    printf("--smooth                smooth the video to reduce noise\n");
    printf("--filter <value>        filter the input video with the given luminosity\n");
    printf("--hs                    compute horn schunck on the current output video\n");
    printf("\n");
    printf("\n");
    printf("Examples:\n");
    // printf("");
    printf("\n");
    // printf("  %s --small --lmodel 100\n", argv[0]);
    // printf("  %s --med --lmodel 300 --lbin 1000\n", argv[0]);
    // printf("  %s --med --lmodel 500 --lbin 1000 --from 300\n", argv[0]);
    // printf("  %s --hi --lmodel 20 --txt --predict --diff\n", argv[0]);
    // exit(0);
}

enum video_op { 
    filter = 0,
    smooth = 1,
    laplace = 2,
};

// Take an intermediate video and alter it
// Video *applyVideoOp(const Video *video, video_op operation) {

    // switch (operation) {

    // case filter {
        // return filter
    // }



    // }

// }


args_t *process_command_line_options(int argc, char ** argv)
{
    struct option longopts[] = {
        {"in", required_argument, NULL, 'i'},
        {"out", required_argument, NULL, 'o'},
        {"out-fps", required_argument, NULL, 'f'},
        {"out-dur", required_argument, NULL, 'd'},
        {"smooth", no_argument, NULL, 's'},
        {"filter", required_argument, NULL, 'l'},
        {"hs", no_argument, NULL, 'h'},
        {NULL, 0, NULL, 0}
    };

    args_t *args = new_args(argc, argv);

    char ch;
    while ((ch = getopt_long(argc, argv, "", longopts, NULL)) != -1) {
        switch (ch) {

        case 'i':
            args->file_in = optarg;
            // printf("Trying to set file_in: '%s'\n", optarg);
            args->input = fromMP4(args->file_in);
            args->output = args->input;
            break;
        case 'o':
            args->file_out = optarg;
            // printf("Trying to set file_out: '%s'\n", optarg);
            break;
        case 'f':
            args->out_fps = atoi(optarg);
            args->duration_s = args->input->n_frames / args->out_fps;
            break;
        case 'd':
            args->duration_s = atoi(optarg);
            args->out_fps = args->input->n_frames / args->duration_s;
            break;
        case 'h':
            if (args->output == NULL) {
                args->output = hornSchunckVideo(args->input, 10, 0.5);
            } else {
                Video *temp = hornSchunckVideo(args->output, 10, 0.5);
                args->output = temp;
            }
            break;
        case 's':
            args->should_smooth = true;
            // go ahead and smooth it
            if (args->output == NULL) {
                args->output = smoothVideo(args->input);
            } else {
                Video *temp = smoothVideo(args->output);
                args->output = temp;
            }
            break;
        case 'l':
            args->should_filter = true;

            uint8_t filter_value = atoi(optarg);
            if (args->output == NULL) {
                args->output = filterVideo(args->input, filter_value);
            } else {
                Video *temp = filterVideo(args->output, filter_value);
                // free the old video
                args->output = temp;
            }
            break;
        default:
            errx(1, "Unknown option\n");
        }
    }


    /* missing required args? */
    if (args-> file_in == NULL || args->out_fps == -1 || args->duration_s == -1 || args->file_out == NULL) {
        usage(args->argv);
        // free_data_iso(args->data);

        exit(0);
    }

    return args;
}

int main(int argc, char ** argv) {

    args_t *args = process_command_line_options(argc, argv);

    printf("Arguments processed\n");
    printf("File in: %s\n", args->file_in);
    printf("File out: %s\n", args->file_out);
    args->output->fps = args->out_fps;

    writeMP4(args->output, args->file_out);
    // 
    // if (args->should_filter)


    return 0;
}