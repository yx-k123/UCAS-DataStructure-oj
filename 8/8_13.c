#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct word {  
    union {
        struct word *llink;
        struct word *uplink; 
    };
    int tag; 
    int size;
    int addr;    
    struct word *rlink;
} WORD, head, foot, *Space;

void insert_free_space(Space *head, int tag, int addr, int size);
void merge_free_space(Space *head);
void print_free_blocks(Space head);
Space FootLoc(Space p);

int main()
{
    Space head = NULL;
    int tag, addr, size;
    char line[100];
    int phase = 1;  

    while (fgets(line, sizeof(line), stdin)) {
        if (line[0] == '\n' || line[0] == '\0') {
            phase = 2;  
            continue;
        }
        
        if (sscanf(line, "%d %d %d", &tag, &addr, &size) == 3) {
            if (phase == 1 && tag == 0) {
                insert_free_space(&head, tag, addr, size);
            } else if (phase == 2 && tag == 1) {
                insert_free_space(&head, 0, addr, size);  
            }
        }
    }
    merge_free_space(&head);
    print_free_blocks(head);
    return 0;
}

void insert_free_space(Space *head, int tag, int addr, int size) {
    Space new_space = (Space)malloc(sizeof(WORD));
    if (new_space == NULL) return;
    
    new_space->tag = tag;
    new_space->size = size;
    new_space->addr = addr;
    new_space->llink = NULL;
    new_space->rlink = NULL;

    if (*head == NULL) {
        *head = new_space;
    } else {
        Space current = *head;
        Space prev = NULL;
        
        while (current != NULL && current->addr < addr) {
            prev = current;
            current = current->rlink;
        }
        
        if (prev == NULL) {
            new_space->rlink = *head;
            (*head)->llink = new_space;
            *head = new_space;
        } else {
            new_space->rlink = current;
            new_space->llink = prev;
            prev->rlink = new_space;
            if (current != NULL) {
                current->llink = new_space;
            }
        }
    }
}

void merge_free_space(Space *head) {
    Space current = *head;
    
    while (current != NULL && current->rlink != NULL) {
        Space next = current->rlink;
        
        if (current->addr + current->size == next->addr) {
            current->size += next->size;
            current->rlink = next->rlink;
            if (next->rlink != NULL) {
                next->rlink->llink = current;
            }
            free(next);
        } else {
            current = current->rlink;
        }
    }
}

void print_free_blocks(Space head) {
    Space current = head;
    while (current != NULL) {
        printf("%d %d %d\n", current->tag, current->addr, current->size);
        current = current->rlink;
    }
}

Space FootLoc(Space p) {
    char *q; 
    Space f;
    q = (char *)p;
    f = (Space)( q + sizeof(char)*p->size - sizeof(foot));
    return f;
}