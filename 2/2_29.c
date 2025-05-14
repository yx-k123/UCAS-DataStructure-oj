#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

void DeleteCommonElement(struct node **ha, struct node **hb, struct node **hc);
void insertList(struct node **tail, char n);
void printList(struct node *head);
struct node *createList();

int main()
{
    struct node *ha = createList();
    struct node *hb = createList();
    struct node *hc = createList();
    struct node *ta = ha;
    struct node *tb = hb;
    struct node *tc = hc;

    char temp = '0';
    char ch = '0';
    while(scanf("%c%c", &temp, &ch) != EOF)
    {
        insertList(&ta, temp);
        if(ch == '\n')
            break;
    }
    while(scanf("%c%c", &temp, &ch) != EOF)
    {
        insertList(&tb, temp);
        if(ch == '\n')
            break;
    }
    while(scanf("%c%c", &temp, &ch) != EOF)
    {
        insertList(&tc, temp);
        if(ch == '\n')
            break;
    }

    DeleteCommonElement(&ha, &hb, &hc);
    printList(ha);

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

void DeleteCommonElement(struct node **ha, struct node **hb, struct node **hc)
{
    struct node *prev = *ha;
    struct node *curr = (*ha)->next;

    while (curr != NULL)
    {
        struct node *tempB = (*hb)->next;
        struct node *tempC = (*hc)->next;
        int foundInB = 0, foundInC = 0;

        while (tempB != NULL)
        {
            if (tempB->data == curr->data)
            {
                foundInB = 1;
                break;
            }
            tempB = tempB->next;
        }

        while (tempC != NULL)
        {
            if (tempC->data == curr->data)
            {
                foundInC = 1;
                break;
            }
            tempC = tempC->next;
        }

        if (foundInB && foundInC)
        {
            prev->next = curr->next;
            free(curr);
            curr = prev->next;
        }
        else
        {
            prev = curr;
            curr = curr->next;
        }
    }
}