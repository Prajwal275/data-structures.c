#include <stdio.h>
#include <stdlib.h>

typedef struct BTreeNode {
    int *keys;
    struct BTreeNode **children;
    int t, n, leaf;
} BTreeNode;

BTreeNode* createNode(int t, int leaf) {
    BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node->t = t;
    node->leaf = leaf;
    node->keys = (int*)malloc(sizeof(int) * (2 * t - 1));
    node->children = (BTreeNode**)malloc(sizeof(BTreeNode*) * (2 * t));
    node->n = 0;
    return node;
}

void traverse(BTreeNode* root) {
    if (root) {
        for (int i = 0; i < root->n; i++) {
            if (!root->leaf) traverse(root->children[i]);
            printf("%d ", root->keys[i]);
        }
        if (!root->leaf) traverse(root->children[root->n]);
    }
}

int findKey(BTreeNode* root, int k) {
    int idx = 0;
    while (idx < root->n && root->keys[idx] < k) ++idx;
    return idx;
}

void removeFromLeaf(BTreeNode* root, int idx) {
    for (int i = idx + 1; i < root->n; ++i)
        root->keys[i - 1] = root->keys[i];
    root->n--;
}

int getPred(BTreeNode* root, int idx) {
    BTreeNode* cur = root->children[idx];
    while (!cur->leaf) cur = cur->children[cur->n];
    return cur->keys[cur->n - 1];
}

int getSucc(BTreeNode* root, int idx) {
    BTreeNode* cur = root->children[idx + 1];
    while (!cur->leaf) cur = cur->children[0];
    return cur->keys[0];
}

void merge(BTreeNode* root, int idx) {
    BTreeNode* child = root->children[idx], *sibling = root->children[idx + 1];
    child->keys[child->n] = root->keys[idx];
    for (int i = 0; i < sibling->n; ++i)
        child->keys[child->n + 1 + i] = sibling->keys[i];
    if (!child->leaf)
        for (int i = 0; i <= sibling->n; ++i)
            child->children[child->n + 1 + i] = sibling->children[i];
    for (int i = idx + 1; i < root->n; ++i) root->keys[i - 1] = root->keys[i];
    for (int i = idx + 2; i <= root->n; ++i) root->children[i - 1] = root->children[i];
    child->n += sibling->n + 1;
    root->n--;
    free(sibling->keys);
    free(sibling->children);
    free(sibling);
}

void borrowFromPrev(BTreeNode* root, int idx) {
    BTreeNode* child = root->children[idx], *sibling = root->children[idx - 1];
    for (int i = child->n - 1; i >= 0; --i) child->keys[i + 1] = child->keys[i];
    if (!child->leaf)
        for (int i = child->n; i >= 0; --i) child->children[i + 1] = child->children[i];
    child->keys[0] = root->keys[idx - 1];
    if (!child->leaf) child->children[0] = sibling->children[sibling->n];
    root->keys[idx - 1] = sibling->keys[sibling->n - 1];
    child->n++; sibling->n--;
}

void borrowFromNext(BTreeNode* root, int idx) {
    BTreeNode* child = root->children[idx], *sibling = root->children[idx + 1];
    child->keys[child->n] = root->keys[idx];
    if (!child->leaf) child->children[child->n + 1] = sibling->children[0];
    root->keys[idx] = sibling->keys[0];
    for (int i = 1; i < sibling->n; ++i) sibling->keys[i - 1] = sibling->keys[i];
    if (!sibling->leaf)
        for (int i = 1; i <= sibling->n; ++i) sibling->children[i - 1] = sibling->children[i];
    child->n++; sibling->n--;
}

void fill(BTreeNode* root, int idx) {
    if (idx != 0 && root->children[idx - 1]->n >= root->t)
        borrowFromPrev(root, idx);
    else if (idx != root->n && root->children[idx + 1]->n >= root->t)
        borrowFromNext(root, idx);
    else
        merge(root, idx);
}

void removeFromNonLeaf(BTreeNode* root, int idx) {
    int k = root->keys[idx];
    if (root->children[idx]->n >= root->t) {
        root->keys[idx] = getPred(root, idx);
        removeKey(root->children[idx], root->keys[idx]);
    } else if (root->children[idx + 1]->n >= root->t) {
        root->keys[idx] = getSucc(root, idx);
        removeKey(root->children[idx + 1], root->keys[idx]);
    } else {
        merge(root, idx);
        removeKey(root->children[idx], k);
    }
}

void removeKey(BTreeNode* root, int k) {
    int idx = findKey(root, k);
    if (idx < root->n && root->keys[idx] == k) {
        if (root->leaf) removeFromLeaf(root, idx);
        else removeFromNonLeaf(root, idx);
    } else {
        if (root->leaf) { printf("Key %d not found\n", k); return; }
        int flag = (idx == root->n);
        if (root->children[idx]->n < root->t) fill(root, idx);
        if (flag && idx > root->n) removeKey(root->children[idx - 1], k);
        else removeKey(root->children[idx], k);
    }
}

void splitChild(BTreeNode* parent, int i, BTreeNode* child) {
    int t = child->t;
    BTreeNode* z = createNode(t, child->leaf);
    z->n = t - 1;
    for (int j = 0; j < t - 1; j++) z->keys[j] = child->keys[j + t];
    if (!child->leaf) for (int j = 0; j < t; j++) z->children[j] = child->children[j + t];
    child->n = t - 1;
    for (int j = parent->n; j >= i + 1; j--) parent->children[j + 1] = parent->children[j];
    parent->children[i + 1] = z;
    for (int j = parent->n - 1; j >= i; j--) parent->keys[j + 1] = parent->keys[j];
    parent->keys[i] = child->keys[t - 1];
    parent->n++;
}

void insertNonFull(BTreeNode* root, int k) {
    int i = root->n - 1;
    if (root->leaf) {
        while (i >= 0 && root->keys[i] > k) root->keys[i + 1] = root->keys[i], i--;
        root->keys[i + 1] = k; root->n++;
    } else {
        while (i >= 0 && root->keys[i] > k) i--;
        i++;
        if (root->children[i]->n == 2 * root->t - 1) {
            splitChild(root, i, root->children[i]);
            if (root->keys[i] < k) i++;
        }
        insertNonFull(root->children[i], k);
    }
}

BTreeNode* insert(BTreeNode* root, int k) {
    if (!root) {
        root = createNode(3, 1);
        root->keys[0] = k; root->n = 1;
        return root;
    }
    if (root->n == 2 * root->t - 1) {
        BTreeNode* s = createNode(root->t, 0);
        s->children[0] = root; splitChild(s, 0, root);
        int i = 0; if (s->keys[0] < k) i++;
        insertNonFull(s->children[i], k);
        return s;
    }
    insertNonFull(root, k);
    return root;
}

int main() {
    BTreeNode* root = NULL; int n, k;
    printf("Enter number of keys to insert: ");
    scanf("%d", &n); printf("Enter %d keys:\n", n);
   
