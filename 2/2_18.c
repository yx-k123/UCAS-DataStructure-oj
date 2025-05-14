#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

struct node *createList(int n);
void insertList(struct node **tail, int n);
void deleteNode(struct node **head, int n);
void printList(struct node *head);

int main()
{   
    int temp = 0;
    char ch = ' ';
    scanf("%d", &temp);
    struct node *head = createList(temp);
    struct node *tail = head;

    while(scanf("%c%d", &ch, &temp) != EOF)
    {
        if(ch == '\n')
            break;
        insertList(&tail, temp);
    }

    deleteNode(&head, temp);
    printList(head);
    return 0;
}

struct node *createList(int n)
{
    struct node *head = NULL;

    head = (struct node *)malloc(sizeof(struct node));
    head->data = n;
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

void deleteNode(struct node **head, int i)
{
    if (*head == NULL || i < 0)
        return;

    struct node *temp = *head;
    struct node *prev = NULL;

    for (int index = 0; temp != NULL && index < i; index++)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
        return;

    if (prev == NULL)
        *head = temp->next;
    else
        prev->next = temp->next;

    free(temp);
}

void printList(struct node *head)
{
    struct node *temp = head;
    if(temp == NULL)
    {
        printf("NULL\n");
        return;
    }
    while(temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}