
#ifndef VISUALCOMPUTING_TP2_HISTOGRAMUTILS_H
#define VISUALCOMPUTING_TP2_HISTOGRAMUTILS_H

#endif //VISUALCOMPUTING_TP2_HISTOGRAMUTILS_H

#include "ioUtils.h"

int *compute_histogram(image_structure_t *img);

image_structure_t * histogram_stretching(image_structure_t *img, int min, int max);
image_structure_t * histogram_equalization(image_structure_t *img, int *histogram, int max);
