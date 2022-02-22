#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int val;
    struct node *left;
    struct node *right;
    int heightBalance;
} node;
node *minElementNode(node *root)
{
    while (root->left != NULL)
        root = root->left;
    return root;
}
node *findParent(node *root, node *child)
{
    if (root == child)
        return NULL;
    while (root != NULL && root->left != child && root->right != child)
    {
        if (root->val > child->val)
            root = root->left;
        else
            root = root->right;
    }
    return root;
}

node *findSuccessor(node *root, node *n)
{
    if (n->right != NULL)
        return minElementNode(n->right);

    node *parent = findParent(root, n);
    while (parent != NULL && n == parent->right)
    {
        n = parent;
        parent = findParent(root, n);
    }
    return parent;
}
void inorder(node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->val);
        inorder(root->right);
    }
}

node *createNewNode(int val)
{
    node *newNode = (node *)malloc(sizeof(node));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->heightBalance = 0;
    return newNode;
}
void add(node *curr, int val)
{
    if (curr == NULL)
        return;
    node *newNode = createNewNode(val);
    int cond1; //Condition 1
    int cond2; //Condition 2
    while ((cond1 = curr->val > val && curr->left != NULL) || (cond2 = curr->val < val && curr->right != NULL))
    { //while(true) {if(cond1){} else if (cond2){} else break;}
        if (cond1)
            curr = curr->left;
        else if (cond2)
            curr = curr->right;
    }
    if (curr->val > val)
        curr->left = newNode;
    else
        curr->right = newNode;
}
node *find(node *curr, int val)
{
    while (curr != NULL && curr->val != val)
    {
        if (curr->val > val)
            curr = curr->left;
        else
            curr = curr->right;
    }
    if (curr)
        return (curr);
    printf("No such key\n");
    return NULL;
}
node *delete (node *root, int val)
{
    node *toDelete = find(root, val);
    if (!toDelete) //If val does not exist
        return root;
    // Case 1 - Node to be deleted is leaf (or single node)
    if (toDelete->left == NULL && toDelete->right == NULL)
    {
        node *parent = findParent(root, toDelete);
        if (!parent)
        {
            free(toDelete);
            return NULL;
        }

        if (parent->left == toDelete)
            parent->left = NULL;
        else
            parent->right = NULL;
        free(toDelete);
        return root;
    }
    // Case 2 - Node to be deleted is internal node and inorder successor exists
    node *successor = findSuccessor(root, toDelete);
    if (successor)
    {
        int temp = successor->val;
        node *newRoot = delete (root, temp);
        toDelete->val = temp;
        return newRoot;
    }
    // Case 3 - Node to be deleted is internal node and inorder successor does not exist
    else
    {
        node *parent = findParent(root, toDelete);
        if (!parent)
            root = toDelete->left;
        else
            parent->right = toDelete->left;

        free(toDelete);
        return root;
    }
}
node *rotate(node *bt, node *x, node *y, node *z)
{
    node *a, *b, *c, *t0, *t1, *t2, *t3;
    if (z->left == y && y->left == x)
    {
        a = x;
        b = y;
        c = z;
        t1 = a->right;
        t2 = b->right;
        y->heightBalance = 0;
        z->heightBalance = 0;
    }
    else if (z->right == y && y->right == x)
    {
        a = z;
        b = y;
        c = x;
        t1 = b->left;
        t2 = c->left;
        y->heightBalance = 0;
        z->heightBalance = 0;
    }
    else if (z->right == y && y->left == x)
    {
        a = z;
        b = x;
        c = y;
        t1 = b->left;
        t2 = b->right;
        z->heightBalance = -(x->heightBalance);
        x->heightBalance = 0;
        y->heightBalance = 0;
    }
    else if (z->left == y && y->right == x)
    {
        a = y;
        b = x;
        c = z;
        t1 = b->left;
        t2 = b->right;
        z->heightBalance = -(x->heightBalance);
        x->heightBalance = 0;
        y->heightBalance = 0;
    }
    t0 = a->left;
    t3 = c->right;
    b->left = a;
    b->right = c;
    a->left = t0;
    a->right = t1;
    c->left = t2;
    c->right = t3;

    node *parent = findParent(bt, z);
    if (!parent)
        bt = b;
    else if (parent->left == z)
        parent->left = b;
    else
        parent->right = b;
    return bt;
}
node *addinAVL(node *root, int val)
{
    node *curr = root;
    if (curr == NULL)
        return NULL;
    node *newNode = createNewNode(val);
    int cond1; //Condition 1
    int cond2; //Condition 2
    while ((cond1 = curr->val > val && curr->left != NULL) || (cond2 = curr->val < val && curr->right != NULL))
    { //while(true) {if(cond1){} else if (cond2){} else break;}
        if (cond1)
            curr = curr->left;
        else if (cond2)
            curr = curr->right;
    }
    if (curr->val > val)
    {
        curr->left = newNode;
        curr->heightBalance--;
    }
    else
    {
        curr->right = newNode;
        curr->heightBalance++;
    }
    // curr is the parent of newNode
    node *x, *y, *z;
    x = newNode;
    y = curr;
    z = findParent(root, curr);
    if (!z)
        return root;
    if (z->left == y && y->heightBalance != 0)
        z->heightBalance--;
    else if (z->right == y && y->heightBalance != 0)
        z->heightBalance++;

    while (z->heightBalance == -1 || z->heightBalance == 1)
    {
        x = y;
        y = z;
        node *parent = findParent(root, z);
        if (!parent)
            return z;
        else
            z = parent;
        if (z->left == y)
            z->heightBalance--;
        else
            z->heightBalance++;
    }
    return (z->heightBalance == 0) ? root : rotate(root, x, y, z);
}

int main()
{
    // int keys[] = {5, 7, 6, 2, 1, 3};
    // int keys[] = {4, 2, 1, 0, -1};
    // int keys[] = {1, 2, 3, 4, 5};
    int keys[] = {7, 9, 8, 3, 2, 5, 4};
    node *root = createNewNode(keys[0]); //Create first node of tree
    for (int i = 1; i < sizeof(keys) / sizeof(int); i++)
    {
        root = addinAVL(root, keys[i]);
    }

    inorder(root);
    // printf("\n");
    // root = delete (root, 5);
    // inorder(root);
    // printf("\n");
    // root = delete (root, 3);
    // inorder(root);
    // printf("%d %d\n", minElementNode(root)->val, minElementNode(root->right)->val);
    // printf("%p\n", findSuccessor(root, find(root, 7)));
}