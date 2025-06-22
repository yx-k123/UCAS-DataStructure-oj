#include <stdio.h>
#include <string.h>

int main() {
    char S[1000], T[100], V[100];
    char result[2000] = "";  
    
    scanf("%s %s %s", S, T, V);
    
    int sLen = strlen(S);
    int tLen = strlen(T);
    int vLen = strlen(V);
    
    int i = 0, j = 0;
    
    while (i < sLen) {
        int match = 1;
        for (int k = 0; k < tLen && i + k < sLen; k++) {
            if (S[i + k] != T[k]) {
                match = 0;
                break;
            }
        }
        
        if (match && tLen > 0) {
            for (int k = 0; k < vLen; k++) {
                result[j++] = V[k];
            }
            i += tLen;
        } else {
            result[j++] = S[i++];
        }
    }
    
    result[j] = '\0'; 
    printf("%s\n", result);
    
    return 0;
}