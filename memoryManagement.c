#include <stdio.h>
#include <stdlib.h>

// memory segments

/*
  |-----------------------|
  |argc, argv             |
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
  |global variables       |
  |uninitialized data     |
  |fixed size             |
  |-----------------------|
  |global variables       |
  |initialized data       |
  |fixed size             |
  |-----------------------|
  |text (code)            |
  |fixed size             |
  |-----------------------|
*/

// global variables are stored in the data segment
int uninitializedGlobalVariables1, uninitializedGlobalVariables2, uninitializedGlobalVariables3;
int initializedGlobalVariables1 = 1, initializedGlobalVariables2 = 2, initializedGlobalVariables3 = 3;

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

int main(
    int argc,
    char *argv[]) {
  printf("|----memory segments----|\n");
  printf("|-----------------------|\n");
  printf("|argc, argv             |\n");
  printf("%p : argc\n", &argc);
  printf("%p : argv\n", &argv);
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
  printf("|heap (grows up)        |\n");
  printf("|-----------------------|\n");
  printf("|global variables       |\n");
  printf("|uninitialized data     |\n");
  printf("%p : uninitializedGlobalVariables3\n", &uninitializedGlobalVariables3);
  printf("%p : uninitializedGlobalVariables2\n", &uninitializedGlobalVariables2);
  printf("%p : uninitializedGlobalVariables1\n", &uninitializedGlobalVariables1);
  printf("|-----------------------|\n");
  printf("|global variables       |\n");
  printf("|initialized data       |\n");
  printf("%p : initializedGlobalVariables3\n", &initializedGlobalVariables3);
  printf("%p : initializedGlobalVariables2\n", &initializedGlobalVariables2);
  printf("%p : initializedGlobalVariables1\n", &initializedGlobalVariables1);
  printf("|-----------------------|\n");
  printf("|text (code)            |\n");
  printf("|-----------------------|\n");

  printf("\n\n\n");
  int *heapVariable = (int *)malloc(sizeof(int));
  printf("%p : top of variable in heap\n", heapVariable);
  printf("if stack and heap grow to each other, it will cause stack overflow\n");
  infiniteStackFunction(heapVariable);
}