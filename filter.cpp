/******************************************************************************
 * CS 103 Filter PA
 * Name: Hope Kim
 * USC email: hopekim@usc.edu
 * Comments (you want us to know):
 *
 * For this program, we will be applying various filters such as sobel, blur,
 * and unsharp to images. It uses command line arguments in order to take an
 * input file and different variables to apply the filters and write to an
 * output file with the final images.
******************************************************************************/

#include <iostream>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <cstdlib>
#include "bmplib.h"

using namespace std;

//============================Add function prototypes here======================
void dummy(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB]);
void convolve(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB], 
        int N, double kernel[][11]);
void sobel(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB]);
void gaussian(double k[][11], int N, double sigma);
void gaussian_filter(unsigned char output [][SIZE][3], 
                     unsigned char input[][SIZE][3], int N, double sigma);
void unsharp(unsigned char output[][SIZE][3], unsigned char input[][SIZE][3], 
             int N, double sigma, double alpha);

//============================Do not change code in main()======================

#ifndef AUTOTEST

int main(int argc, char* argv[])
{
   //First check argc
  if(argc < 3)
    {
      //we need at least ./filter <input file> <filter name> to continue
      cout << "usage: ./filter <input file> <filter name> <filter parameters>";
      cout << " <output file name>" << endl;
      return -1;
    }
   //then check to see if we can open the input file
   unsigned char input[SIZE][SIZE][RGB];
   unsigned char output[SIZE][SIZE][RGB];
   char* outfile;
   int N;
   double sigma, alpha;
   //double kernel[11][11];

   // read file contents into input array
   int status = readRGBBMP(argv[1], input); 
   if(status != 0)
   {
      cout << "unable to open " << argv[1] << " for input." << endl;
      return -1;
   }
   //Input file is good, now look at next argument
   if( strcmp("sobel", argv[2]) == 0)
   {
     sobel(output, input);
     outfile = argv[3];
   }
   else if( strcmp("blur", argv[2]) == 0)
   {
     if(argc < 6)
       {
	 cout << "not enough arguments for blur." << endl;
	 return -1;
       }
     N = atoi(argv[3]);
     sigma = atof(argv[4]);
     outfile = argv[5];
     gaussian_filter(output, input, N, sigma);
   }
   else if( strcmp("unsharp", argv[2]) == 0)
   {
     if(argc < 7)
       {
	 cout << "not enough arguments for unsharp." << endl;
	 return -1;
       }
     N = atoi(argv[3]);
     sigma = atof(argv[4]);
     alpha = atof(argv[5]);
     outfile = argv[6];
     unsharp(output, input, N, sigma, alpha);

   }
   else if( strcmp("dummy", argv[2]) == 0)
   {
     //do dummy
     dummy(output, input);
     outfile = argv[3];
     for(int i = 0; i < SIZE; i++){
      for(int j=0; j<SIZE; j++){
         for(int c= 0; c < 3; c++){
            if(input[i][j][c] != output[i][j][c]){
               cout << "failed";
            }
         }
      } //this is just to check if convolve is working for dummy
     }
   }
   else
   {
      cout << "unknown filter type." << endl;
      return -1;
   }
   if(writeRGBBMP(outfile, output) != 0)
   {
      cout << "error writing file " << argv[3] << endl;
   }

}   

#endif 

// //=========================End Do not change code in main()=====================


// Creates an identity kernel (dummy kernel) that will simply
// copy input to output image and applies it via convolve()
//
// ** This function is complete and need not be changed.
// Use this as an example of how to create a kernel array, fill it in
// appropriately and then use it in a call to convolve.
void dummy(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB])
{
   double k[11][11];
   for (int i = 0; i < 3; i++)
   {
      for(int j = 0; j < 3; j++)
      {
         k[i][j] = 0;
      }
   }
   k[1][1] = 1;
   convolve(out, in, 3, k);
}

