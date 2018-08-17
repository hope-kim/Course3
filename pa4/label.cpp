/* 
label.cpp

Author: Hope Kim

Email: hopekim@usc.edu

Short description of this file:
   This file utilizes the queue class in order to carry out all
   of the different filters such as rgb2gray, gray2binary, and 
   component_labeling with label2RGB.
*/

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "bmplib.h" 
#include "queue.h"
using namespace std;

void usage() { 
    cerr << "usage: ./label <options>" << endl;
    cerr <<"Examples" << endl;
    cerr << "./label test_queue" << endl;
    cerr << "./label gray <input file> <outputfile>" << endl;
    cerr << "./label binary <inputfile> <outputfile>" << endl;
    cerr << "./label segment <inputfile> <outputfile>" << endl;
}

//function prototypes
void test_queue();
void rgb2gray(unsigned char ***in,unsigned char **out,int height,int width);
void gray2binary(unsigned char **in,unsigned char **out,int height,int width);
int component_labeling(unsigned char **binary_image,int **labeled_image,int height,int width);
void label2RGB(int  **labeled_image, unsigned char ***rgb_image,int num_segment,int height,int width);
void clean(unsigned char ***input,unsigned char **gray,unsigned char **binary, int **labeled_image,int height , int width);

// main function, you do not need to make any changes to this function 
int main(int argc,char **argv) {

    srand( time(0) );
    if(argc < 2 )  {
        usage();
        return -1;
    }        
    unsigned char ***input=0;
    unsigned char **gray=0;
    unsigned char **binary=0;
    int **labeled_image=0;
    if( strcmp("test_queue",argv[1]) == 0 ) { 
        test_queue();
    } 
    else if(strcmp("gray",argv[1]) == 0 ) {
        if(argc <4 ) {
            cerr << "not enough arguemnt for gray" << endl;
            return -1;
        }
        int height,width;
        input = readRGBBMP(argv[2],&height,&width);
        if(input == 0)
        {
            cerr << "unable to open " << argv[2] << " for input." << endl;
            return -1;
        }            
        gray = new unsigned char*[height];
        for(int i=0;i<height;i++) 
            gray[i] = new unsigned char[width];
        rgb2gray(input,gray,height,width);
        if(writeGSBMP(argv[3],gray,height,width) != 0) { 
            cerr << "error writing file " << argv[3] << endl;
            clean(input,gray,binary,labeled_image,height,width);
            return -1;
        }
        clean(input,gray,binary,labeled_image,height,width);

    }
    else if(strcmp("binary",argv[1]) == 0 ) {
        if(argc <4 ) {
            cerr << "not enough arguemnt for binary" << endl;
            return -1;
        }            
        int height,width;
        input = readRGBBMP(argv[2],&height,&width);
        if(input == 0)
        {
            cerr << "unable to open " << argv[2] << " for input." << endl;
            clean(input,gray,binary,labeled_image,height,width);
            return -1;
        }            

        gray = new unsigned char*[height];
        for(int i=0;i<height;i++) 
            gray[i] = new unsigned char[width];
        rgb2gray(input,gray,height,width);

        binary = new unsigned char*[height];
        for(int i=0;i<height;i++)
            binary[i] = new unsigned char[width];

        gray2binary(gray,binary,height,width);
        if(writeBinary(argv[3],binary,height,width) != 0) { 
            cerr << "error writing file " << argv[3] << endl;
            clean(input,gray,binary,labeled_image,height,width);
            return -1;
        }
        clean(input,gray,binary,labeled_image,height,width);
     
    }
    else if(strcmp("segment",argv[1]) == 0 ) {
        if(argc <4 ) {
            cerr << "not enough arguemnt for segment" << endl;
            return -1;
        } 
        int height,width;
        input = readRGBBMP(argv[2],&height,&width);
        if(input == 0)
        {
            cerr << "unable to open " << argv[2] << " for input." << endl;
            clean(input,gray,binary,labeled_image,height,width);
            return -1;
        }            

        gray = new unsigned char*[height];
        for(int i=0;i<height;i++) 
            gray[i] = new unsigned char[width];
        rgb2gray(input,gray,height,width);

        binary = new unsigned char*[height];
        for(int i=0;i<height;i++)
            binary[i] = new unsigned char[height];

        gray2binary(gray,binary,height,width);


        labeled_image = new int*[height];
        for(int i=0;i<height;i++) labeled_image[i] = new int[width];
        int segments= component_labeling(binary, labeled_image,height,width); 

        for(int i=0;i<height;i++) 
            for(int j=0;j<width;j++) 
                for(int k=0;k<RGB;k++) 
                    input[i][j][k] = 0;
        label2RGB(labeled_image, input ,segments, height,width);
        if(writeRGBBMP(argv[3],input,height,width) != 0) {
            cerr << "error writing file " << argv[3] << endl;
            clean(input,gray,binary,labeled_image,height,width);
            return -1;
        }
        clean(input,gray,binary,labeled_image,height,width);

    }

   return 0;
}

