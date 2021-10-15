#include "histogramUtils.h"
#include <stdlib.h>

int *compute_histogram(image_structure_t *img)
{
    int *histogram = malloc(256*sizeof(int));
    for(int i=0;i<=255;i++)
    {
        histogram[i] = 0;
    }

    for(int i=0;i<img->rows;i++){
        for(int j=0;j<img->cols;j++){
            histogram[img->image_matrix[i*img->cols+j]]++ ;
        }

    }
    return histogram;

}

//            new_img_matrix[i*img->cols+j] = (char)((int)((int)img->image_matrix[i*img->cols+j]*(255/(max_intensity - min_intensity))));


image_structure_t * histogram_stretching(image_structure_t *img, int min_intensity, int max_intensity){

    image_structure_t *new_image = malloc(sizeof(image_structure_t));
    unsigned char *new_img_matrix = malloc(img->rows*img->cols* sizeof(unsigned char));


    for(int i=0;i<img->rows;i++)
        for(int j=0;j<img->cols;j++)
        {
            new_img_matrix[i*img->cols+j] = (char)((255*((int)img->image_matrix[i*img->cols+j] - min_intensity))/(max_intensity - min_intensity));
                    //Max (i − i1)/(i2 − i1).
        }
    new_image->maxval = 255;
    new_image->cols = img->cols;
    new_image->rows = img->rows;

    new_image->image_matrix = new_img_matrix;

    return new_image;
}


image_structure_t * histogram_equalization(image_structure_t *img, int *histogram, int max)
{
    int cumulative_histogram_sum[256];
    for(int i=0;i<=255;i++)
    {
        if(i==0)
            cumulative_histogram_sum[i] = histogram[i];
        else
            cumulative_histogram_sum[i] = histogram[i] + cumulative_histogram_sum[i-1];
    }


    int slope = (int)(cumulative_histogram_sum[max]/max);
    printf("%d\n", slope);
    image_structure_t *new_image = malloc(sizeof(image_structure_t));
    unsigned char *new_img_matrix = malloc(img->rows*img->cols* sizeof(unsigned char));


    for(int i=0;i<img->rows;i++)
        for(int j=0;j<img->cols;j++)
        {
            new_img_matrix[i*img->cols+j] = (char)((int)(cumulative_histogram_sum[img->image_matrix[i*img->cols+j]]/slope));
        }
    new_image->maxval = 255;
    new_image->cols = img->cols;
    new_image->rows = img->rows;

    new_image->image_matrix = new_img_matrix;

    return new_image;

}

