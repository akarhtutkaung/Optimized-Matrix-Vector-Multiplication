#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "search.h"

void las(int len, int rep){       // linear array search function
  clock_t start, end;             // initialized start and end for clock
  int o = (2*len)-1;              // to use for the 2nd loop
  int *arr = make_evens_array(len); // make evens array
  start = clock();      // start timer
  for(int x = 0; x<rep; x++){
    for(int y = 0; y<o; y++){
      linear_array_search(arr, len, y);   // linear array search
    }
  }
  end = clock();    // stop timer
  double timet = (double) (end - start)/CLOCKS_PER_SEC; // calculate time taken
  printf ("%11.4e", timet);
  free(arr);  // free the array
}

void lls(int len, int rep){ // linked list search function
  clock_t start, end; // initialized start and end for clock
  int o = (2*len)-1;  // to use for the 2nd loop
  list_t *arr = make_evens_list(len); // make even lists
  start = clock();    // start clock
  for(int x = 0; x<rep; x++){
    for(int y = 0; y<o; y++){
      linkedlist_search(arr, len, y); // linked list search
    }
  }
  end = clock();  // end the clock
  double timet = (double) (end - start)/CLOCKS_PER_SEC; // calculate the time taken
  printf ("%11.4e", timet);
  list_free(arr); // free the list
}

void bas(int len, int rep){     // binary array search function
  clock_t start, end; // initialized start and end for clock
  int o = (2*len)-1;    // to use for 2nd loop
  int *arr = make_evens_array(len); // make even array
  start = clock();  // start clock
  for(int x = 0; x<rep; x++){
    for(int y = 0; y<o; y++){
      binary_array_search(arr, len, y); // binary array search
    }
  }
  end = clock();  // end clock
  double timet = (double) (end - start)/CLOCKS_PER_SEC; // calculate the time taken
  printf ("%11.4e", timet);
  free(arr);  // free the array
}

void bts(int len, int rep){   // binary tree search function
  clock_t start, end; // initializedstart and end for clock
  int o = (2*len)-1;  // to use for 2nd loop
  bst_t *arr = make_evens_tree(len);  // make even tree
  start = clock();  // start clock
  for(int x = 0; x<rep; x++){
    for(int y = 0; y<o; y++){
      binary_tree_search(arr, len, y);  // binary tree search
    }
  }
  end = clock();  // end clock
  double timet = (double) (end - start)/CLOCKS_PER_SEC; // calculate time taken
  printf ("%11.4e", timet);
  bst_free(arr); // free the tree
}

int main(int argc, char *argv[]){
  if(argc <4){      // if less than 3 input, show error
    printf("usage: ./search_benchmark <minpow> <maxpow> <repeats> [which]\n");
    printf(" which is a combination of:\n");
    printf("  a : Linear Array Search\n");
    printf("  l : Linked List Search\n");
    printf("  b : Binary Array Search\n");
    printf("  t : Binary Tree Search\n");
    printf("  (default all)\n");
    return 1;
  }

  int min = 1 << atoi(argv[1]);   // set the min number; 2^min
  int max = 1 << atoi(argv[2]);   // set the max number; 2^max
  int rep = atoi(argv[3]);  // set the repeats number
  char *str;
  int linear_array = 0; // initialized to use for later
  int linked_list = 0;
  int binary_array = 0;
  int binary_tree = 0;

  printf("%6s %10s ","LENGTH","SEARCHES");

  if(argc >= 5){      // if have more than 4 inputs,
    str = argv[4];    // set the 4th input as searching list to consider
    for(int i=0; i<strlen(str); i++){
      if(str[i] == 'a'){    // if have char of a, then set linear_array = 1
        linear_array = 1;
      }
      else if(str[i] == 'l'){ // if have char of l, then set linked_list = 1
        linked_list = 1;
      }
      else if(str[i] == 'b'){ // if have char of b, then set binary_array = 1
        binary_array = 1;
      }
      else if(str[i] == 't'){ // if have char of t, then set binary_tree = 1
        binary_tree = 1;
      }
    }
  }
  else{   // if nothing was mentioned, set all as 1
    linear_array = 1;
    linked_list = 1;
    binary_array = 1;
    binary_tree = 1;
  }
  if(linear_array){printf("%11s ", "array");}   // to display the array, list, binary, tree as the user wanted
  if(linked_list){printf("%10s ", "list");}
  if(binary_array){printf("%10s", "binary");}
  if(binary_tree){printf("%10s", "tree");}
  printf("\n");

  for(int len = min; len<=max; len*=2){
    printf("%6d %10d ", len, len*2*rep);
      if(linear_array){             // if linear_array = 1, go to las() function
        las(len, rep);
      }
      if(linked_list){             // if linked_list = 1, go to lls() function
        lls(len, rep);
      }
      if(binary_array){             // if binary_array = 1, go to bas() function
        bas(len, rep);
      }
      if(binary_tree){             // if binary_tree = 1, go to bts() function
        bts(len, rep);
      }
    printf("\n");
  }
  return 0;
}