//This function is used to test your queue implementation. You do not need to change it,
//though doing so might be useful/helpful

void test_queue() { 
    // create some locations;
    Location three_one, two_two;
    three_one.row = 3; three_one.col = 1;
    two_two.row = 2; two_two.col = 2;

    //create an Queue with max capacity 5
    Queue q(5);

    cout << boolalpha;
    cout << q.is_empty() << endl;           // true
    q.push(three_one);
    cout << q.is_empty() << endl;           // false
    q.push(two_two);

    Location loc = q.pop();
    cout << loc.row << " " << loc.col << endl; // 3 1
    loc = q.pop();
    cout << loc.row << " " << loc.col << endl; // 2 2
    cout << q.is_empty() << endl;           // true
}

//Loop over the 'in' image array and calculate the single 'out' pixel value using the formula
// GS = 0.2989 * R + 0.5870 * G + 0.1140 * B 
void rgb2gray(unsigned char ***in,unsigned char **out,int height,int width){
   
   // loops through the rows
   for (int i = 0; i < height; i++)
   {
      // loops through the columns
      for (int j = 0; j < width; j++)
      {
         // uses the formula to create the single "out" pixel
         out[i][j] = (unsigned char) (in[i][j][0]*0.2989+in[i][j][1]*0.5870+in[i][j][2]*0.1140);
      }
   }   
}

//Loop over the 'in' gray scale array and create a binary (0,1) valued image 'out'
//Set the 'out' pixel to 1 if 'in' is above the threshold, else 0
void gray2binary(unsigned char **in,unsigned char **out,int height,int width) {
   
   // loops through the rows
   for (int i = 0; i < height; i++)
   {
      // loops through the columns
      for (int j = 0; j < width; j++)
      {
         // if the "in" pixel is above the threshold, set it to 1
      	if ((unsigned char) in[i][j] > THRESHOLD)
      	{
      	   out[i][j] = (unsigned char) 1;
      	}
      	
      	// if the "in" pixel is below the threshold, set it to 0
         else
         {
         	out[i][j] = (unsigned char) 0;
         }
      }
   } 
}