// Convolves an input image with an NxN kernel to produce the output kernel
// You will need to complete this function by following the 
// instructions in the comments
void convolve(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB], 
	      int N, double kernel[][11])
{
 
   int padded[SIZE+11][SIZE+11][RGB];  // Use for input image with appropriate 
                                       // padding
   int temp[SIZE][SIZE][RGB];          // Use for the unclamped output pixel 
                                       // values then copy from temp to out, 
                                       // applying clamping 

   //first set all of padded to 0 (black)
   
   /* for loops to set all of padded to 0 (black) */
   // 1st for loop to loop through the rows 
   for(int i = 0; i < (SIZE+11); i++)
   {
      // 2nd for loop to loop through the columns 
      for(int j = 0; j < (SIZE+11); j++)
      {
         // 3rd for loop to loop through the color
         for(int k = 0; k < RGB; k++)
         {
            // sets all of padded to 0 (black)
            padded[i][j][k] = 0;
         }
      }
   }
   
   //now copy input into padding to appropriate locations
   
   /* for loops to pad with N/2 */ 
   // 1st for loop to loop through the rows
   for(int i = N/2; i < (SIZE + N/2); i++)              
   {
      // 2nd for loop to loop through the columns
      for(int j = N/2; j < (SIZE + N/2); j++)
      {
         // 3rd for loop to loop through the color
         for(int k = 0; k < RGB; k++)
         {
            // pads with N/2
            padded[i][j][k] = in[i-(N/2)][j-(N/2)][k];
         }
      }
   }

   //initialize temp pixels to 0 (black)
   
   /* for loops to set all of temp to 0 (black) */
   // 1st for loop to loop through the rows
   for(int i = 0; i < SIZE; i++)
   {
      // 2nd for loop to loop through the columns
      for(int j = 0; j < SIZE; j++)
      {
         // 3rd for loop to loop through the color
         for(int k = 0; k < RGB; k++)
         {
            // sets all of temp to 0 (black)
            temp[i][j][k] = 0;
         }
      }
   }

   //now perform convolve (using convolution equation on each pixel of the 
   // actual image) placing the results in temp (i.e. unclamped result)
   
   // for(int y= ;y< ;y++)
   for(int i = (N/2); i < (SIZE + N/2); i++)
   {
      // for(int x= ;x< ;x++)
      for(int j = (N/2); j < (SIZE + N/2); j++)
      {
         // for(int k=0;k<RGB;k++)
         for(int k = 0; k < RGB; k++)
         {
            // for(int i= ; i<= ; i++)
            for(int l = 0; l <= N; l++)
            {
               // for(int j= ; j<= ; j++)
               for(int m = 0; m <= N; m++)
               {
                  // temp[][][k] += padded[][][k]*kernel[][];
                  temp[i-N/2][j-N/2][k] += padded[i+l-N/2][j+m-N/2][k]*kernel[l][m];
               }
            }
         }
       }
    }


   //now clamp and copy to output
   // You may need to cast to avoid warnings from the compiler:
   // (i.e. out[i][j][k] = (unsigned char) temp[i][j][k];)
   
   // 1st for loop to loop through the rows to clamp
   for(int i = 0; i < SIZE; i++)
   {
      // 2nd for loop to loop through the columns to clamp
      for(int j = 0; j < SIZE; j++)
      {
         // 3rd for loop to loop through the color to clamp
         for(int k = 0; k < RGB; k++)
         {
            // if less than 0, set to 0
            if(temp[i][j][k] < 0)
            {
               temp[i][j][k] = 0;
            }
            // if greater than 255, set to 255
            if(temp[i][j][k] > 255)
            {              
               temp[i][j][k] = 255;
            }
            
            // copy to output
            out[i][j][k] = (unsigned char) temp[i][j][k];
         }
      }
   }
}

// You will need to complete this function by following the 
//  instructions in the comments
void sobel(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB])
{
   double k[11][11];
   double s_h1[3][3] = { {-1, 0, 1}, 
                         {-2, 0, 2}, 
                         {-1, 0, 1} };
   double s_h2[3][3] = { {1, 0, -1}, 
                         {2, 0, -2}, 
                         {1, 0, -1} };
   
   unsigned char h1_soble[SIZE][SIZE][RGB]; //hold intermediate images
   unsigned char h2_soble[SIZE][SIZE][RGB]; 

   for (int i = 0; i < 11; i++)
   {
      for(int j=0; j < 11; j++)
      {
         k[i][j] = 0;
      }
   }


   // Copy in 1st 3x3 horizontal sobel kernel (i.e. copy s_h1 into k)
   
   // 1st for loop to loop through the rows
   // to copy 1st 3x3 horizontal sobel kernal
   for(int i = 0; i < 3; i++)
   {
      // 2nd for loop to loop through the columns
      // to copy 1st 3x3 horizontal sobel kernal
      for(int j = 0; j < 3; j++)
      {
         // copying s_h1 into k
         k[i][j] = s_h1[i][j];
      }
   }

   // Call convolve to apply horizontal sobel kernel with result in h1_soble
   convolve(h1_soble, in, 3, k);

   // Copy in 2nd 3x3 horizontal sobel kernel (i.e. copy s_h2 into k)
   
   // 1st for loop to loop through the rows
   // to copy 2nd 3x3 horizontal sobel kernal
   for(int i = 0; i < 3; i++)
   {
      // 2nd for loop to loop through the columns
      // to copy 2nd 3x3 horizontal sobel kernal
      for(int j = 0; j < 3; j++)
      {
         // copying s_h2 into k
         k[i][j] = s_h2[i][j];
      }
   }

   // Call convolve to apply horizontal sobel kernel with result in h2_soble
   convolve(h2_soble, in, 3, k);

   // Add the two results (applying clamping) to produce the final output
   
   // 1st for loop to loop through the rows
   // to add and clamp for final output
   for(int i = 0; i < SIZE; i++)
   {
      // 2nd for loop to loop through the columns
      // to add and clamp for final output
      for(int j = 0; j < SIZE; j++)
      {
         // 3rd for loop to loop through the color
         // to add and clamp for final output
         for(int l = 0; l < RGB; l++)
         {
            // adds the two results
            out[i][j][l] = h1_soble[i][j][l] + h2_soble[i][j][l];
            
            // if less than 0, set to 0
            if(out[i][j][l] < 0)
            {
               out[i][j][l] = 0;
            }
            
            // if greater than 255, set to 255
            if(out[i][j][l] > 255)      
            {
               out[i][j][l] = 255;
            } 
         }
      } 
   }
}

