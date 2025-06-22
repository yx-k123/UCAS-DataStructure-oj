#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    LEAF,    
    BRANCH   
} NodeKind;

typedef char* KeysType;

typedef struct Record {
    KeysType key;
    int value;
} Record;

typedef struct TrieNode {
    NodeKind kind;
    union {
        struct { KeysType K; Record *infoptr; } lf;   
        struct { struct TrieNode *ptr[27]; int num; } bh;   
    };
} TrieNode, *TrieTree;

void insert(TrieTree *root, KeysType key, int value);
int search(TrieTree *root, KeysType key);
void delete(TrieTree *root, KeysType key);
int char_to_index(char c);
Record* create_record(KeysType key, int value);
TrieNode* creat_branch_node();
TrieNode* create_leaf_node(KeysType key, int value);
void print_trie_helper(TrieNode *node, char *prefix, int depth, int is_last);
void print_trie(TrieTree *root);
void print_trie_simple(TrieTree *root);
void print_trie_simple_helper(TrieNode *node, char *path, int depth);
void traverse_all_keys(TrieTree *root);
void traverse_keys_helper(TrieNode *node, char *path, int depth);

int main() {
    TrieTree root = NULL;
    int operation;
    char key[1000]; 
    
    while (scanf("%d %s", &operation, key) == 2) {
        switch (operation) {
            case 1:  
                insert(&root, key, 1);  
                // print_trie(&root);
                break;
                
            case 2:  
                delete(&root, key);
                // print_trie(&root);
                break;
            
            case 3:
                if (search(&root, key) != -1) {
                    printf("True\n");
                } else {
                    printf("False\n");
                }
                break;
                
            default:
                break;
        }
    }
    
    return 0;
}

int char_to_index(char c) {
    return c - 'a' + 1; 
}

Record* create_record(KeysType key, int value) {
    Record *new_record = (Record *)malloc(sizeof(Record));
    new_record->key = (char*)malloc(strlen(key) + 1);
    strcpy(new_record->key, key); 
    new_record->value = value;
    return new_record;
}

TrieNode* creat_branch_node() {
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
    node->kind = BRANCH;
    for (int i = 0; i < 27; i++) {
        node->bh.ptr[i] = NULL;
    }
    node->bh.num = 0;
    return node;
}

TrieNode* create_leaf_node(KeysType key, int value) {
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
    node->kind = LEAF;
    node->lf.K = (char*)malloc(strlen(key) + 1);
    strcpy(node->lf.K, key);
    node->lf.infoptr = create_record(key, value);
    return node;
}

void insert(TrieTree *root, KeysType key, int value) {
    if (*root == NULL) {
        *root = creat_branch_node();
    }

    int length = strlen(key);
    TrieNode *current = *root;
    TrieNode *pre_current = NULL;

    for (int i = 0; i < length; i++) {
        int index = char_to_index(key[i]);
        if (current->kind == BRANCH) {
            if (current->bh.ptr[index] == NULL) {
                if (i == length - 1) {
                    current->bh.ptr[index] = create_leaf_node(key, value);
                    current->bh.num++;
                    return;
                }
                TrieNode *new_branch_node = creat_branch_node();
                current->bh.ptr[index] = new_branch_node;
                current->bh.num++;
            } else {
                if (i == length - 1) {
                    current->bh.ptr[0] = create_leaf_node(key, value);
                    current->bh.num++;
                    return;
                }
            }
            pre_current = current;
            current = current->bh.ptr[index];
        } else if (current->kind == LEAF) {
            char *existing_key = current->lf.K;
            int pre_index = 0;
            if (i>0) pre_index = char_to_index(key[i-1]);
            if (i == length - 1) {
                if (strlen(existing_key) == length) current->lf.infoptr->value = value;
                else {
                    TrieNode *new_branch = creat_branch_node();
                    pre_current->bh.ptr[pre_index] = new_branch;
                    int existing_next_index = char_to_index(existing_key[i]);
                    new_branch->bh.ptr[0] = current;
                    new_branch->bh.num++;
                    new_branch->bh.ptr[index] = create_leaf_node(key, value);
                    new_branch->bh.num++;
                }
                return;
            }
            
            TrieNode *new_branch = creat_branch_node();
            pre_current->bh.ptr[pre_index] = new_branch;

            if (strlen(existing_key) > i) {
                int existing_next_index = char_to_index(existing_key[i]);
                new_branch->bh.ptr[existing_next_index] = current;
                new_branch->bh.num++;
            } else {
                new_branch->bh.ptr[0] = current;
                new_branch->bh.num++;
            }
            
            current = new_branch;
        }
    }
}

int search(TrieTree *root, KeysType key) {
    if (*root == NULL) return -1;

    int length = strlen(key);
    TrieNode *current = *root;

    for (int i = 0; i < length; i++) {
        int index = char_to_index(key[i]);
        if (current->kind == BRANCH) {
            if (current->bh.ptr[index] == NULL) {
                return -1; 
            }
            current = current->bh.ptr[index];
        } else {
            return -1; 
        }
    }

    if (current->kind == LEAF && strcmp(current->lf.K, key) == 0) {
        return current->lf.infoptr->value;
    }

    if (current->kind == BRANCH && current->bh.ptr[0] != NULL && 
        current->bh.ptr[0]->kind == LEAF && 
        strcmp(current->bh.ptr[0]->lf.K, key) == 0) {
        return current->bh.ptr[0]->lf.infoptr->value;
    }

    return -1;
}

