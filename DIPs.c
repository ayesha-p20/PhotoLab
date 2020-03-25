#include "DIPs.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include<assert.h>

/* Example of DIP */
/* make the picture color black & white */

/* make the picture color black & white */
IMAGE *BlackNWhite(IMAGE *image)
{
    assert(image != NULL);
    unsigned int x, y;
    unsigned int width = ImageWidth(image);
    unsigned int height = ImageHeight(image);
    unsigned char R,G,B, new_value;   /* R,G,B are temporary variables to hold R,G,B values */
    for (x = 0; x < width; x++)
    {   for(y = 0; y < height; y++)
        {  
         R = GetPixelR(image, x , y);
         G = GetPixelG(image, x , y);
         B = GetPixelB(image, x , y);
         assert(image->R != NULL);
         assert(image->G != NULL);
         assert(image->B != NULL);
         new_value = (R+G+B)/3;
         SetPixelR(image, x, y,new_value);
         SetPixelG(image, x, y,new_value);
         SetPixelB(image, x, y,new_value);
        }
    }
    return(image);
}

// Sharpen function
IMAGE *Sharpen(IMAGE *image)
{

    assert(image != NULL);
    unsigned int width = ImageWidth(image);
    unsigned int height = ImageHeight(image);
    unsigned int x, y;
    IMAGE *copy_image = CreateImage(width,height); /* creating a new IMAGE pointer */
    int tmpr = 0, tmpg = 0, tmpb = 0;
    unsigned char r,g,b;          /* temporary variables to hold R,G,B values */
       
    assert(image->R != NULL);
    assert(image->G != NULL);
    assert(image->B != NULL);
 
    for (x = 0; x < width; x++)
    {   for(y = 0; y < height; y++)
        {  
            SetPixelR(copy_image,x,y,GetPixelR(image,x,y));
            SetPixelG(copy_image,x,y,GetPixelG(image,x,y));
            SetPixelB(copy_image,x,y,GetPixelB(image,x,y));

        }
    }

    for (x = 1; x < width - 1; x++)
    {   for (y = 1; y < height - 1; y++)
        { 
            tmpr = 9 * GetPixelR(image,x,y) - GetPixelR(image,x-1,y-1) - GetPixelR(image,x-1,y)- GetPixelR(image,x-1,y+1)- GetPixelR(image,x,y-1) - GetPixelR(image,x,y+1) - GetPixelR (image,x+1,y-1) - GetPixelR(image,x+1,y) - GetPixelR(image,x+1,y+1);
            tmpg = 9 * GetPixelG(image,x,y) - GetPixelG(image,x-1,y-1) - GetPixelG(image,x-1,y) - GetPixelG(image,x-1,y+1) - GetPixelG(image,x,y-1) - GetPixelG(image,x,y+1) - GetPixelG(image,x+1,y-1) - GetPixelG(image,x+1,y) - GetPixelG(image,x+1,y+1);
             tmpb = 9 * GetPixelB(image,x,y) - GetPixelB(image,x-1,y-1) - GetPixelB(image,x-1,y)- GetPixelB(image,x-1,y+1)- GetPixelB(image,x,y-1) - GetPixelB(image,x,y+1) - GetPixelB(image,x+1,y-1) - GetPixelB(image,x+1,y) - GetPixelB(image,x+1,y+1);

            r = (tmpr > 255)?255:(tmpr < 0)?0:tmpr;
            g = (tmpg > 255)?255:(tmpg < 0)?0:tmpg;
            b = (tmpb > 255)?255:(tmpb < 0)?0:tmpb;       


            SetPixelR(copy_image, x, y, r);
            SetPixelG(copy_image, x, y, g);
            SetPixelB(copy_image, x, y, b);

            tmpr = tmpg = tmpb = 0;
        }
    }
    DeleteImage(image);
    return(copy_image);
}


// Hue function
IMAGE *Hue(IMAGE *image, int degree)
{
    assert(image != NULL);
    unsigned int width = ImageWidth(image);
    unsigned int height = ImageHeight(image);
    unsigned int x, y;
    unsigned char R,G,B;   /* temporary variables to hold R,G,B values */

    double a, b, r;
    double d = degree * PI / 180.0;
    double tmp_r, tmp_g, tmp_b;

    a = (2 * cos(d) + 1.0) / 3.0;
    b = (1.0 - cos(d)) / 3.0 - sin(d) / sqrt(3.0);
    r = (1.0 - cos(d)) / 3.0 + sin(d) / sqrt(3.0);

    for (x = 0; x < width; x++)
    {   for (y = 0; y < height; y++)
        {  
            R = GetPixelR(image, x , y);
            G = GetPixelG(image, x , y);
            B = GetPixelB(image, x , y);
 
            assert(image->R != NULL);
            assert(image->G != NULL);
            assert(image->B != NULL);
          
            tmp_r = R * a + G * b + B * r;
            tmp_g = R * r + G * a + B * b;
            tmp_b = R * b + G * r + B * a;

            R = (tmp_r > 255)?255:(tmp_r < 0)?0:tmp_r;
            G = (tmp_g > 255)?255:(tmp_g < 0)?0:tmp_g;
            B = (tmp_b > 255)?255:(tmp_b < 0)?0:tmp_b;

            SetPixelR(image, x, y,R);
            SetPixelG(image, x, y,G);
            SetPixelB(image, x, y,B);

        }
    }
    return(image);
}



/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
