#include "inc.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, const char** argv)
{
    int heap[] = {15, 7, 45, 6, 321, 845, 321, 22, 34, 93};
    int size = sizeof(heap) / sizeof(int);
    print_array(heap, size);
    heap_sort(heap, size);
    print_array(heap, size);
    return 0;
}
