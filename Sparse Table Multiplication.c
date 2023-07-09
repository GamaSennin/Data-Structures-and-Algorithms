#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// creating data structure Matrix
typedef struct NODE
{
    int data;
    int row;
    int column;
    struct NODE *next;
    struct NODE *down;
} matrix;

// creating node in the data structure Matrix
matrix *create_Node(int data, int row, int column)
{
    matrix *node = (matrix *)malloc(sizeof(matrix));
    node->data = data;
    node->row = row;
    node->column = column;
    node->next = NULL;
    node->down = NULL;
    return node;
}

// Adding node in the Matrix
matrix *create(int n, matrix *head_column[], matrix *head_row[])
{

    matrix *head = NULL;
    matrix *tail_column = NULL;
    matrix *tail_row = NULL;
    matrix *third = NULL;
    head = (matrix *)malloc(sizeof(matrix));
    head->data = 0;
    head->row = 0;
    head->column = 0;
    head->next = NULL;
    head->down = NULL;
    tail_column = head;
    head_column[0] = head;
    tail_row = head;
    head_row[0] = head;
    for (int i = 1; i <= n; i++)
    {
        third = create_Node(0, 0, i);
        tail_column->next = third;
        tail_column = tail_column->next;
        head_column[i] = tail_column;
        third = create_Node(0, i, 0);
        tail_row->down = third;
        tail_row = tail_row->down;
        head_row[i] = tail_row;
    }
    return head;
}

// Multiplying two matrices
void multiply(matrix *head1, matrix *head2)
{
    matrix *row = head1->down;
    matrix *column = head2->next;
    matrix *a;
    matrix *b;
    int sum = 0;
    int k = 0;
    while (row != NULL)
    {
        column = head2->next;
        while (column != NULL)
        {
            sum = 0;
            a = row->next;
            b = column->down;
            while (a != NULL && b != NULL)
            {
                if ((a->column) > (b->row))
                    b = b->down;
                else if ((a->column) < (b->row))
                    a = a->next;
                else
                {
                    sum = sum + a->data * b->data;
                    a = a->next;
                    b = b->down;
                }
            }
            if (sum != 0)
            {
                k = 1;
                printf("%d %d %d\n", row->row, column->column, sum);
            }

            column = column->next;
        }

        row = row->down;
    }
    if (!k)
        printf("NULL MATRIX!");
}

// deleting empty columns which doesn't contain any element
void delete_empty_columns(matrix *head, int n)
{
    matrix *right = head->next;
    matrix *current = head;
    for (int i = 0; i < n; i++)
    {
        if (right->down == NULL)
        {
            current->next = right->next;
            matrix *a = right;
            right = right->next;
            free(a);
        }
        else
        {
            current = current->next;
            right = right->next;
        }
    }
}

// deleting empty rows which doesn't contain any element
void delete_empty_rows(matrix *head, int n)
{
    matrix *right = head->down;
    matrix *current = head;
    for (int i = 0; i < n; i++)
    {
        if (right->next == NULL)
        {
            current->down = right->down;
            matrix *a = right;
            right = right->down;
            free(a);
        }
        else
        {
            current = current->down;
            right = right->down;
        }
    }
}
void free_row_column(matrix ** arr,int n){
    for(int i=0;i<=n;i++){
        free(arr[i]);
    }
}
// Driver code
int main()
{
    // taking input size of matrix
    int n;
    scanf("%d", &n);

    matrix *head1;
    matrix **head_column1;
    head_column1 = (matrix **)malloc((n + 1) * sizeof(matrix *));
    matrix **head_row1;
    head_row1 = (matrix **)malloc((n + 1) * sizeof(matrix *));
    head1 = create(n, head_column1, head_row1);

    matrix *head2;
    matrix **head_column2;
    head_column2 = (matrix **)malloc((n + 1) * sizeof(matrix *));
    matrix **head_row2;
    head_row2 = (matrix **)malloc((n + 1) * sizeof(matrix *));
    head2 = create(n, head_column2, head_row2);

    // Scaning all elments from input and building up data structure
    int a, b, c, d;
    scanf("%d", &a);
    matrix *third = NULL;
    while (a == 1)
    {
        scanf("%d %d %d", &b, &c, &d);
        third = create_Node(d, b, c);
        head_row1[b]->next = third;
        head_row1[b] = head_row1[b]->next;

        head_column1[c]->down = third;
        head_column1[c] = head_column1[c]->down;

        scanf("%d", &a);
    }

    // optimizing space complexity or memory by deleting redundent nodes in matrix1
    
    delete_empty_columns(head1, n);
    delete_empty_rows(head1, n);
    while (a == 2)
    {
        scanf("%d %d %d", &b, &c, &d);
        third = create_Node(d, b, c);
        head_row2[b]->next = third;
        head_row2[b] = head_row2[b]->next;
        head_column2[c]->down = third;
        head_column2[c] = head_column2[c]->down;

        scanf("%d", &a);
    }

    // optimizing space complexity or memory by deleting redundent nodes in matrix1
    
    delete_empty_columns(head2, n);
    delete_empty_rows(head2, n);

    // multiplying two matrices and printing out final output matrix
    multiply(head1, head2);

    //optimizing memory
    free_row_column(head_row1,n);
    free_row_column(head_column1,n);
    free_row_column(head_row2,n);
    free_row_column(head_column2,n);
    return 0;
}