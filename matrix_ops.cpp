#include "matrix_ops.h"

double** matrix_allocate(int rows, int cols){ 
	//Allocate a 2D array of doubles using new
	//return that pointer
	
	double** matrix = new double*[rows];
	for (int i = 0; i < rows; i++)
	{
	   matrix[i] = new double[cols];
	   for(int j = 0; j < cols; j++)
	   {
	      matrix[i][j] = 0;
	   }
	}
	
	return matrix;

	return 0; //Replace this line. This included to make the skeleton compile
}

void matrix_delete(double** M, int rows){
	//delete a 2D array with 'rows' #of rows
	
	for (int i = 0; i < rows; i++)
	{
	   delete M[i];
	}
	
	delete [] M;
}

double** matrix_add(double** A, double** B, int rows, int cols){
	//Allocate a new 2D array of the proper size (hint: use matrix allocate)
	//Calculate A+B into your new array
	//Return the pointer to the new array
	
	double** matrixAddition = matrix_allocate(rows,cols);
	
	for (int i = 0; i < rows; i++)
	{
	   for (int j = 0; j < cols; j++)
	   {
	      matrixAddition[i][j] = A[i][j] + B[i][j];
	   } 
	}
	
	return matrixAddition;
	

}

double** matrix_subtract(double** A, double** B, int rows, int cols){
	//Allocate a new 2D array of the proper size (hint: use matrix allocate)
	//Calculate A-B into your new array
	//Return the pointer to the new array
	double** matrixSubtraction = matrix_allocate(rows,cols);
	
	for (int i = 0; i < rows; i++)
	{
	   for (int j = 0; j < cols; j++)
	   {
	      matrixSubtraction[i][j] = A[i][j] - B[i][j];
	   } 
	}
	
	return matrixSubtraction;
	

}

double** matrix_multiply(double** A, int rows_A, int cols_A, double** B, 
	                     int rows_B, int cols_B){
	                     
	 

    //Allocate a new 2D array to hold the result of A*B
    //See the writeup for the proper dimensions
    double** matrixMultiplication = matrix_allocate(rows_A, cols_B);

    //For matrix multiply you'll want to initilize all elements
    //of this new array to 0.0
    
    for (int i = 0; i < rows_A; i++)
	 {
	   for (int j = 0; j < cols_B; j++)
	   {
	      for (int x = 0; x < cols_A; x++)
	      {
	         matrixMultiplication[i][j] += (A[i][x])*(B[x][j]);
	      }
	   } 
	 }
    
    
    

    //Now follow the pseudo-code in the writeup to perform A*B

    return matrixMultiplication; //Replace this line. This included to make the skeleton compile
}
