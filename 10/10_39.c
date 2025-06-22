#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    static int arr[200000];
    static int temp[500]; 
    
    char line[2000000];
    int n = 0, m = 0;
    
    fgets(line, sizeof(line), stdin);
    char* token = strtok(line, " \n");
    while (token != NULL) {
        arr[n++] = atoi(token);
        token = strtok(NULL, " \n");
    }
    m = n;
    
    fgets(line, sizeof(line), stdin);
    token = strtok(line, " \n");
    while (token != NULL) {
        arr[n++] = atoi(token);
        token = strtok(NULL, " \n");
    }
    
    int len1 = m;
    int len2 = n - m;
    
    if (len1 <= len2) {
        for (int i = 0; i < len1; i++) {
            temp[i] = arr[i];
        }
        
        int i = 0, j = m, k = 0;
        while (i < len1 && j < n) {
            if (temp[i] <= arr[j]) {
                arr[k++] = temp[i++];
            } else {
                arr[k++] = arr[j++];
            }
        }
        
        while (i < len1) arr[k++] = temp[i++];
        while (j < n) arr[k++] = arr[j++];
    } else {
        for (int i = 0; i < len2; i++) {
            temp[i] = arr[m + i];
        }
        
        int i = m - 1, j = len2 - 1, k = n - 1;
        while (i >= 0 && j >= 0) {
            if (arr[i] > temp[j]) {
                arr[k--] = arr[i--];
            } else {
                arr[k--] = temp[j--];
            }
        }
        
        while (j >= 0) arr[k--] = temp[j--];
    }
    
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(" ");
    }
    printf("\n");
    
    return 0;
}