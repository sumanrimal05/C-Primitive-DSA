#include "dynamicArray.h"

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