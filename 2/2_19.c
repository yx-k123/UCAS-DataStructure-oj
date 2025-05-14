#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node *next;
};

struct node *createList();
void insertList(struct node **tail, int n);
void printList(struct node *head);
void delete(struct node **head, int mink, int maxk);

int main()
{   
    int mink = 0;
    int maxk = 0;
    struct node *head = createList();
    struct node *tail = head;
    int temp = 0;
    char ch = ' ';

    while(scanf("%d%c", &temp, &ch) != EOF)
    {   
        insertList(&tail, temp);
        if(ch == '\n')
            break;
    }
    scanf("%d",&mink);
    scanf("%d",&maxk);

    delete(&head, mink, maxk);
    printList(head);
    return 0;
}

struct node *createList()
{
    struct node *head = NULL;

    head = (struct node *)malloc(sizeof(struct node));
    head->data = 0;
    head->next = NULL;

    return head;
}

void insertList(struct node **tail, int n)
{
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->data = n;
    newNode->next = NULL;

    (*tail)->next = newNode;
    *tail = newNode;
    return;
}

void printList(struct node *head)
{
    struct node *temp = head->next;
    while(temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void delete(struct node **head, int mink, int maxk)
{
    struct node *temp = (*head)->next;
    struct node *prev = *head;

    while(temp != NULL)
    {
        if(temp->data > mink && temp->data < maxk)
        {
            temp = temp->next;
            free(prev->next);
            prev->next = temp;
        }
        else if (temp->data <= mink)
        {
            prev = temp;
            temp = temp->next;
        } else {
            break;
        }
    }
    return;
}