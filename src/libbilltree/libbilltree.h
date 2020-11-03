//
// Created by Bill Schumacher on 11/2/20.
//
// License: MIT

#ifndef BILLTREE_LIBRARY_H
#define BILLTREE_LIBRARY_H
#include "xxh3.h"
#include <stdbool.h>
#include <limits.h>

typedef struct {
    void* value;
    XXH64_hash_t key;
    void* left;
    void* right;
} BillTreeNode;

typedef struct {
    BillTreeNode* root;
    void (*FreeValue) (void*);
} BillTree;

static inline XXH64_hash_t
GetXXHash(const char *s) {
    return XXH3_64bits(s, strlen(s));
}

static inline BillTreeNode*
BillTreeNode_NewHashValue(XXH64_hash_t hash, void* value) {
    BillTreeNode* node = malloc(sizeof(BillTreeNode));
    node->key = hash;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

static inline BillTreeNode*
BillTreeNode_NewKeyValue(const char* key, void* value) {
    return BillTreeNode_NewHashValue(GetXXHash(key), value);
}

static inline BillTree*
BillTree_New() {
    BillTree* tree = malloc(sizeof(BillTree));
    BillTreeNode* root = BillTreeNode_NewHashValue(UINT64_MAX / 2, NULL);
    tree->root = root;
    tree->FreeValue = NULL;
    return tree;
}

static void
BillTreeNode_InsertHashValue(BillTreeNode* node, XXH64_hash_t hash, void* value);

static inline void
BillTreeNode_InsertKeyValue(BillTreeNode* node, const char* key, void* value ) {
    BillTreeNode_InsertHashValue(node, GetXXHash(key), value);
}

static inline void
BillTree_InsertHashValue(BillTree* tree, XXH64_hash_t hash, void* value) {
    BillTreeNode_InsertHashValue(tree->root, hash, value);
}

static inline void
BillTree_InsertKeyValue(BillTree* tree, const char* key, void* value) {
    BillTreeNode_InsertHashValue(tree->root, GetXXHash(key), value);
}

static uint64_t
BillTreeNode_Nodes(BillTreeNode* node);

static inline uint64_t
BillTree_Nodes(BillTree* tree) {
    return BillTreeNode_Nodes(tree->root);
}

static uint64_t
BillTree_LeftNodes(BillTree* tree);

static uint64_t
BillTree_RightNodes(BillTree* tree);

static uint64_t
BillTreeNode_LeftNodes(BillTreeNode* node);

static uint64_t
BillTreeNode_RightNodes(BillTreeNode* node);

static inline bool
BillTreeNode_Equal(BillTreeNode* a, BillTreeNode* b) {
    return a->key == b->key;
}
static inline bool
BillTreeNode_Greater(BillTreeNode* a, BillTreeNode* b) {
    return a->key > b->key;
}
static inline bool
BillTreeNode_Lesser(BillTreeNode* a, BillTreeNode* b) {
    return a->key < b->key;
}

static void*
BillTreeNode_FindHash(BillTreeNode* node, XXH64_hash_t hash);

static inline void*
BillTreeNode_FindKey(BillTreeNode* node, const char* key) {
    return BillTreeNode_FindHash(node, GetXXHash(key));
}

static uint64_t
BillTreeNode_Leaves(BillTreeNode* node);

static inline uint64_t
BillTree_Leaves(BillTree* tree) {
    return BillTreeNode_Leaves(tree->root);
}

static inline uint64_t
BillTree_OuterNodes(BillTree* tree) {
    return BillTreeNode_LeftNodes(tree->root) + 1 + BillTreeNode_RightNodes(tree->root);
}

static void
BillTreeNode_Free(BillTreeNode* node, void (*FreeValue) (void*));

static inline void
BillTree_Free(BillTree* tree) {
    BillTreeNode_Free(tree->root, tree->FreeValue);
    free(tree);
}
#endif //BILLTREE_LIBRARY_H
