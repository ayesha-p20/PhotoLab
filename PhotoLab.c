/*********************************************************************/
/* PhotoLab.c: homework assignment #3, for EECS 22,  Fall 2017       */
/*                                                                   */
/* Author: Mina Moghadam                                                */
/* Date:   11/8/2017                                                */
/*                                                                   */
/* Comments: */
/*                                                                   */
/* Please use this template to submit your hw3.                      */
/*********************************************************************/

#include <stdio.h>
#include <string.h>

#include <assert.h>

#include "DIPs.h"
#include "Advanced.h"
#include "FileIO.h"
#include "Constants.h"
#include "Image.h"
#include "Test.h"

/*** function declarations ***/

/* print a menu */
void PrintMenu();

/* Test all functions */
int AutoTest(void);

int main()
{

#ifdef DEBUG
    int check = AutoTest();
    if(check!= 0)
       {
         printf("AutoTest failed, error code %d \n",check);
       }
    else
       {
         printf("AutoTest finished successfully.\n");
       }

#else
    int rc, check_save;
    int option;           /* user input option */
    char fname[SLEN];        /* input file name */
    int prev_option, option_before_previous;

    rc = 1;
    PrintMenu();
    scanf("%d", &option);
    prev_option = 0; /* indicates what the option was selected before current option, initialized with 0 */
    option_before_previous = -1; /* variable to indicate which option was selected before the previous option */
    /* Hue() parameter */
    int hue;

    /* Posterize() parameter */
    unsigned char rbits, gbits, bbits;

    /* Noise() parameter */
    int n;

    /* MotionBlur() parameter */
    int blur_amount;

    /* Enlarge() parameter */
    int enlarge_percentage;

    /* Square() parameters */
    int x_offset, y_offset, crop_size;

    /* BrightnessAndContrast() parameters */
    int b_level, c_level;
    
    while (option != EXIT) 
    {
       IMAGE *image;
        if (option == 1) {
            printf("Please input the file name to load: ");
            scanf("%s", fname);
            image = LoadImage(fname);  
        }

        /* menu item 2 - 11 requires image is loaded first */
        else if (option >= 2 && option < 12) 
        {
            if(prev_option != 1){
               /* printf("No image is read.\n");*/
                 printf("No image to process.\n");
            }
            /* now image is loaded */
            else {
                switch (option) {
                    case 2:
                        printf("Please input the file name to save: ");
                        scanf("%s", fname);
                        check_save = SaveImage(fname,image);
                        if(check_save != 0)
                             printf("\nError: Image not saved!\n ");
                        DeleteImage(image);
                        image = NULL;
                        break;
                    case 3:
                        assert(image != NULL);
                        image = BlackNWhite(image);
                        printf("\"Black amd White\" operation is done!\n");
                        break;
                    case 4:
                        assert(image != NULL);
                        image = Sharpen(image);
                        printf("\"Sharpen\" operation is done!\n");
                        break;
                    case 5:
                        assert(image != NULL);
                        printf("Please input the degree of changing hue: ");
                        scanf("%d", &hue);
                        image = Hue(image, hue);
                        printf("\"Hue\" operatin is done!\n");
                        break;
                    case 6:
                        assert(image != NULL);
                        printf("Please input noise percentage: ");
                        scanf("%d", &n);
                        image = Noise(image,n);
                        printf("\"Noise\" operation is done!\n");
                        break;
                    case 7:
                        assert(image != NULL);
                        printf("Enter the number of posterization bits for R chennel (1 to 8):");
                        scanf("%hhu", &rbits);
                        printf("Enter the number of posterization bits for G chennel (1 to 8):");
                        scanf("%hhu", &gbits);
                        printf("Enter the number of posterization bits for B chennel (1 to 8):");
                        scanf("%hhu", &bbits);
                        image = Posterize(image, rbits, gbits, bbits);
                        printf("\"Posterize\" operation is done!\n");
                        break;
                    case 8:
                        assert(image != NULL);
                        printf("Please input motion blur amount: ");
                        scanf("%d", &blur_amount);
                        image = MotionBlur(image,blur_amount);
                        printf("\"Motion Blur\" operation is done!\n");
                        break;
                    case 9:
                        assert(image != NULL);
                        printf("Please input the enlarging percentage (integer between 100 - 200): ");
                        scanf("%d",&enlarge_percentage);
                        while(enlarge_percentage < 100)
                        {
                            printf("Warning: Percentage doesn't lie in range [100,200]. Please enter a valid percentage: ");
                            scanf("%d",&enlarge_percentage);
                        }
                        image = Enlarge(image,enlarge_percentage);
                        printf("\"Enlarge\" operation is done!\n");
                        break;
                    case 10:
                        assert(image != NULL);
                        printf("Please enter the X offset value: ");
                        scanf("%d",&x_offset);
                        printf("Please enter the Y offset value: ");
                        scanf("%d",&y_offset);
                        printf("Please input the cropped square size: ");
                        scanf("%d",&crop_size);
                        image = Square(image,x_offset,y_offset,crop_size);
                        printf("\"Square\" operation is done!\n");
                        break;
                    case 11:
                        assert(image != NULL);
                        printf("Please input the brightness level (integer between -255 - 255): ");
                        scanf("%d",&b_level);
                        printf("Please input the contrast level (integer between -255 - 255): ");
                        scanf("%d",&c_level);
                        while(b_level > 255 || b_level < -255)
                        {
                            printf("Warning: Brightness doesn't lie in range [-255,255]. Please enter a valid integral value: ");
                            scanf("%d",&b_level);
                        }
                        while(c_level > 255 || c_level < -255)
                        {
                            printf("Warning: Brightness doesn't lie in range [-255,255]. Please enter a valid integral value: ");
                            scanf("%d",&b_level);

                        }
                        image = BrightnessAndContrast(image,b_level, c_level);
                        printf("\"Brightness and Contrast Adjustment\" operation is done!\n");
                        break;
		    default:
                        break;

                }
            } 

        }
        else if (option == 12) {
            rc = AutoTest();
            if(rc!= 0)
            {
              printf("AutoTest failed, error code %d \n",rc);
            }
            else
            {
              printf("AutoTest finished successfully.\n");
            }
        }
        else 
        {
            printf("Invalid selection!\n");
        }

        /* Process finished, waiting for another input */
        PrintMenu();
        /* assign prev_option to option_before_previous and option to prev_option before scanning new option input*/
        option_before_previous = prev_option;
        prev_option = option;
        scanf("%d", &option);
        /* delete image if:
 *         1) previous option was load but current option is not save or dip operation
 *         2) option before previous option was load image and previous option was a dip operation but current option is not save */
        if((prev_option == 1 && (option < 2 || option > 11)) || (option_before_previous == 1 && prev_option > 1 && prev_option < 12 && option != 2))
        {
          DeleteImage(image);
          image = NULL;
        }

    }
    printf("\nYou exit the program.\n");
#endif

    return 0;
}


/*******************************************/
/* Function implementations should go here */
/*******************************************/

/* Menu */
void PrintMenu()
{

    printf("\n-------------------------\n");
    printf("1: Load a PPM image\n");
    printf("2: Save the image in PPM and JPEG format\n");
    printf("3: Change the color image to black and white\n");
    printf("4: Sharpen the image\n");
    printf("5: Change the hue of image\n");
    printf("6: Add Noise to an image\n");
    printf("7: Posterize an image\n");
    printf("8: Add Motion Blur \n");
    printf("9: Enlarge the picture by percentage \n");
    printf("10: Crop a square potion of the image \n");
    printf("11: Adjust the Brightness and Contrast of an image \n");
    printf("12: Test all functions\n");
    printf("13: Exit\n");
    printf("\n-------------------------\n");
    printf("Please make your choice: ");
}

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
