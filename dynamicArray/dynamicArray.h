#ifndef DYNAMIC_ARRARY_H
#define DYNAMIC_ARRARY_H

#include<stdio.h>
#include <stdlib.h>

//Structure Defination
typedef struct {
  int* data;
  int capacity;   // Size of array
  int size;       // Number of elements
  float loadFactor; // Determines how filled the array is
}DynamicArray;

//Function prototypes
void calculateLoadFactor(DynamicArray* dArr);
void arrayInitialize(DynamicArray* dArr);
void arraySizeShrink(DynamicArray *dArr);
void arraySizeExtend(DynamicArray *dArr);
void arrayAddElement(DynamicArray *dArr, int value);
void arrayRemoveLast(DynamicArray* dArr);
void freeDynamicArray(DynamicArray* dArr);

#endif