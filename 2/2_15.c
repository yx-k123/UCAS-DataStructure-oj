#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node *next;
};

struct node *createList();
void insertList(struct node **tail, int n);
struct node *addList(struct node **ha, struct node **hb, struct node **ta, struct node **tb);
void printList(struct node *head);

int main()
{
    struct node *ha = createList();
    struct node *hb = createList();

    struct node *ta = ha;
    struct node *tb = hb;

    int temp = 0;
    char ch = ' ';
    while(scanf("%d%c", &temp, &ch) != EOF)
    {
        if(ch == '\n')
            break;
    }

    while(scanf("%d%c", &temp, &ch) != EOF)
    {
        if(ch == '\n'){
            insertList(&ta, temp);
            break;
        }
        insertList(&ta, temp);
    }

    while(scanf("%d%c", &temp, &ch) != EOF)
    {
        if(ch == '\n'){
            insertList(&tb, temp);
            break;
        }
        insertList(&tb, temp);
    }

    struct node *hc = addList(&ha, &hb, &ta, &tb);
    printList(hc);

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

struct node *addList(struct node **ha, struct node **hb, struct node **ta, struct node **tb)
{
    struct node *result = createList();
    (*tb)->next = (*ha)->next;
    result->next = (*hb)->next;

    return result;
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