void delete(TrieTree *root, KeysType key) {
    if (*root == NULL) return;

    int length = strlen(key);
    TrieNode *current = *root;
    TrieNode *parent = NULL;
    int parent_index = -1;

    for (int i = 0; i < length; i++) {
        int index = char_to_index(key[i]);
        
        if (current->kind == BRANCH) {
            if (current->bh.ptr[index] == NULL) {
                return; 
            }
            parent = current;
            parent_index = index;
            current = current->bh.ptr[index];
        } else {
            return;  
        }
    }

    TrieNode *target_leaf = NULL;
    TrieNode *leaf_parent = NULL;
    int leaf_index = -1;
    
    if (current->kind == LEAF && strcmp(current->lf.K, key) == 0) {
        target_leaf = current;
        leaf_parent = parent;
        leaf_index = parent_index;
    } else if (current->kind == BRANCH && current->bh.ptr[0] != NULL && 
               current->bh.ptr[0]->kind == LEAF && 
               strcmp(current->bh.ptr[0]->lf.K, key) == 0) {
        target_leaf = current->bh.ptr[0];
        leaf_parent = current;
        leaf_index = 0;
    } else {
        return;  
    }

    free(target_leaf->lf.K);
    free(target_leaf->lf.infoptr->key);
    free(target_leaf->lf.infoptr);
    free(target_leaf);
    
    if (leaf_parent != NULL) {
        leaf_parent->bh.ptr[leaf_index] = NULL;
        leaf_parent->bh.num--;
    } else {
        *root = NULL;
    }
}

void print_trie_helper(TrieNode *node, char *prefix, int depth, int is_last) {
    if (node == NULL) return;
    
    for (int i = 0; i < depth - 1; i++) {
        printf("    ");
    }
    if (depth > 0) {
        printf("%s", is_last ? "└── " : "├── ");
    }
    
    if (node->kind == LEAF) {
        printf("[LEAF] \"%s\" (value: %d)\n", node->lf.K, node->lf.infoptr->value);
    } else if (node->kind == BRANCH) {
        printf("[BRANCH] (children: %d)\n", node->bh.num);
        
        int non_null_count = 0;
        for (int i = 0; i < 27; i++) {
            if (node->bh.ptr[i] != NULL) {
                non_null_count++;
            }
        }
        
        int current_count = 0;
        for (int i = 0; i < 27; i++) {
            if (node->bh.ptr[i] != NULL) {
                current_count++;
                char child_char = (i == 0) ? '$' : ('a' + i - 1);  
                
                for (int j = 0; j < depth; j++) {
                    printf("    ");
                }
                printf("%s'%c':\n", (current_count == non_null_count) ? "└── " : "├── ", child_char);
                
                print_trie_helper(node->bh.ptr[i], prefix, depth + 1, current_count == non_null_count);
            }
        }
    }
}

void print_trie(TrieTree *root) {
    printf("\n=== Trie Tree Structure ===\n");
    if (*root == NULL) {
        printf("Empty tree\n");
        return;
    }
    
    char prefix[1000] = "";
    print_trie_helper(*root, prefix, 0, 1);
    printf("===========================\n\n");
}

void print_trie_simple(TrieTree *root) {
    printf("\n=== Trie Tree (Simple) ===\n");
    if (*root == NULL) {
        printf("Empty tree\n");
        return;
    }
    
    print_trie_simple_helper(*root, "", 0);
    printf("==========================\n\n");
}

void print_trie_simple_helper(TrieNode *node, char *path, int depth) {
    if (node == NULL) return;
    
    if (node->kind == LEAF) {
        printf("Depth %d: \"%s\" -> %d\n", depth, node->lf.K, node->lf.infoptr->value);
    } else if (node->kind == BRANCH) {
        if (node->bh.ptr[0] != NULL && node->bh.ptr[0]->kind == LEAF) {
            printf("Depth %d: \"%s\" -> %d (at $)\n", depth, 
                   node->bh.ptr[0]->lf.K, node->bh.ptr[0]->lf.infoptr->value);
        }
        
        for (int i = 1; i < 27; i++) {
            if (node->bh.ptr[i] != NULL) {
                char new_path[1000];
                sprintf(new_path, "%s%c", path, 'a' + i - 1);
                print_trie_simple_helper(node->bh.ptr[i], new_path, depth + 1);
            }
        }
    }
}

void traverse_all_keys(TrieTree *root) {
    printf("\n=== All Keys in Trie ===\n");
    if (*root == NULL) {
        printf("No keys found\n");
        return;
    }
    
    char path[1000] = "";
    traverse_keys_helper(*root, path, 0);
    printf("========================\n\n");
}

void traverse_keys_helper(TrieNode *node, char *path, int depth) {
    if (node == NULL) return;
    
    if (node->kind == LEAF) {
        printf("Key: \"%s\", Value: %d\n", node->lf.K, node->lf.infoptr->value);
    } else if (node->kind == BRANCH) {
        if (node->bh.ptr[0] != NULL && node->bh.ptr[0]->kind == LEAF) {
            printf("Key: \"%s\", Value: %d\n", 
                   node->bh.ptr[0]->lf.K, node->bh.ptr[0]->lf.infoptr->value);
        }

        for (int i = 1; i < 27; i++) {
            if (node->bh.ptr[i] != NULL) {
                path[depth] = 'a' + i - 1;
                path[depth + 1] = '\0';
                traverse_keys_helper(node->bh.ptr[i], path, depth + 1);
            }
        }
    }
}