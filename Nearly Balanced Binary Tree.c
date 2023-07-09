#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define N 1e7 // defining N as 10^7

// defining Tree Structure
typedef struct Tree
{
    int data;
    int size;
    struct Tree *parent;
    struct Tree *left;
    struct Tree *right;
} tree;

// declaring Global Array
tree *arr[(int)N];

tree *newnode(int val)
{
    // Make new node with specified Value
    tree *temp = (tree *)malloc(sizeof(tree));
    temp->data = val;
    temp->parent = NULL;
    temp->size = 0;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

tree *makebst(int si, int ei)
{
    // Make balanced binary search tree from sorted array
    if (si > ei)
    {
        return NULL;
    }
    int mid = (si + ei) / 2;
    tree *root = arr[mid];
    tree *left = makebst(si, mid - 1);
    tree *right = makebst(mid + 1, ei);

    if (root != NULL)
    {
        // Giving size to node
        root->size = ei - si;
    }

    root->left = left;
    if (left != NULL)
    {
        left->parent = root;
    }

    root->right = right;
    if (right != NULL)
    {
        right->parent = root;
    }

    return root;
}

int makearray(tree *root, int ind)
{
    /*make sorted array from tree node where tree is
    unbalanced(ceases condition for nearly balanced binary tree)*/
    if (root == NULL)
    {
        return ind;
    }
    if (root->left != NULL)
    {
        ind = makearray(root->left, ind);
    }
    arr[ind++] = root;
    if (root->right != NULL)
    {
        ind = makearray(root->right, ind);
    }
    return ind;
}

tree *makeBST(tree *root)
{
    // Returns root of balanced binary tree made from sorted array
    int size = makearray(root, 0);
    tree *Root;
    Root = makebst(0, size - 1);
    return Root;
}

tree *make_balanced(tree *root, int val)
{
    /*Find the node starting from root where nearly balanced
    condition for any sub tree or tree is violated*/
    tree *temp = root;
    while (1)
    {
        int s = temp->size;
        if (val > temp->data && temp->right != NULL)
        {
            int rs = temp->right->size;
            if (4 * (rs + 1) > 3 * (s + 1)) // Checks condition foe nearly balanced binary tree
            {
                if (temp == root)
                {
                    root = makeBST(temp);
                }
                else
                {
                    /*attaching new balanced binary tree to parent of root
                    where nearly balanced condition is violated*/
                    temp->parent->right = makeBST(temp);
                    temp->parent->right->parent = temp->parent;
                }
                break;
            }
            else
            {
                temp = temp->right;
            }
        }
        else if (val < temp->data && temp->left != NULL)
        {
            int ls = temp->left->size;
            if (4 * (ls + 1) > 3 * (s + 1))
            {
                if (temp == root)
                {
                    root = makeBST(temp);
                }
                else
                {
                    temp->parent->left = makeBST(temp);
                    temp->parent->left->parent = temp->parent;
                }
                break;
            }
            else
            {
                temp = temp->left;
            }
        }
        else
        {
            break;
        }
    }
    return root;
}

tree *insert(tree *root, int val)
{
    // Inserting new node in binary tree
    if (root == NULL)
    {
        root = newnode(val);
        return root;
    }
    else if (root->data < val)
    {
        tree *temp;
        temp = insert(root->right, val);
        root->right = temp;
        temp->parent = root;
        root->size++; // updating size of node when new node is added
    }
    else if (root->data > val)
    {
        tree *temp;
        temp = insert(root->left, val);
        root->left = temp;
        temp->parent = root;
        root->size++; // updating size of node when new node is added
    }
    return root;
}

double findtime(double *time, int val)
{
    /*Finding total time for ith iteration by adding time taken
    from 1st iteration to ith iteration*/
    double sum = 0;
    for (int i = 0; i < val; i++)
    {
        sum = sum + time[i];
    }
    return sum;
}

int main()
{
    // File Handling
    FILE *fp1;
    FILE *fp2;
    fp1 = fopen("time_vs_val.csv", "w"); // file in which total time for ith iteration is printed
    fp2 = fopen("t_val.csv", "w");       // file in which time for ith iteration is printed
    fprintf(fp1, "ith Number , Total Time Taken\n");
    fprintf(fp2, "ith Number , Time Taken for ith iteration \n");

    struct Tree *root = NULL;
    double *time = (double *)(calloc(N, sizeof(double)));

    // Inserting nodes in binary tree and calculating time for the iterations
    clock_t start_t, end_t;
    double total_t;
    start_t = clock();
    root = insert(root, 1);
    root = make_balanced(root, 1);
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    time[0] = total_t;

    for (int i = 2; i <= N; i++)
    {
        start_t = clock();
        insert(root, i);
        root = make_balanced(root, i);
        end_t = clock();
        total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        time[i - 1] = total_t;
        if (i % 50000 == 0)
        {
            fprintf(fp1, "%d , %f\n", i, findtime(time, i));
        }
        if (i >= (int)1e5 && i <= (int)1e6)
        {
            fprintf(fp2, "%d , %f\n", i, time[i - 1]);
        }
    }
    fclose(fp1);
    fclose(fp2);
    return 0;
}