//This is the function that does the work of looping over the binary image
// and doing the connected component labeling
// See the .pdf for more details
int component_labeling(unsigned char **binary_image,int **label,int height,int width) {
    
    // creates a Queue BFS with max length height*width
    Queue BFS(height*width);
    
    // sets current label to 0
    int current_label = 0;
    
    // loops through the rows
    for (int i = 0; i < height; i++)
    {
      // loops through the columns
    	for (int j = 0; j < width; j++)
    	{
    	   // sets every pixel of the labeled image to 0
			label[i][j] = 0;
    	} 
    }
    
    // loops through the rows
    for (int i = 0; i < height; i++)
    {
      // loops through the columns
    	for (int j = 0; j < width; j++)
    	{
    	   // checks for the first white pixel and if not labeled
    		if (binary_image[i][j] == 1 && !label[i][j])
    		{
    		   // current label is incremented
    			current_label++;
    			
    			// labels the labeled array with the current label
    			label[i][j] = current_label;
    			
    			// makes a new location
    			Location loc;
    			loc.row = i;
    			loc.col = j;
    			
    			// pushes the location into BFS Queue
    			BFS.push(loc);
    		}
    		
    		// continues the BFS
    		while(!BFS.is_empty())
    		{
    		   // captures the location that is in the BFS Queue
    			Location loc = BFS.pop();
            
            // creates the NW neighbor to the original location
    			Location NW;
    			NW.row = loc.row-1;
    			NW.col = loc.col-1;
            
            // checks to make sure the neighbor is within the image
    			if ((NW.row > 0 && NW.row < height) && (NW.col > 0 && NW.col < width))
    			{
    			   // checks if the neighbor is white and is not labeled
	    			if (binary_image[NW.row][NW.col] == 1 && !label[NW.row][NW.col])
	    			{
	    			   // labels the labeled array with the current label
	    				label[NW.row][NW.col] = current_label;
                  
                  // pushes this location into the queue
	    				BFS.push(NW);
	    			}
    			}

            // creates the N neighbor to the original location
    			Location N;
    			N.row = loc.row-1;
    			N.col = loc.col;
    			
    			// checks to make sure the neighbor is within the image
    			if ((N.row > 0 && N.row < height) && (N.col > 0 && N.col < width))
    			{
    			   // checks if the neighbor is white and is not labeled
	    			if (binary_image[N.row][N.col] == 1 && !label[N.row][N.col])
	    			{
	    			   // labels the labeled array with the current label
	    				label[N.row][N.col] = current_label;

                  // pushes this location into the queue
	    				BFS.push(N);
	    			}
    			}

            // creates the NE neighbor to the original location
    			Location NE;
    			NE.row = loc.row-1;
    			NE.col = loc.col+1;
    			
    			// checks to make sure the neighbor is within the image
    			if ((NE.row > 0 && NE.row < height) && (NE.col > 0 && NE.col < width))
    			{
    			   // checks if the neighbor is white and is not labeled
	    			if (binary_image[NE.row][NE.col] == 1 && !label[NE.row][NE.col])
	    			{
	    			   // labels the labeled array with the current label
	    				label[NE.row][NE.col] = current_label;

                  // pushes this location into the queue
	    				BFS.push(NE);
	    			}
    			}

            // creates the E neighbor to the original location
    			Location E;
    			E.row = loc.row;
    			E.col = loc.col+1;
    			
    			// checks to make sure the neighbor is within the image
    			if ((E.row > 0 && E.row < height) && (E.col > 0 && E.col < width))
    			{
    			   // checks if the neighbor is white and is not labeled
	    			if (binary_image[E.row][E.col] == 1 && !label[E.row][E.col])
	    			{
	    			   // labels the labeled array with the current label
	    				label[E.row][E.col] = current_label;

                  // pushes this location into the queue
	    				BFS.push(E);
	    			}
    			}

            // creates the SE neighbor to the original location
    			Location SE;
    			SE.row = loc.row+1;
    			SE.col = loc.col+1;
    			
    			// checks to make sure the neighbor is within the image
    			if ((SE.row > 0 && SE.row < height) && (SE.col > 0 && SE.col < width))
    			{
    			   // checks if the neighbor is white and is not labeled
	    			if (binary_image[SE.row][SE.col] == 1 && !label[SE.row][SE.col])
	    			{
	    			   // labels the labeled array with the current label
	    				label[SE.row][SE.col] = current_label;
                  
                  // pushes this location into the queue
	    				BFS.push(SE);
	    			}
    			}

            // creates the S neighbor to the original location
    			Location S;
    			S.row = loc.row+1;
    			S.col = loc.col;
    			
    			// checks to make sure the neighbor is within the image
    			if ((S.row > 0 && S.row < height) && (S.col > 0 && S.col < width))
    			{
    			   // checks if the neighbor is white and is not labeled
	    			if (binary_image[S.row][S.col] == 1 && !label[S.row][S.col])
	    			{
	    			   // labels the labeled array with the current label
	    				label[S.row][S.col] = current_label;
                  
                  // pushes this location into the queue
	    				BFS.push(S);
	    			}
    			}
            
            // creates the SW neighbor to the original location
    			Location SW;
    			SW.row = loc.row+1;
    			SW.col = loc.col-1;
    			
    			// checks to make sure the neighbor is within the image
    			if ((SW.row > 0 && SW.row < height) && (SW.col > 0 && SW.col < width))
    			{
    			   // checks if the neighbor is white and is not labeled
	    			if (binary_image[SW.row][SW.col] == 1 && !label[SW.row][SW.col])
	    			{
	    			   // labels the labeled array with the current label
	    				label[SW.row][SW.col] = current_label;
                  
                  // pushes this location into the queue
	    				BFS.push(SW);
	    			}
    			}

            // creates the W neighbor to the original location
    			Location W;
    			W.row = loc.row;
    			W.col = loc.col-1;
    			
    			// checks to make sure the neighbor is within the image
    			if ((W.row > 0 && W.row < height) && (W.col > 0 && W.col < width))
    			{
    			   // checks if the neighbor is white and is not labeled
	    			if (binary_image[W.row][W.col] == 1 && !label[W.row][W.col])
	    			{
	    			   // labels the labeled array with the current label
	    				label[W.row][W.col] = current_label;
                  
                  // pushes this location into the queue
	    				BFS.push(W);
	    			}
    			}
    		}		
    	}
    }
    
    // returns the current label after all the BFS is finished
    return current_label;
}    

