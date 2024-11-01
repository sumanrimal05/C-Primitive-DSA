#include<stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 2
#define LOAD_FACTOR_THRESHOLD_EXPAND 0.75
#define LOAD_FACTOR_THRESHOLD_SHRINK 0.2


typedef struct {
  int* data;
  int capacity;   // Size of array
  int size;       // Number of elements
  float loadFactor; // Determines how full the array is
}DynamicArray;

//Function prototypes
void calculateLoadFactor(DynamicArray* dArr);
void arrayInitialize(DynamicArray* dArr);
void arraySizeShrink(DynamicArray *dArr);
void arraySizeExtend(DynamicArray *dArr);
void arrayAddElement(DynamicArray *dArr, int value);
void arrayRemoveLast(DynamicArray* dArr);
void freeDynamicArray(DynamicArray* dArr);

void calculateLoadFactor(DynamicArray* dArr){
  // Inorder to avoid dividing by zero
  if(dArr->capacity <= 0){
    dArr->loadFactor = 0.0f;
  }
  dArr->loadFactor = (float) dArr->size / (float) dArr->capacity;

}

void arrayInitialize(DynamicArray* dArr){
  //Initialize the capacity to be 2
  dArr->capacity = 2;
  dArr->size=0;
  dArr->data = (int*) malloc (dArr->capacity * sizeof(int));

  if(!dArr->data){
    fprintf(stderr, "Memory allocation failed during initialization\n");
    exit(EXIT_FAILURE);
  }
}

void arraySizeShrink(DynamicArray *dArr){
  dArr-> capacity /= 2;
  // We don't want to shrink the array Size below 1 as it may cause error
  // So, we just set as the default capacity 2 we used while initializing
  if (dArr->capacity < 2){
    dArr->capacity = 2;
  }

  dArr->data = (int*) realloc(dArr->data, dArr->capacity * sizeof(int));
  if(!dArr->data){
    fprintf(stderr, "Memory allocation failed during shrinking\n");
    exit(EXIT_FAILURE);
  }
}

void arraySizeExtend(DynamicArray *dArr){
  dArr->capacity *= 2; //Double the capacity to reduce frequent reallocation
  dArr->data = (int*) realloc(dArr->data, dArr->capacity * sizeof(int));
  if(!dArr->data){
    fprintf(stderr, "Memory allocation failed during extending\n");
    exit(EXIT_FAILURE);
  }
}

void arrayAddElement(DynamicArray *dArr, int value){
  //Before adding elements. Let's calculate the loadFactor.
  // So that we can know if we need to extend the array or not
  calculateLoadFactor(dArr);
  if(dArr->loadFactor > LOAD_FACTOR_THRESHOLD_EXPAND){
    arraySizeExtend(dArr);
  }

  dArr->data[dArr->size] = value;
  dArr->size++;
}

void arrayRemoveLast(DynamicArray* dArr){


  // Check if there is element in the array
  if(dArr->size == 0){
    printf("Array Empty. Cannot remove element\n");
  }

  // We are first decreasing size so to check if fits in resizing case or not
  dArr->size --;
  //Before removing elements. Let's calculate the loadFactor.
  // So that we can know if we need to shrink the array or not
  calculateLoadFactor(dArr);

  if(dArr->loadFactor < LOAD_FACTOR_THRESHOLD_SHRINK){
    arraySizeShrink(dArr);
  }
  

}

void freeDynamicArray(DynamicArray* dArr){
  free(dArr->data);   //Free the data array
  dArr->data = NULL; //Setting pointer to NULL to prevent dangling pointer
  dArr->capacity = 0; // Reset Capacity
  dArr->size = 0;     // Reset Size
  dArr->loadFactor = 0;   //Reset loadFactor

}



int main(){

  DynamicArray myArray;

  //Initialize the array
  arrayInitialize(&myArray);

  for(int i = 0; i<=10; i++){
    arrayAddElement(&myArray, i);
    printf("Added %d: Size =%d, Capacity =%d, Load Factor =%.2f\n", i,myArray.size, myArray.capacity, myArray.loadFactor);
  }

  // Remove last three elements
  for(int i=0; i<9; i++){
    arrayRemoveLast(&myArray);
    printf("Removed %d: Size =%d, Capacity =%d, Load Factor =%.2f\n", i,myArray.size, myArray.capacity, myArray.loadFactor);
  }

  freeDynamicArray(&myArray);

  return 0;
}