#include "dynamicArray.h"

//Initial Array Capacity for 2 integer size or 8 bytes. 
// So,if the user only enters 2 integer, we don't have to resize it. 
//Defining the initial capacity as per the user need is Recommended
#define INITIAL_CAPACITY 2    

// Threshold constant for load factor
// Load factor is used to determine how filled the array is
// Defining these threshold as: for expansion the array should be filled 75% and vice-versa.
#define LOAD_FACTOR_THRESHOLD_EXPAND 0.75
#define LOAD_FACTOR_THRESHOLD_SHRINK 0.2

void calculateLoadFactor(DynamicArray* dArr){
  // Inorder to avoid dividing by zero
  if(dArr->capacity <= 0){
    dArr->loadFactor = 0.0f;
  }
  dArr->loadFactor = (float) dArr->size / (float) dArr->capacity;

}

//Initialize the dynamic array with initial capacity of 2
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

// Dynamically Shrink Array size
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

// Dynamically increase array size
void arraySizeExtend(DynamicArray *dArr){
  dArr->capacity *= 2; //Double the capacity to reduce frequent reallocation
  dArr->data = (int*) realloc(dArr->data, dArr->capacity * sizeof(int));
  if(!dArr->data){
    fprintf(stderr, "Memory allocation failed during extending\n");
    exit(EXIT_FAILURE);
  }
}

// Add element to the last index of the array
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

// Once you decleare an array. You cannot change it's size without using realloc
// So it is not efficient to reduct the size of array every time we remove the last element
// SO here we are just reducing the array size logically. Actually the array size is same. But we changed the last index value only
// If only the threshod is met only we reduct the size of arr.
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

// Free array memory allocation
void freeDynamicArray(DynamicArray* dArr){
  free(dArr->data);   //Free the data array
  dArr->data = NULL; //Setting pointer to NULL to prevent dangling pointer
  dArr->capacity = 0; // Reset Capacity
  dArr->size = 0;     // Reset Size
  dArr->loadFactor = 0;   //Reset loadFactor

}



