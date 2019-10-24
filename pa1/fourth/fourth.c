/*
This program uses a linear algebra formula to predict the price of a house, given its elements (number of bathrooms, year made, etc)
*/

#include <stdlib.h>
#include <stdio.h>


double** inverse(double** matrix, int rows, int cols){
 
  double** inversed = (double**)malloc(sizeof(double*)* rows);
  int i, j, a;
  for(i=0; i < rows; i++){
    inversed[i] = (double*)malloc(sizeof(double)*(cols)); 
  }
  for(i=0; i< rows; i++){
    for(j=0; j<cols; j++){
      if(i==j)
	inversed[i][j]=1;
      else
	inversed[i][j]=0;
    }
  }
  
   if (matrix[0][0] != 0 && matrix[0][0] != 1){
       double temp = matrix[0][0];
      for (a=0; a<cols; a++){
	   matrix[0][a] = matrix[0][a]/temp;
	   inversed[0][a] = inversed[0][a]/temp;
      }
   }
	
      for (a=1; a<rows; a++){
	if(matrix[a][0] !=0){ 
	 double mult = matrix[a][0];
	 int c;
	 for (c=0; c<cols; c++){
	   matrix[a][c]-= (matrix[0][c] * mult);
	   inversed[a][c]-= (inversed[0][c] * mult);
	 }
	}
       }
	
       for ( a=1; a<rows; a++){
	 if (matrix[a][a] != 0 && matrix[a][a] != 1){
	   double div = matrix[a][a];
	   int b;
	   for (b=0; b<cols; b++){
	     matrix[a][b] = (matrix[a][b]/div);
	     inversed[a][b] = (inversed[a][b]/div);
	   }
	 }
		
	 if (rows > a+1){

	   int z, t;
	   for (z=a+1; z<rows; z++){
	     if(matrix[z][a] !=0){
	       double mult = matrix[z][a];
	       for (t=0; t<cols; t++){
		 matrix[z][t] -= (matrix[a][t] * mult);
		 inversed[z][t] -= (inversed[a][t] * mult);
	       }
	     }
	   }
	 }
		
		
	 int x;
	 for (x=a-1; x>=0; x--){
	   int y;
	  if(matrix[x][a] != 0){
	     //need to find a mult
	     double mult = matrix[x][a];
	     for (y=0; y<cols; y++){
	       matrix[x][y] -= (matrix[a][y] * mult);
	       inversed[x][y] -= (inversed[a][y] * mult);
	     }
	   }
	 }
	}

  return inversed;
}

double** transpose(double** A, int row, int col){
  col = col+1;
  double** result = (double**)malloc(sizeof(double)* col);
  int i;
  for(i=0; i < col; i++){
    result[i] = (double*)malloc(sizeof(double)*row);
  }
  int j;
  for(i = 0; i<row; i++){
    for(j=0; j<col; j++){
      result[j][i] = A[i][j];
    }
  }

  return result;
}

double**  Multiply(double** A, int rowA, int colA, double** B, int rowB, int colB){
  // printf("in mult\n");
  double** result = (double**)malloc(sizeof(double*)* rowA);
  int i;
  for(i=0; i < rowA; i++){
    result[i] = (double*)malloc(sizeof(double)*colB);
  }
  int j, k;
  for(i = 0; i<rowA; i++){
    for(j=0; j<colB; j++)
      result[i][j] =0;
  }

  for(i = 0; i <rowA; i++){
    for(j=0; j<colB; j++){
      for(k=0; k <colA; k++){
	result[i][j] += A[i][k]*B[k][j];
	
      }

    }

  }

  return result;
}

double** CreateX(int row, int col, FILE* fp){
  // printf("create x");
  col = col+1;
  int i, j, r;
  // double num;
  double** matrix = (double**)malloc(sizeof(double*) * row);
  for(i = 0; i<row; i++)
   matrix[i]=(double*)malloc(sizeof(double)*col);
  for( i=0; i<row; i++){
    for(j=0; j<col; j++){
      r = fscanf(fp, "%lf%*c", &matrix[i][j]);
      if(r == EOF)
  	return matrix;
      // printf("%lf", matrix[i][j]);
    }
    // printf("\n");
  }
  return matrix;
}


int main(int argc, char** argv){
 
 int attr, examples;
  FILE* trainfp = fopen(argv[1], "r");

  fscanf(trainfp, "%d", &attr);
  fscanf(trainfp, "%d", &examples);

  
 double** X = CreateX(examples, attr, trainfp);
 double** Y = (double**)malloc(sizeof(double*)*examples);
 int i,j;
 for(i=0; i<examples; i++)
   Y[i]=(double*)malloc(sizeof(double));
  for(i=0; i< examples; i++){
     Y[i][0] = X[i][0];
     X[i][0] = 1;
  }
 
  double** transposedX= transpose(X, examples, attr);
  double** firstMult = Multiply(transposedX, attr+1, examples, X, examples, attr+1);
  double** inversed= inverse(firstMult, attr+1, attr+1);
  double** xInvx = Multiply(inversed, attr+1, attr+1, transposedX, attr+1, examples);
  double** W = Multiply(xInvx, attr+1, examples, Y, examples, 1);

  FILE* test = fopen(argv[2], "r");
  if(test == NULL)
    printf("error\n");
  else{
  int newEx;
  fscanf(test,"%d", &newEx);
  
  int r;
  double** newX = (double**)malloc(sizeof(double*) * newEx);
  for(i = 0; i<newEx; i++)
    newX[i]=(double*)malloc(sizeof(double)*(attr+1));
  for(i=0; i<newEx;i++){
    newX[i][0]=1;
;
  }
  for( i=0; i<newEx; i++){
    for(j=1; j<attr+1; j++){
	r = fscanf(test, "%lf%*c", &newX[i][j]);
	if(r == EOF)
	  break;      
    }
  } 
  
  double** newY = Multiply(newX, newEx, attr+1, W, attr+1, 1);
  
  for(i=0; i<newEx; i++){
    for(j=0; j<1; j++)
      printf("%0.0lf", newY[i][j]);
    printf("\n");
    }
  }
  fclose(trainfp);
  fclose(test);
  return 0;
}
