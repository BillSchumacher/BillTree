//
// Created by Bill Schumacher on 11/2/20.
//
// License: MIT

#include "example.h"
#include <stdio.h>
#include "../libbilltree/libbilltree.c"

typedef struct  {
    int a;
    int b;
    int c;
    float d;
} TreeValue;

BillTree* example;
void FreeTreeValue(void* value) {
    free((TreeValue*) value);
}

void hello(void) {
    printf("%lu\n", GetXXHash("Hello, World!\n"));
    example = BillTree_New();
    example->FreeValue = FreeTreeValue;
    TreeValue* tv = malloc(sizeof(TreeValue));
    TreeValue* tv2 = malloc(sizeof(TreeValue));
    BillTree_InsertKeyValue(example, "Hello world!\n", tv);
    printf("Initial\n-------------------\n");
    printf("Leaves: %lu\n", BillTree_Leaves(example));
    printf("Nodes: %lu\n", BillTree_Nodes(example));
    BillTree_InsertKeyValue(example, "Hello world!\n", tv);
    printf("Same hash, no new nodes\n-------------------\n");
    printf("Leaves: %lu\n", BillTree_Leaves(example));
    printf("Nodes: %lu\n", BillTree_Nodes(example));
    printf("New hash, 1 new nodes\n-------------------\n");
    BillTree_InsertKeyValue(example, "Hello world, should increase!\n", tv2);
    printf("Leaves: %lu\n", BillTree_Leaves(example));
    printf("Nodes: %lu\n", BillTree_Nodes(example));
}

void cleanup () {
    printf("Cleanup btrees\n");
    BillTree_Free(example);
}

int main(void) {
    atexit(cleanup);
    hello();
    return 0;
};