//First make num_segments number of random colors to use for coloring the labeled parts of the image.
//Then loop over the labeled image using the label to index into your random colors array.
//Set the rgb_pixel to the corresponding color, or set to black if the pixel was unlabeled.
#ifndef AUTOTEST
void label2RGB(int  **labeled_image, unsigned char ***rgb_image,int num_segments,int height,int width)
{
   // makes a dynamically allocated array for random colors
   int** randomColorsArray = new int*[num_segments];
   for (int i = 0; i < num_segments; i++)
   {
   		randomColorsArray[i] = new int[3];
   		for (int j = 0; j < 3; j++)
   		{
   			randomColorsArray[i][j] = rand() % 255;
   		}
   }
   
   // loops through the rows
   for (int i = 0; i < height; i++)
	{
	   // loops through the columns
	   for (int j = 0; j < width; j++)
	   {
	      // loops through the colored pixels
	      for (int k = 0; k < 3; k++)
	   	{
	   	   // if the labeled array has not been labeled yet, set it to black
	   		if (!labeled_image[i][j])
		   	{
		   		rgb_image[i][j][k] = 0;
		   	}
		   	
		   	// if the label array has been labeled, set it to a random color
		   	else
		   	{
		   	   // uses the label to create a random color pixel
		   		rgb_image[i][j][k] = (unsigned char) randomColorsArray[labeled_image[i][j]-1][k];
		   	}	
	   	}
	   }
	}
	
	// deletes the dynamic memory allocation
	for (int i = 0; i < num_segments; i++)
	{
		delete [] randomColorsArray[i];
	}
   delete [] randomColorsArray;
}
#endif

//fill out this function to delete all of the dynamic arrays created
#ifndef AUTOTEST
void clean(unsigned char ***input,unsigned char **gray,unsigned char **binary, int **labeled_image,int height , int width) {
   if(input) {
      //delete allocated input image array here
    	for (int i = 0; i < height; i++)
    	{
    		for (int j = 0; j < width; j++)
    		{
    			delete [] input[i][j];
    		}
    		delete [] input[i];
    	}
    	delete [] input;
    } 

   if(gray) {
      //delete gray-scale image here
      for (int i = 0; i < height; i++)
      {
         delete [] gray[i];
      }
      delete [] gray;       
   }
   
   if(binary) {
      //delete binary image array here
      for (int i = 0; i < height; i++)
      {
         delete [] binary[i];
      }
      delete [] binary;
   }
   
   if(labeled_image) {
      //delete labeled array here
      for (int i = 0; i < height; i++)
      {
         delete [] labeled_image[i];
      }
      delete [] labeled_image;
   }
}
#endif
