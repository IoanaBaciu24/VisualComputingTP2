//
// Created by Baciu Ioana on 04.10.2021.
//
#include <stdlib.h>
#include <stdio.h>
#include "ioUtils.h"
#include "filteringUtils.h"

int main(int argc, char *argv[])
{
    FILE *input_file_descriptor;
    char *file1 = "/Users/yone/Downloads/boat_noise1.pgm";
    char *file2 = "/Users/yone/Documents/VisualComputing_TP2/test.pgm";

    input_file_descriptor = fopen(file1,"r");
    if (input_file_descriptor == NULL) {
        printf("error in opening file %s\n", argv[1]);
        exit(1);
    }

    image_structure_t *img = read_image(input_file_descriptor);
    image_structure_t *new_img = smooth_image(img, 3);

    for(int i=0;i<10;i++)
    {
        new_img = smooth_image(new_img, 3);
    }
    write_image_to_file(new_img,file2);


}

