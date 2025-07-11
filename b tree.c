#include <stdio.h>
#include <stdlib.h>

#define ORDER 3

// B-tree node structure
typedef struct BTreeNode {
    int keys[ORDER - 1];
    struct BTreeNode *children[ORDER];
    int numKeys;
    int leaf;
} BTreeNode;

// Function to create a new B-tree node
BTreeNode* createNode(int leaf) {
    BTreeNode *newNode = (BTreeNode *)malloc(sizeof(BTreeNode));
    newNode->numKeys = 0;
    newNode->leaf = leaf;
    for (int i = 0; i < ORDER; i++) newNode->children[i] = NULL;
    return newNode;
}

// Function to insert a key into the B-tree
void insert(BTreeNode **root, int key) {
    if (*root == NULL) {
        *root = createNode(1);  // root is a leaf node initially
        (*root)->keys[0] = key;
        (*root)->numKeys = 1;
        return;
    }

    BTreeNode *r = *root;
    if (r->numKeys == ORDER - 1) {
        BTreeNode *newRoot = createNode(0);
        newRoot->children[0] = r;
        split(newRoot, 0);
        *root = newRoot;
    }
    insertNonFull(*root, key);
}

// Function to split a full node
void split(BTreeNode *x, int i) {
    BTreeNode *y = x->children[i];
    BTreeNode *z = createNode(y->leaf);
    z->numKeys = ORDER / 2;

    for (int j = 0; j < ORDER / 2; j++) z->keys[j] = y->keys[j + ORDER / 2];

    if (!y->leaf) {
        for (int j = 0; j < ORDER / 2 + 1; j++) z->children[j] = y->children[j + ORDER / 2];
    }
    
    y->numKeys = ORDER / 2;
    for (int j = x->numKeys; j > i; j--) x->children[j + 1] = x->children[j];
    x->children[i + 1] = z;

    for (int j = x->numKeys - 1; j >= i; j--) x->keys[j + 1] = x->keys[j];
    x->keys[i] = y->keys[ORDER / 2 - 1];
    x->numKeys++;
}

// Function to insert into a non-full node
void insertNonFull(BTreeNode *x, int key) {
    int i = x->numKeys - 1;
    if (x->leaf) {
        while (i >= 0 && key < x->keys[i]) {
            x->keys[i + 1] = x->keys[i];
            i--;
        }
        x->keys[i + 1] = key;
        x->numKeys++;
    } else {
        while (i >= 0 && key < x->keys[i]) i--;
        i++;
        if (x->children[i]->numKeys == ORDER - 1) {
            split(x, i);
            if (key > x->keys[i]) i++;
        }
        insertNonFull(x->children[i], key);
    }
}

// Function to print the B-tree
void printTree(BTreeNode *root, int level) {
    if (root != NULL) {
        printf("Level %d: ", level);
        for (int i = 0; i < root->numKeys; i++) printf("%d ", root->keys[i]);
        printf("\n");

        if (!root->leaf) {
            for (int i = 0; i <= root->numKeys; i++) printTree(root->children[i], level + 1);
        }
    }
}

int main() {
    BTreeNode *root = NULL;
    int keys[] = {8, 9, 10, 11, 15, 20, 17};

    for (int i = 0; i < 7; i++) {
        insert(&root, keys[i]);
    }

    printTree(root, 0);
    return 0;
}
