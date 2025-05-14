#include <stdio.h>
#include <stdlib.h>

struct node
{   
    struct node *prior;
    int data;
    struct node *next;
    int freq;
};

int buffer[100];

void insertList(struct node **head, int n);
void printList(struct node *head);
void searchList(struct node *head, int n);
struct node *initList();

int main()
{   
    
    int i = 0;
    struct node *head = initList();
    int temp = 0;
    char ch = ' ';
    scanf("%d%c", &temp, &ch);
    while(scanf("%d%c", &temp, &ch) != EOF)
    {
        insertList(&head, temp);
        if(ch == '\n')
            break;
    }
    while(scanf("%d%c", &temp, &ch) != EOF)
    {   
        buffer[temp] = (buffer[temp] == 0) ? ++i : buffer[temp] ;
        searchList(head, temp);
        if(ch == '\n')
            break;
    }
    printList(head);
    return 0;
}

struct node *initList()
{
    struct node *head = NULL;

    head = (struct node *)malloc(sizeof(struct node));
    head->data = 0;
    head->next = head;
    head->prior = head;
    head->freq = 0;

    return head;
}

void insertList(struct node **head, int n)
{
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->data = n;
    newNode->freq = 0;

    (*head)->prior->next = newNode;
    newNode->next = *head;
    newNode->prior = (*head)->prior;
    (*head)->prior = newNode;
    
    return;
}

void printList(struct node *head)
{
    struct node *temp = head->next;
    printf("%d", temp->data);
    temp = temp->next;
    while(temp != head)
    {
        printf(" %d", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void searchList(struct node *head, int n)
{
    struct node *temp = head->next;
    while(temp != head)
    {
        if(temp->data == n)
        {
            temp->freq++;
            int frequency = temp->freq;
            struct node *temp2 = temp->prior;
            if (temp2 == head)
                return;

            while (temp2 != head)
            {
                if(temp2->freq > frequency || (temp2->freq == frequency && buffer[temp2->data] < buffer[temp->data]))
                {
                    break;
                }
                temp2 = temp2->prior;
            }

            temp->prior->next = temp->next;
            temp->next->prior = temp->prior;
            temp->next = temp2->next;
            temp->prior = temp2;
            temp2->next->prior = temp;
            temp2->next = temp;

            return;
        }
        temp = temp->next;
    }
    return;
}