// Add the rest of your functions here (i.e. gaussian, gaussian_filter, unsharp)

// generates the kernel to be used given the user input 
void gaussian(double k[][11], int N, double sigma)
{
   // variable to ensure sum of values is equal to 1
   double sum = 0.0;
   
   // 1st for loop to loop through the rows
   // with indices based on raw Gaussian indexing
   for(int i = (-N/2); i <= (N/2); i++)
   {
      // 2nd for loop to loop through the columns
      // with indices based on raw Gaussian indexing
      for(int j = (-N/2); j <= (N/2); j++)
      {
         // uses equation to make the kernal values
         // based on raw Gaussian indexing
         k[i+N/2][j+N/2] = pow(M_E, -((i*i + j*j)/(2*sigma*sigma)));
         
         // adds to the sum                                    
         sum += k[i+N/2][j+N/2];
      }
   }
   
   // 1st for loop to loop through the rows to normalize
   for(int i = 0; i < N; i++)
   {
      // 2nd for loop to loop through the columns to normalize
      for(int j = 0; j < N; j++)
      {
         // divides by sum to ensure that the final sum is equal to 1
         k[i][j] /= sum;   
         
         // outputs the kernel for each row to the screen
         cout << k[i][j] << " ";                                               
      } 
      
      // outputs a new line at the end of each row
      cout << endl;
   } 
}

// uses gaussian() function
// to apply kernal to image and convolves the filtered image
void gaussian_filter(unsigned char output[][SIZE][3], 
                      unsigned char input[][SIZE][3], int N, double sigma)
{
   // temp array to hold the values for gaussian
   double temp[11][11];
   
   // applies gaussian kernal to image
   gaussian(temp, N, sigma);
   
   // convolves the filtered image
   convolve(output, input, N, temp);
}

// sharpens the image and enhances the detail in the image
void unsharp(unsigned char output[][SIZE][3], unsigned char input[][SIZE][3],
             int N, double sigma, double alpha)
{
   // applies the gaussian_filter on the image
   gaussian_filter(output, input, N, sigma);
   
   // temp arrays to hold values
   int D[SIZE][SIZE][3];                     
   int S[SIZE][SIZE][3];
   
   // 1st for loop to loop through the rows
   // to create the final output image
   for(int i = 0; i < SIZE; i++)                 
   {
      // 2nd for loop to loop through the columns
      // to create the final output image
      for (int j = 0; j < SIZE; j++)
      {
         // 3rd for loop to loop through the RGB
         // to create the final output image
         for(int k = 0; k < 3; k++)
         {
            // uses formula given to create the final image
            D[i][j][k] = (int)input[i][j][k] - (int)output[i][j][k];
            S[i][j][k] = (int)input[i][j][k] + (int)(alpha*(D[i][j][k]));
         }
      }
   }
   
   // 1st for loop to loop through the rows to clamp
   for(int i = 0; i < SIZE; i++)
   {
      // 2nd for loop to loop through the columns to clamp 
      for (int j = 0; j < SIZE; j++)
      {
         // 3rd for loop to loop through the RGB to clamp
         for(int k = 0; k < 3; k++)
         {
            // if less than 0, set to 0
            if(S[i][j][k] < 0)
            {
               S[i][j][k] = 0;
            }
            // if greater than 255, set to 255
            if(S[i][j][k] > 255)             
            {
               S[i][j][k] = 255;
            }
            
            // puts final, clamped image into output
            output[i][j][k] = (unsigned char) S[i][j][k];
         }
      }
   }
}
