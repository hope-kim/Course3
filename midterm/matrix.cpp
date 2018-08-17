#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>

#include "matrix_ops.h"

using namespace std;

//Program is called like: ./matrix t1.txt add
//First argument is filename
//Second argument is operation to perform
int main(int argc, char const *argv[])
{
    //First check if there are enough arguments
    if(argc < 3)
    {
        cout << "Not enough arguments: ./matrix <filename> <operation>" << endl;
        return 1;
    }
    
    //Now create an ifstream object and try to open the file,
    //If this fails print a message and return 1
    //See the writeup for the error message
    
    ifstream inputFile(argv[1]);
    
    if (inputFile.fail())
    {
        cout << "Unable to open file: " << argv[1] << endl;
        return 1;
    }
    
    //The first line of the file is #rows #cols for the A matrix.
    //Read in these two integer values into appropriately named variables
    
    int rowsA;
    int colsA;
    
    inputFile >> rowsA >> colsA;
    
    
    
    //Pass these values to the matrix_allocate function to allocate
    //a row x col sized array of doubles
    
    double** matrixA = matrix_allocate(rowsA, colsA);
    
    //Write the code needed to read in matrix A into
    //the array you just allocated
    double contentA;
    for (int i = 0; i < rowsA; i++)
    {
        matrixA[i] = new double[colsA];
        for (int j = 0; j < colsA; j++)
        {
            inputFile >> contentA;
            matrixA[i][j] = contentA;
        }
    }
    
    //The next line of the file is #rows #cols for the B matrix
    //Read in these two integer values into appropriately named variables
    
    int rowsB;
    int colsB;
    
    inputFile >> rowsB >> colsB;
    
    
    
    //Pass these two values to the matrix_allocate function to allocate
    //a row x col sized array of doubles
    
    double** matrixB = matrix_allocate(rowsB, colsB);
    
    
    //Write the code needed to read in matrix B
    //into the array you just allocated
    double contentB;
    for (int i = 0; i < rowsB; i++)
    {
        matrixB[i] = new double[colsB];
        for (int j = 0; j < colsB; j++)
        {
            inputFile >> contentB;
            matrixB[i][j] = contentB;
        }
    }
    
    
    
    //Now verify the dimensions are compatible with the operation specified.
    //The operation comes from the 2nd command line argument
    
    
    //If the dimensions aren't compatible, then quit with an error message
    //See the writeup for the error message.
    
    bool compatible = false;
    
    bool stringAdd = !strcmp(argv[2], "add");
    bool stringSub = !strcmp(argv[2], "subtract");
    bool stringMult = !strcmp(argv[2], "multiply");
    
    if (stringAdd || stringSub)
    {
        if (rowsA == rowsB && colsA == colsB)
        {
            compatible = true;
        }
        else
        {
            compatible = false;
            cout << "Number of rows and number of columns must match for add or subtract." << endl;
            return 1;
        }
    }
    else if (stringMult)
    {
        if (colsA == rowsB)
        {
            compatible = true;
        }
        else
        {
            compatible = false;
            cout << "Number of columns in A must match number of rows in B for multiply." << endl;
            return 1;
        }
    }
    //If the 2nd command line argument isn't one of {add, subtract, multiply}
    //Then print out an error message and return 1. See writeup for message.
    
    else
    {
        compatible = false;
        cout << "Unknown Operation: " << argv[2] << endl;
        cout << "Valid operations: add, subtract, multiply" << endl;
        return 1;
        
    }
    //Return 1 in all failure cases
    
    double** result = NULL;
    
    //Now perform the operation.
    
    //Store the size of the result in these variables.
    //For add and subtract it's easy, for multiply check the docs.
    int rows, cols;
    
    if (stringAdd && compatible)
    {
        result = matrix_add(matrixA, matrixB, rowsA, colsA);
        rows = rowsA;
        cols = colsA;
    }
    if (stringSub && compatible)
    {
        result = matrix_subtract(matrixA, matrixB, rowsA, colsA);
        rows = rowsA;
        cols = colsA;
    }
    if (stringMult && compatible)
    {
        result = matrix_multiply(matrixA, rowsA, colsA, matrixB, rowsB, colsB);
        rows = rowsA;
        cols = colsB;
    }
    
    //The functions matrix_add, matrix_subtract and matrix_multiply allocate
    //the result matrix for you.
    //They will return a pointer to this matrix.
    //Don't forget to caputure that pointer. You'll need it.
    
    
    
    //Based on the 2nd command line argument call the proper function in
    //matrix_ops. Set rows and cols to the proper value
    
    //At this point assuming your matrix_ops functions are correct,
    //then YOU'RE almost DONE! ;-) See below for one last thing.
    
    //We give you the code to print out the resulting matrix
    
    
    for(int r = 0; r<rows;r++)
    {
        for(int c = 0; c<cols;c++)
        {
            cout << fixed << setprecision(2) << setw(7) << result[r][c];
        }
        cout << endl;
    }
    
    //Now delete A, B and result using matrix_delete();
    matrix_delete(matrixA, rowsA);
    matrix_delete(matrixB, rowsB);
    
    return 0;
}

