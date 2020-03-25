#include "Advanced.h"


#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include<assert.h>

/* Add noise to an image */
IMAGE *Noise(IMAGE *image, int n)
{
        
        assert(image != NULL);
        unsigned int width = ImageWidth(image);
        unsigned int height = ImageHeight(image);
        int x, y, i;
	int num; /* number of noise added */
	num = ( n*height*width )/100;
	srand(time(NULL));

	for ( i = 0; i < num; i++ ) {
		x = ( (double)rand()/RAND_MAX )*(width-1);
		y = ( (double)rand()/RAND_MAX )*(height-1);
                assert(image->R != NULL);
                assert(image->G != NULL);
                assert(image->B != NULL);
                /* noisy pixels should be white */      
                SetPixelR(image, x, y,255);
                SetPixelG(image, x, y,255);
                SetPixelB(image, x, y,255);
	}
        return(image);
}

/* make the image posterized */
IMAGE *Posterize(IMAGE *image, int rbits, int gbits,int bbits)
{

        assert(image != NULL);
        unsigned int width = ImageWidth(image);
        unsigned int height = ImageHeight(image);
        unsigned char r,g,b; /* temporary variables to store R,G,B values during computation */
	int x, y;
        assert(image->R != NULL);
        assert(image->G != NULL);
        assert(image->B != NULL);

	for(x=0; x<width; x++) {
		for(y=0; y<height; y++) {

                        r = GetPixelR(image, x , y);
                        g = GetPixelG(image, x , y);
                        b = GetPixelB(image, x , y);


			unsigned char one = 1;
			int i;
			for(i=0; i<rbits-1; i++) {
				r |= one;
				one <<= 1;
			}
			one = ~one;
			r &= one;

			one = 1;
			for(i=0; i<gbits-1; i++) {
				g |= one;
				one <<= 1;
			}
			one = ~one;
			g &= one;

			one = 1;
			for(i=0; i<bbits-1; i++) {
				b |= one;
				one <<= 1;
			}
			one = ~one;
			b &= one;

                        SetPixelR(image, x, y,r);
                        SetPixelG(image, x, y,g);
                        SetPixelB(image, x, y,b);

		}
	}
        return(image);
}

/* add motion blur to the image */
IMAGE *MotionBlur(IMAGE *image,int BlurAmount)
{

        assert(image != NULL);
        unsigned int width = ImageWidth(image);
        unsigned int height = ImageHeight(image);
        unsigned char r,g,b;         /* temporary variables to store R,G,B values during computation */
	int x,y,m;
	int temp_r , temp_g , temp_b;
        assert(image->R != NULL);
        assert(image->G != NULL);
        assert(image->B != NULL);

	for (x = 0; x < width; x++)
	{
        	for (y = height - 1; y >= 0 ; y--)
		{
	                r = GetPixelR(image, x , y);
                        g = GetPixelG(image, x , y);
                        b = GetPixelB(image, x , y);

        		int count = 0;
			temp_r = temp_g = temp_b = 0.0;
			for (m = 1; m<=BlurAmount ; m++)
			{
				if((y-m) >= 0)
				{
					temp_r += GetPixelR(image,x,y-m);
					temp_b += GetPixelB(image,x,y-m);
					temp_g += GetPixelG(image,x,y-m);
					count++;
				}
			}
			count = (count==0)?1:count;
			r = temp_r / 2.0 / count + r / 2.0;
			b = temp_b / 2.0 / count + b / 2.0;
			g = temp_g / 2.0 / count + g / 2.0;

                        SetPixelR(image, x, y, r);
                        SetPixelG(image, x, y, g);
                        SetPixelB(image, x, y, b);

		}
	}
        return(image);
		
}

