#include <iostream>
#include <cmath>
#include "bmplib.h"

using namespace std;

// global variable. bad style but ok for this lab
unsigned char image[SIZE][SIZE];

// Fill in this function:
void draw_rectangle(int top, int left, int height, int width)
{
   // top side
   for (int x = left; x < (left+width); x++)
   {
      int y = top;
      if(x >= 0 && x <= 255)
      {
         if(y >= 0 && y <=255)
         {
            image[y][x] = 0;
         }
      }
   }
   
   // right side
   for (int y = top; y < (top+height); y++)
   {
      int x = left+width;
      if(x >= 0 && x <= 255)
      {
         if(y >= 0 && y <=255)
         {
            image[y][x] = 0;
         }
      }
   }
   
   // bottom side
   for (int x = (left+width); x > left; x--)
   {
      int y = top+height;
      if(x >= 0 && x <= 255)
      {
         if(y >= 0 && y <=255)
         {
            image[y][x] = 0;
         }
      }
   }
   
   // left side
   for (int y = (top+height); y > top; y--)
   {
      int x = left;
      if(x >= 0 && x <= 255)
      {
         if(y >= 0 && y <=255)
         {
            image[y][x] = 0;
         }
      }
   } 
}


// Fill in this function:
void draw_ellipse(int cy, int cx, int height, int width)

{
   double rx = width/2;
   double ry = height/2;
   
   for (double theta=0.0; theta < 2*M_PI; theta += .01)
   {
      double x = rx*cos(theta)+cx;
      double y = ry*sin(theta)+cy;
      if ((y > 0 && y < 255) && (x > 0 && x < 255))
      {
         image[(int)y][(int)x] = 0;
      }
   }
         
}


int main() {
    // initialize the image to all white pixels
    for (int i=0; i < SIZE; i++) {
        for (int j=0; j < SIZE; j++) {
            image[i][j] = 255;
        }
    }
    
    // Main program loop here
    int userInput = 0;
    
    while (userInput != 2)
    {
        cout << "To draw a rectangle, enter: 0 top left height width" << endl;
        cout << "To draw an ellipse, enter: 1 cy cx height width" << endl;
        cout << "To save your drawing as \"output.bmp\" and quit, enter: 2" << endl;
        cout << "Enter your choice: ";
        cin >> userInput;
        
        if (userInput == 0)
        {
            int top = 0;
            int left = 0;
            int height = 0;
            int width = 0;
            cin >> top >> left >> height >> width;
            
            draw_rectangle(top, left, height, width);
        }
        else if (userInput == 1)
        {
            int cy = 0;
            int cx = 0;
            int height = 0;
            int width = 0;
            cin >> cy >> cx >> height >> width;
            
            draw_ellipse(cy, cx, height, width);
        }
    }
    
    if (userInput == 2)
    {
        cout << "Quitting!" << endl;
        writeGSBMP("output.bmp", image);
        showGSBMP(image);
    }
    
    
   
    
    return 0;
}
