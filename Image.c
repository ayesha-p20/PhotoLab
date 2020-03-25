/* Image.c contains definitions of functions for getting and setting pixels */
#include<stdlib.h> /* for free() */
#include<assert.h>
#include "Image.h"
#include<stdio.h>

/* function definitions */

/* Get the R intensity of pixel (x, y) in image */
unsigned char GetPixelR(const IMAGE *image, unsigned int x,  unsigned int y)
{
  assert(image != NULL && image->R != NULL);
  int width = image -> W;
  int height = image -> H;
  assert(0 <= x && x <= width && 0 <= y && y <= height);
  assert(image -> R != NULL);
  return (*((image -> R) + x*(height) + y));
}

/* Get the G intensity of pixel (x, y) in image */
unsigned char GetPixelG(const IMAGE *image, unsigned int x,  unsigned int y)
{
  assert(image != NULL && image -> G != NULL);
  int width = image -> W;
  int height = image -> H;
  assert(0 <= x && x <= width && 0 <= y && y <= height);
  assert(image -> G != NULL);
  return (*((image -> G) + x*(height) + y));
}

/* Get the B intensity of pixel (x, y) in image */
unsigned char GetPixelB(const IMAGE *image, unsigned int x,  unsigned int y)
{
  assert(image != NULL && image ->B != NULL);
  int width = image -> W;
  int height = image -> H;
  assert(0 <= x && x <= width && 0 <= y && y <= height);
  assert(image -> B != NULL);
  return (*((image -> B) + x*(height) + y));
}

/* Set the R intensity of pixel (x, y) in image to r */
void SetPixelR(IMAGE *image, unsigned int x,  unsigned int y, unsigned char r)
{
  assert(image != NULL && image->R != NULL);
  int width = image -> W;
  int height = image -> H;
  assert(0 <= x && x <= width && 0 <= y && y <= height);
/*  assert(image -> R != NULL);  */ 
  *((image -> R) + x*(height) + y) = r;  
}

/* Set the G intensity of pixel (x, y) in image to g */
void SetPixelG(IMAGE *image, unsigned int x,  unsigned int y, unsigned char g)
{
  assert(image != NULL && image -> G != NULL);
  int width = image -> W;
  int height = image -> H;
  assert(0 <= x && x <= width && 0 <= y && y <= height);
  *((image -> G) + x*(height) + y) = g;
}

/* Set the B intensity of pixel (x, y) in image to b */
void SetPixelB(IMAGE *image, unsigned int x,  unsigned int y, unsigned char b)
{
  assert(image != NULL && image ->B != NULL);
  int width = image -> W;
  int height = image -> H;
  assert(0 <= x && x <= width && 0 <= y && y <= height);
  *((image -> B) + x*(height) + y) = b;
}

/* Allocate dynamic memory for the image structure and its R/G/B values */
/* Return the pointer to the image, or NULL in case of error */
IMAGE *CreateImage(unsigned int Width, unsigned int Height)
{
  IMAGE *image;
  image = malloc(sizeof(IMAGE));
  if(!image)
  {
   printf("Out of memory! ");
   return(NULL);
  }
  
  /* initializing struct elements */
  image -> W = Width;
  image -> H = Height;
  image -> R = malloc(sizeof(unsigned char)*Width*Height);
  image -> G = malloc(sizeof(unsigned char)*Width*Height);
  image -> B = malloc(sizeof(unsigned char)*Width*Height);
  
  return(image);
}

/* Free the memory for the R/G/B values and IMAGE structure */
void DeleteImage(IMAGE *image)
{
  assert(image != NULL);
  assert(image -> R != NULL); 
  free(image -> R);
  assert(image -> G != NULL); 
  free(image -> G);
  assert(image -> B != NULL);
  free(image -> B);
  free(image);
  image = NULL;
}

/* Return the image's width in pixels */
unsigned int ImageWidth(const IMAGE *image)
{
  assert(image != NULL);
  return(image -> W);
}

/* Return the image's height in pixels */
unsigned int ImageHeight(const IMAGE *image)
{
  assert(image != NULL);
  return(image -> H);
}
