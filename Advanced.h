#ifndef ADVANCED_H_INCLUDED_
#define ADVANCED_H_INCLUDED_

#include "Constants.h"
#include "Image.h"

/* add noise to an image */
IMAGE *Noise(IMAGE *image,int n);

/* posterize the image */
IMAGE *Posterize(IMAGE *image, int rbits, int gbits,int bbits);

/* motion blur */
IMAGE *MotionBlur(IMAGE *image, int BlurAmount);

/* square */
IMAGE *Square(IMAGE *image, int x, int y, int L);

/* enlarge */
IMAGE *Enlarge(IMAGE *image, int percentage);

/* brightness and contrast */
IMAGE *BrightnessAndContrast(IMAGE *image, int brightness, int contrast);


#endif /* ADVANCED_H_INCLUDED_ */


/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
