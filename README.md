# Photo Lab
**Photo Lab** was an assignment for a curse I took at college. This program accepts an image as input, applies a filter chosen by the user and displays the output image.
I used pointers and structure to create this program.
The user can select the following filters:
* Black and White <br/>
* Sharpen<br/>
* Hue <br/>
* Noise<br/>
* Posterize<br/>
* Blur <br/>
* Square <br/>
* Brightness and Contrast <br/>
* Enlarge <br/>

Apart from these options, the user can select 'Autotest', a feature that applies all the filters listed above to the original image.

## Built With
This program was made in C on a Linux server. gdb and Valgrind were used to detect errors in the program.

## Usage
The user can select a filter from the menu and provide additional arguments if required. The output can be viewed at https://bondi.eecs.uci.edu/~parveza/
This program also runs in debug mode, in which case it automatically runs Autotest, a function that applies all the filters to the image one by one. 
The following image shows the effect of each filter on an image:
![Alt text](https://github.com/ayesha-p20/MovieLab/blob/master/output.png?raw=true "Output 4")
