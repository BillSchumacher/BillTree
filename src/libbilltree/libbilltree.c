//
// Created by Bill Schumacher on 11/2/20.
//
// License: MIT

#include "libbilltree.h"

void BillTreeNode_InsertHashValue(BillTreeNode *node, XXH64_hash_t hash, void *value) {
    if (node->key == hash) {
        if (node->value != NULL && node->value != value) {
            free(node->value);
        }
        node->value = value;
        return;
    }
    if (node->key > hash) {
        if (node->right != NULL) {
            BillTreeNode_InsertHashValue(node->right, hash, value);
        } else {
            node->right = BillTreeNode_NewHashValue(hash, value);
        }
    } else {
        if (node->left != NULL) {
            BillTreeNode_InsertHashValue(node->left, hash, value);
        } else {
            node->left = BillTreeNode_NewHashValue(hash, value);
        }
    }
}

uint64_t BillTreeNode_Nodes(BillTreeNode *node) {
    uint64_t child_count = 1;
    if (node->left != NULL) {
        child_count += BillTreeNode_Nodes(node->left);
    }
    if (node->right != NULL) {
        child_count += BillTreeNode_Nodes(node->right);
    }
    return child_count;
}

uint64_t BillTree_LeftNodes(BillTree *tree) {
    if (tree->root->left != NULL) {
        return 1 + BillTreeNode_Nodes(tree->root->left);
    }
    return 1;
}

uint64_t BillTree_RightNodes(BillTree *tree) {
    if (tree->root->right != NULL) {
        return 1 + BillTreeNode_Nodes(tree->root->right);
    }
    return 1;
}

uint64_t BillTreeNode_LeftNodes(BillTreeNode *node) {
    if (node->left != NULL) {
        return 1 + BillTreeNode_Nodes(node->left);
    }
    return 1;
}

uint64_t BillTreeNode_RightNodes(BillTreeNode *node) {
    if (node->right != NULL) {
        return 1 + BillTreeNode_Nodes(node->right);
    }
    return 1;
}

uint64_t BillTreeNode_Leaves(BillTreeNode *node) {
    if (node->left == NULL && node->right == NULL) {
        return 1;
    }
    uint64_t leaves = 0;
    if (node->left != NULL) {
        leaves += BillTreeNode_Leaves(node->left);
    }
    if (node->right != NULL) {
        leaves += BillTreeNode_Leaves(node->right);
    }
    return leaves;
}

void *BillTreeNode_FindHash(BillTreeNode *node, XXH64_hash_t hash) {
    if (node->key == hash) {
        return node->value;
    }
    if (node->key > hash) {
        if (node->right != NULL) {
            return BillTreeNode_FindHash(node->right, hash);
        } else {
            return NULL;
        }
    } else {
        if (node->left != NULL) {
            return BillTreeNode_FindHash(node->left, hash);
        } else {
            return NULL;
        }
    }
}

void BillTreeNode_Free(BillTreeNode *node, void (*FreeValue)(void *)) {
    if (node->left != NULL) {
        BillTreeNode_Free(node->left, FreeValue);
    }
    if (node->right != NULL) {
        BillTreeNode_Free(node->right, FreeValue);
    }
    if (node->value != NULL) {
        if (FreeValue != NULL) {
            FreeValue(node->value);
        } else {
            free(node->value);
        }
    }
    free(node);
}