/* enlarge the image */
IMAGE *Enlarge(IMAGE *image, int percentage)
{
        assert(image != NULL);
        unsigned int width = ImageWidth(image);
        unsigned int height = ImageHeight(image);
        unsigned int x,y;
        unsigned char r,g,b;    
        IMAGE *new_image;
        double multiplier = percentage/100.00;
        double factor = 1/multiplier;   /* flipping the formula to find value of old pixel that needs to be used to find new pixel */
        new_image = CreateImage((int)width*multiplier,(int)height*multiplier);
        assert(image->R != NULL);
        assert(image->G != NULL);
        assert(image->B != NULL);
        assert(new_image->R != NULL);
        assert(new_image->G != NULL);
        assert(new_image->B != NULL);
        /* picture returned as it is if percentage = 100 */
        if(percentage == 100)
        {
           return(image);
        }
        else
        { 
           for(x = 0; x < width*multiplier; x++)
           {
              for(y = 0;y < height*multiplier; y++)
              {
                 /* retrieving old pixel's value to determine the value of the new pixel */ 
                 r = GetPixelR(image, (int)(x*factor) ,(int)(y*factor));
                 g = GetPixelG(image, (int)(x*factor) ,(int)(y*factor));
                 b = GetPixelB(image, (int)(x*factor) ,(int)(y*factor));
                 
                 assert(new_image->R != NULL);
                 assert(new_image->G != NULL);
                 assert(new_image->B != NULL);

                 SetPixelR(new_image, x, y, r);
                 SetPixelG(new_image, x, y, g);
                 SetPixelB(new_image, x, y, b);
              }
          }
  
        }
        /* new_image is the enlarged image */
        DeleteImage(image);
        return(new_image);

}


/* square */
IMAGE *Square(IMAGE *image, int x, int y, int L)
{
   assert(image != NULL);
   unsigned int width = ImageWidth(image);
   unsigned int height = ImageHeight(image);
   int i,j, size;
   unsigned char r,g,b;     /* temporary variables to store R,G,B values during computation */
   assert(image->R != NULL);
   assert(image->G != NULL);
   assert(image->B != NULL);
   /* determining cropping amount */
   if(L > width-x )
        {
           size = width-x;
        }
   else if(L > height-y)
        {
           size = height-y;
        }
   else
        {
           size = L;
        }
   IMAGE *new_image = CreateImage(size,size);
   for(i = 0; i < size; i++)
      {
        for(j = 0; j < size; j++)
           {
                 r  = GetPixelR(image, i+x , j+y);
                 g  = GetPixelG(image, i+x , j+y);
                 b  = GetPixelB(image, i+x , j+y);

                 SetPixelR(new_image, i, j, r);
                 SetPixelG(new_image, i, j, g);
                 SetPixelB(new_image, i, j, b);
          
            }
       }
    DeleteImage(image);
    return(new_image);
}       

/* brightness and contrast */
IMAGE *BrightnessAndContrast(IMAGE *image, int brightness, int contrast)
{
       assert(image != NULL);
       unsigned int width = ImageWidth(image);
       unsigned int height = ImageHeight(image); 
       unsigned char r,g,b;       /* temporary variables to store R,G,B values during computation */
       int R,G,B,x,y;    /* R,G,B are temporary variables to store R,G,B values during computation */
       double factor = (double)(259 * (contrast + 255)) / (double)(255 * (259 - contrast));
       assert(image->R != NULL);
       assert(image->G != NULL);
       assert(image->B != NULL);
       for (x = 0; x < width; x++)
        {   for(y = 0; y < height; y++)
            { /* brightness */
              r = GetPixelR(image, x , y) + brightness;
              g = GetPixelG(image, x , y) + brightness;
              b = GetPixelB(image, x , y) + brightness;
              
	      r = (r>255)?255:(r<0)?0:r;
	      g = (g>255)?255:(g<0)?0:g;
              b = (b>255)?255:(b<0)?0:b;
 
              /* contrast */   
              R = (int)(factor*(r-128) + 128);
              G = (int)(factor*(g-128) + 128);
              B = (int)(factor*(b-128) + 128);
            
              /* checking if range of R,G,B values is [0,255] */
              R = (R>255)?255:(R<0)?0:R;
              G = (G>255)?255:(G<0)?0:G;
              B = (B>255)?255:(B<0)?0:B;

              SetPixelR(image, x, y, R);
              SetPixelG(image, x, y, G);
              SetPixelB(image, x, y, B);
            }
        }
              
        return(image);
}     
/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
