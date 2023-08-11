#include <stdio.h>
#include <stdlib.h>

// memory segments

/*
  |-----------------------|
  |stack (grows down)     |
  |-----------------------|
  |                       |
  |                       |
  |free memory segment    |
  |                       |
  |                       |
  |-----------------------|
  |heap (grows up)        |
  |-----------------------|
  |data (global variables)|
  |fixed size             |
  |-----------------------|
  |text (code)            |
  |fixed size             |
  |-----------------------|
*/

// global variables are stored in the data segment
int unassignedGlobalVariables1, unassignedGlobalVariables2, unassignedGlobalVariables3;
int assignGlobalVariables1 = 1, assignGlobalVariables2 = 2, assignGlobalVariables3 = 3;

void recursiveStackFunction(int now, int end) {
  if (now == end + 1) {
    return;
  }
  int stackVariable = 1;
  printf("%p : stackVariable in recursiveStackFunction %d\n", &stackVariable, now);
  recursiveStackFunction(now + 1, end);
  return;
}

void recursiveHeapFunction(int now, int end) {
  if (now == end + 1) {
    return;
  }
  int *heapVariable = (int *)malloc(sizeof(int));
  recursiveHeapFunction(now + 1, end);
  printf("%p : heapVariable in recursiveHeapFunction %d\n", heapVariable, now);
  free(heapVariable);
  return;
}

void infiniteStackFunction(void *topOfHeap) {
  int stackVariable[10000] = {0};
  printf("%p : stackVariable in infiniteStackFunction\n", &stackVariable);
  printf("%p : topOfHeap \n", topOfHeap);
  infiniteStackFunction(topOfHeap);
  return;
}

int main() {
  printf("|-----------------------|\n");
  printf("|stack (grows down)     |\n");
  recursiveStackFunction(1, 4);
  printf("|-----------------------|\n");
  printf("|                       |\n");
  printf("|                       |\n");
  printf("|free memory segment    |\n");
  printf("|                       |\n");
  printf("|                       |\n");
  printf("|-----------------------|\n");
  recursiveHeapFunction(1, 4);
  printf("|-----------------------|\n");
  printf("|global variables       |\n");
  printf("|fixed size             |\n");
  printf("%p : unassignedGlobalVariables3\n", &unassignedGlobalVariables3);
  printf("%p : unassignedGlobalVariables2\n", &unassignedGlobalVariables2);
  printf("%p : unassignedGlobalVariables1\n", &unassignedGlobalVariables1);
  printf("%p : assignGlobalVariables3\n", &assignGlobalVariables3);
  printf("%p : assignGlobalVariables2\n", &assignGlobalVariables2);
  printf("%p : assignGlobalVariables1\n", &assignGlobalVariables1);
  printf("|-----------------------|\n");
  printf("|text (code)            |\n");
  printf("|fixed size             |\n");
  printf("|-----------------------|\n");

  printf("\n\n\n");
  int *heapVariable = (int *)malloc(sizeof(int));
  printf("%p : top of variable in heap\n", heapVariable);
  printf("if stack and heap grow to each other, it will cause stack overflow\n");
  infiniteStackFunction(heapVariable);
}