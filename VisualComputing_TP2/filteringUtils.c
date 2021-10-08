//
// Created by Baciu Ioana on 04.10.2021.
//

//#include "ioUtils.h"
#include "filteringUtils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int get_dot_prod(image_structure_t *img, int *matrix,  int start_i, int start_j, int end_i, int end_j, int pos_i, int pos_j)
{
    int sum = 0;
    int count = 0;
    int weight = 0;
    int val = 0, val_i, val_j;
    for(int i = start_i; i<=end_i;i++){
        for(int j=start_j;j<=end_j;j++)
        {
           if(i<0 || i>img->rows || j<0 || j>img->cols)
           {
                val_i = pos_i - i;
                val_j = pos_j - j;
                val = img->image_matrix[(pos_i+val_i)*img->cols+(pos_j+val_j)];
           }
           else{
               val = (int)img->image_matrix[i*img->cols+j];
           }
            sum+=val*matrix[count];
            weight+=matrix[count];
            count+=1;}
        }
    return (int)sum/weight;

    }
int cmpfunc (const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}

    int get_median_value(image_structure_t *img, int window,  int start_i, int start_j, int end_i, int end_j, int pos_i, int pos_j)
    {
        int values_in_window[window*window];
        int count = 0;
        int val = 0, val_i, val_j;
        for(int i = start_i; i<=end_i;i++){
            for(int j=start_j;j<=end_j;j++)
            {
                if(i<0 || i>img->rows || j<0 || j>img->cols)
                {
                    val_i = pos_i - i;
                    val_j = pos_j - j;
                    val = img->image_matrix[(pos_i+val_i)*img->cols+(pos_j+val_j)];
                }
                else{
                    val = (int)img->image_matrix[i*img->cols+j];
                }
                values_in_window[count++] = val;
                }
        }
        qsort(values_in_window, count, sizeof(int), cmpfunc);
//        printf("got here\n");
        return values_in_window[(int)count/2+1];
    }

image_structure_t *smooth_image_median_filter(image_structure_t *img, int size_of_kernel)
{
    int start_i,start_j, end_i, end_j, pos_i, pos_j;
    image_structure_t *new_image = malloc(sizeof(image_structure_t));
    unsigned char *new_img_matrix = malloc(img->rows*img->cols* sizeof(unsigned char));

    for(int i=0;i<img->rows;i++){
        for(int j=0;j<img->cols;j++){
            pos_i = i;
            pos_j = j;
            start_i = i-(int)size_of_kernel/2;
            end_i= i+(int)size_of_kernel/2;

            start_j = j-(int)size_of_kernel/2;
            end_j= j+(int)size_of_kernel/2;

            new_img_matrix[i*img->cols+j] = (char)get_median_value(img, size_of_kernel, start_i, start_j, end_i, end_j, pos_i, pos_j);

        }
    }

    new_image->maxval = 255;
    new_image->cols = img->cols;
    new_image->rows = img->rows;

    new_image->image_matrix = new_img_matrix;

    return new_image;
}



image_structure_t *smooth_image(image_structure_t *img, int size_of_kernel)
{
    int *kernel;
    int kernel_3[] = {1,2,1,2,4,2,1,2,1};
    int kernel_5[] = {1,4,6,4,1,4,16,24,16,4,6,24,36,24,6,4,16,24,16,4,1,4,6,4,1};
    if(size_of_kernel == 3)
        kernel = kernel_3;
    else
        kernel = kernel_5;
    int start_i,start_j, end_i, end_j, pos_i, pos_j;


    image_structure_t *new_image = malloc(sizeof(image_structure_t));
    unsigned char *new_img_matrix = malloc(img->rows*img->cols* sizeof(unsigned char));


    for(int i=0;i<img->rows;i++){
        for(int j=0;j<img->cols;j++){
           pos_i = i;
           pos_j = j;
           start_i = i-(int)size_of_kernel/2;
           end_i= i+(int)size_of_kernel/2;

           start_j = j-(int)size_of_kernel/2;
           end_j= j+(int)size_of_kernel/2;

           new_img_matrix[i*img->cols+j] = (char)get_dot_prod(img, kernel, start_i, start_j, end_i, end_j, pos_i, pos_j);

        }
    }

    new_image->maxval = 255;
    new_image->cols = img->cols;
    new_image->rows = img->rows;

    new_image->image_matrix = new_img_matrix;

    return new_image;


}

image_structure_t *smooth_image_n_times(image_structure_t *img, int size_of_kernel, int smooth_intensity)
{
    for(int i=0;i<smooth_intensity;i++)
    {
        img = smooth_image(img, size_of_kernel);
    }
    return img;
}

image_structure_t *smooth_image_n_times_median_filter(image_structure_t *img, int window_size, int smooth_intensity)
{
    for(int i=0;i<smooth_intensity;i++)
    {
        img = smooth_image_median_filter(img, window_size);
    }
    return img;
}


