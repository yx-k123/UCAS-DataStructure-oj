#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct PolyTerm{
  int coef;
  int expn;
};

typedef struct PolyNode{
  struct PolyTerm data;
  struct PolyNode *next;
} PolyNode, *PolyLink;

typedef PolyLink LinkedPoly;

LinkedPoly createNode();
void insertPoly(LinkedPoly* head, int coef, int expn);
void printPoly(LinkedPoly head);
void parseInput(LinkedPoly* head, char* input);
void derivation(LinkedPoly* head);

int main()
{
    LinkedPoly poly = createNode(); 
    char input[100];

    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0'; 

    parseInput(&poly, input); 
    derivation(&poly);
    printPoly(poly); 

    return 0;
}

void parseInput(LinkedPoly* head, char* input) {
    int coef = 0, expn = 0, sign = 1;
    char* p = input;

    while (*p) {
        while (isspace(*p)) {
            p++;
        }
        if (*p == '+') {
            sign = 1;
            p++;
        } else if (*p == '-') {
            sign = -1;
            p++;
        }
        while (isspace(*p)) {
            p++;
        }
        if (isdigit(*p)) {
            coef = 0;
            while (isdigit(*p)) {
                coef = coef * 10 + (*p - '0');
                p++;
            }
            coef *= sign;
        } else {
            coef = sign; 
        }

        if (*p == 'x') {
            p++;
            if (*p == '^') {
                p++;
                expn = 0;
                while (isdigit(*p)) {
                    expn = expn * 10 + (*p - '0');
                    p++;
                }
            } else {
                expn = 1;
            }
        } else {
            expn = 0;
        }

        insertPoly(head, coef, expn);
    }
}

LinkedPoly createNode() {
    LinkedPoly newNode = (LinkedPoly)malloc(sizeof(PolyNode));
    newNode->data.coef = 0;
    newNode->data.expn = 0;
    newNode->next = newNode;
    return newNode;
}

void insertPoly(LinkedPoly* head, int coef, int expn)
{
    if (coef == 0) {
        return; 
    }

    LinkedPoly newNode = createNode();
    newNode->data.coef = coef;
    newNode->data.expn = expn;

    LinkedPoly current = (*head)->next;
    LinkedPoly prev = *head;

    while (current != *head && current->data.expn > expn) {
        prev = current;
        current = current->next;
    }

    if (current != *head && current->data.expn == expn) {
        current->data.coef += coef;
        if (current->data.coef == 0) { 
            prev->next = current->next;
            free(current);
        }
        free(newNode);
        return;
    }

    newNode->next = current;
    prev->next = newNode;
}

void printPoly(LinkedPoly head)
{
    LinkedPoly current = head->next;

    if (current == head) {
        printf("0\n");
        return;
    }

    while (current != head) {
        if (current->data.coef > 0 && current != head->next) {
            printf(" + ");
        } else if (current->data.coef < 0) {
            if (current != head->next) {
                printf(" - ");
            } else {
                printf("- ");
            }
        } 
        if (current->data.coef == 0) {
            current = current->next;
            continue;
        }
        if (current->data.expn == 0) {
            printf("%d", abs(current->data.coef));
        } else if (current->data.expn == 1) {
            printf("%dx", abs(current->data.coef));
        } else {
            printf("%dx^%d", abs(current->data.coef), current->data.expn);
        }
        current = current->next;
    }
    printf("\n");
}

void derivation(LinkedPoly* head)
{
    LinkedPoly current = (*head)->next;
    LinkedPoly prev = *head;

    while (current != *head) {
        if (current->data.expn == 0) {
            prev->next = current->next;
            free(current);
            current = prev->next;
        } else {
            current->data.coef *= current->data.expn;
            current->data.expn--;
            prev = current;
            current = current->next;
        }
    }
}