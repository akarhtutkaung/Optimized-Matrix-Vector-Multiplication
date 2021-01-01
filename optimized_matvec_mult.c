#include "matvec.h"
#include <stdlib.h>

int optimized_matrix_trans_mult_vec(matrix_t mat, vector_t vec, vector_t res){
  if(mat.rows != vec.len){
    printf("mat.rows (%ld) != vec.len (%ld)\n",mat.rows,vec.len);
    return 1;
  }
  if(mat.cols != res.len){
    printf("mat.cols (%ld) != res.len (%ld)\n",mat.cols,res.len);
    return 2;
  }

  int length = mat.cols;    //set length
  int limit = length/4;     //set limit, later multiply it with 4

  for(int a=0; a<length; a++){  //initialized the result vector
    VSET(res, a, 0);
  }

  for(int i=0; i<mat.rows; i++){    // set the vector...
    int getV = VGET(vec, i);
    int j=0;
    
    for(; j<(limit*4); j+=4){

      int el1 = MGET(mat, i, j);
      int prod1 = el1 * getV;
      VSET(res, j, prod1+VGET(res, j));     // put the result in the vector

      int el2 = MGET(mat, i, j+1);
      int prod2 = el2 * getV;
      VSET(res, j+1, prod2+VGET(res, j+1));

      int el3 = MGET(mat, i, j+2);
      int prod3 = el3 * getV;
      VSET(res, j+2, prod3+VGET(res, j+2));

      int el4 = MGET(mat, i, j+3);
      int prod4 = el4 * getV;
      VSET(res, j+3, prod4+VGET(res, j+3));
    }

    for (; j < length; j++){    // for the remaining coloumns
      int el = MGET(mat, i, j);
      int prod = el * getV;
      VSET(res, j, prod+VGET(res, j));
    }
  }
  return 0;
}
