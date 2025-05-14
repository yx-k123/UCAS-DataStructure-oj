#include <stdio.h>
#include <stdlib.h>

struct node
{
    char data;
    struct node *next;
};

struct node *createList();
void insertList(struct node **tail, char n);
void printList(struct node *head);
void reverse(struct node **head);

int main()
{
    struct node *head = createList();
    struct node *tail = head;
    char temp = '0';
    char ch = ' ';

    while(scanf("%c%c", &temp, &ch) != EOF)
    {
        insertList(&tail, temp);
        if(ch == '\n')
            break;
    }
    reverse(&head);
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

void insertList(struct node **tail, char n)
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
    printf("%c", temp->data);
    temp = temp->next;
    while(temp != NULL)
    {
        printf(",%c", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void reverse(struct node **head)
{
    struct node *prev = NULL;
    struct node *current = (*head)->next;
    struct node *next = NULL;

    while(current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    (*head)->next = prev;
}
