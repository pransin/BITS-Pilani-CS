#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int val;
    struct node *left;
    struct node *right;
    int heightBalance;
} node;

node *minElementNode(node *root);
int getHeightLeft(node *curr);
int getHeightRight(node *curr);
int getBalance(node *curr);
node *findParent(node *root, node *child);
node *findSuccessor(node *root, node *n);
void printInOrder(node *root);
node *createNewNode(int val);
void addBST(node *curr, int val);
node *find(node *curr, int val);
node *delete (node *root, int val);
node* rotate(node *root, node *x, node *y, node *z);
node* addAVL(node* root, node* curr, int val);
node* deleteAVL(node* root, node* curr, int val);



int main(){
    node* root = NULL;
    // int values[] = {8, 7, 6, 5, 10};
    // int values[] = {7, 9, 8, 3, 2, 5, 4};
    // int values[] = {5, 7, 6, 2, 1, 3};
    // int values[] = {4, 2, 1, 0, -1};
    int values[] = {1, 2, 3, 4, 5};

    for(int i=0; i<sizeof(values)/sizeof(int); i++){
        root = addAVL(root, root, values[i]);
    }

    printf("Initial tree - \n");

    printInOrder(root);
    printf("\n");

    int toBeDeleted = 5;

    printf("Tree after deleting %d - \n", toBeDeleted);
    root = deleteAVL(root, root, toBeDeleted);
    printInOrder(root);
    printf("\n");

    return 0;
}



node *minElementNode(node *root)
{
    while (root->left != NULL)
        root = root->left;
    return root;
}

int getHeightLeft(node *curr)
{
    if (curr == NULL)
        return -1;
    return getHeightLeft(curr->left)+1;
}

int getHeightRight(node *curr)
{
    if (curr == NULL)
        return -1;
    return getHeightRight(curr->right)+1;
}

int getBalance(node *curr)
{
    if (curr == NULL)
        return 0;
    return getHeightRight(curr) - getHeightLeft(curr);
}
node *findParent(node *root, node *child)
{
    if (root == child)
        return NULL;
    while (root->left != child && root->right != child)
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
void printInOrder(node *root)
{
    if (root != NULL)
    {
        printInOrder(root->left);
        printf("%d ", root->val);
        printInOrder(root->right);
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
void addBST(node *curr, int val)
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
    // Case 2 - Node to be deleted is internal node and printInOrder successor exists
    node *successor = findSuccessor(root, toDelete);
    if (successor)
    {
        int temp = successor->val;
        node *newRoot = delete (root, temp);
        toDelete->val = temp;
        return newRoot;
    }
    // Case 3 - Node to be deleted is internal node and printInOrder successor does not exist
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
node* rotate(node *root, node *x, node *y, node *z){
    node *a, *b, *c, *t0, *t1, *t2, *t3;
    if (z->left == y && y->left == x)
    {
        a = x;
        b = y;
        c = z;
        t1 = a->right;
        t2 = b->right;
    }
    else if (z->right == y && y->right == x)
    {
        a = z;
        b = y;
        c = x;
        t1 = b->left;
        t2 = c->left;
    }
    else if (z->right == y && y->left == x)
    {
        a = z;
        b = x;
        c = y;
        t1 = b->left;
        t2 = b->right;
    }
    else if (z->left == y && y->right == x)
    {
        a = y;
        b = x;
        c = z;
        t1 = b->left;
        t2 = b->right;
    }
    t0 = a->left;
    t3 = c->right;

    node *parent = findParent(root, b);
    if (!parent)
        root = b;
    else if (parent->left == z)
        parent->left = b;
    else
        parent->right = b;

    b->left = a;
    b->right = c;
    a->left = t0;
    a->right = t1;
    c->left = t2;
    c->right = t3;

    a->heightBalance = getBalance(a);
    b->heightBalance = getBalance(b);
    c->heightBalance = getBalance(c);
    return b;
     
}
node* addAVL(node* root, node* curr, int val){
    
    /* 1.  Perform the normal BST insertion */
    if (curr == NULL){
        if(root == NULL){
            root = createNewNode(val);
            return root;
        }
        return(createNewNode(val));
    }
 
    if (val < curr->val){
        curr->left  = addAVL(root, curr->left, val);
    }
    else if (val > curr->val){
        curr->right = addAVL(root, curr->right, val);
    }
    else // Equal vals are not allowed in BST
        return curr;

    curr->heightBalance = getBalance(curr);
    
    if (curr->heightBalance < -1){
        // Left Left Case
        if(val < curr->left->val) return rotate(root, curr->left->left, curr->left, curr);

        //Left Right Case
        if(val > curr->left->val) return rotate(root, curr->left->right, curr->left, curr);

    }

    if (curr->heightBalance > 1){
        
        //Right Right Case
        if(val > curr->right->val) return rotate(root, curr->right->right, curr->right, curr);

        // Right Left Case
        if(val < curr->right->val) return rotate(root, curr->right->left, curr->right, curr);
    }
 
    /* return the (unchanged) node pointer */
    return curr;

}

node* deleteAVL(node* root, node* curr, int val){
	if (curr == NULL)
		return curr;

	// If the val to be deleted is smaller than the root's val, then it lies in left subtree
	if ( val < curr->val )
		curr->left = deleteAVL(root, curr->left, val);

	// If the val to be deleted is greater than the root's val, then it lies in right subtree
	else if( val > curr->val )
		curr->right = deleteAVL(root, curr->right, val);

	// if val is same as root's val, then this is the node to be deleted
	else {
		// node with only one child or no child
		if( (curr->left == NULL) || (curr->right == NULL) ) {
			node *temp = curr->left ? curr->left : curr->right;

			// No child case
			if (temp == NULL) {
				temp = curr;
				curr = NULL;
			}
			else{ // One child case
                node* parent = findParent(curr, temp);
			    curr->val = temp->val; // Copy the contents of the non-empty child

                if(!parent) return NULL;
                if(parent->right == temp) parent->right = NULL;
                else if(parent->left == temp) parent->left = NULL;
            }
			free(temp);
		}
		else {
			// node with two children: Get the printInOrder
			// successor (smallest in the right subtree)
			node* temp = minElementNode(curr->right);

            if(!temp) return NULL;
			// Copy the printInOrder successor's data to this node
			curr->val = temp->val;

			// Delete the printInOrder successor
			curr->right = deleteAVL(root, curr->right, temp->val);
		}
	}

	// If the tree had only one curr then return
	if (curr == NULL)
	return curr;

	curr->heightBalance = getBalance(curr);

	// If this node becomes unbalanced, then there are 4 cases

	// Left Left Case
	if (curr->heightBalance < -1 && curr->left->heightBalance <= 0) return rotate(root, curr->left->left, curr->left, curr);

	// Left Right Case
	if (curr->heightBalance < -1 && curr->left->heightBalance > 0) return rotate(root, curr->left->right, curr->left, curr);

	// Right Right Case
	if (curr->heightBalance > 1 && curr->right->heightBalance >= 0) return rotate(root, curr->right->right, curr->right, curr);

	// Right Left Case
	if (curr->heightBalance > 1 && curr->right->heightBalance < 0) return rotate(root, curr->right->left, curr->right, curr);

	return curr;

}