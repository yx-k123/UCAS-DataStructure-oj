#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

struct Partner {
    int k;
    int position[MAX_SIZE];
};

int numbers_get_line(int s[MAX_SIZE]);
void Init(struct Partner *line[MAX_SIZE]);
void build(struct Partner *line[MAX_SIZE]);
int power(int n);
void set_free(struct Partner *line[MAX_SIZE]);

int main() {
    struct Partner *line[MAX_SIZE];
    Init(line);
    build(line);
    set_free(line);

    for (int i = 3; i < 4; i++) {
        if (line[i]->position[1] > line[i]->position[3]) {
            int temp = line[i]->position[1];
            line[i]->position[1] = line[i]->position[3];
            line[i]->position[3] = temp;
        }
    }

    for (int i = 0; i < MAX_SIZE; i++) {
        if (line[i]->position[0] != -1) {
            int tag = 0;
            int print[MAX_SIZE];
            int t = 0;
            print[t++] = i;
            for (int k = 0; k < MAX_SIZE; k++) {
                if (line[i]->position[k] != -1 && line[i]->position[k] != -2) {
                    print[t++] = line[i]->position[k];
                    tag = 1;
                }
            }
            if (tag) {
                for (int u = 0; u < t; u++) {
                    printf("%d", print[u]);
                    if (u < t - 1)
                        printf(" ");
                }
                printf("\n");
            }
        }
    }

    // 释放内存
    for (int i = 0; i < MAX_SIZE; i++) {
        free(line[i]);
    }

    return 0;
}

void Init(struct Partner *line[MAX_SIZE]) {
    for (int i = 0; i < MAX_SIZE; i++) {
        line[i] = malloc(sizeof(struct Partner));
        line[i]->k = i;
        for (int j = 0; j < MAX_SIZE; j++) {
            line[i]->position[j] = -1;
        }
    }
}

int numbers_get_line(int s[MAX_SIZE]) {
    int c, i = 0, j = 0;
    int state = 1;
    int number = 0;

    while ((c = getchar()) != EOF && c != '\n' && c != ';') {
        if (c == '-') {
            state = -1;
        } else if (c >= '0' && c <= '9') {
            if (number == 0) {
                number = 1;
                s[j++] = (c - '0') * state;
            } else {
                number++;
                int temp = s[j - 1] * 10 + (c - '0') * state;
                s[j - 1] = temp;
            }
        } else {
            number = 0;
            state = 1;
        }
    }
    return j;
}

void build(struct Partner *line[MAX_SIZE]) {
    int data[MAX_SIZE];
    int count;
    while ((count = numbers_get_line(data)) != 0) {
        int idx = data[0];
        for (int k = 0; k < count - 1; k++) {
            line[idx]->position[k] = data[k + 1];
        }
    }
}

int power(int n) {
    int sum = 1;
    for (int i = 0; i < n; i++) {
        sum *= 2;
    }
    return sum;
}

void set_free(struct Partner *line[MAX_SIZE]) {
    int data[MAX_SIZE];
    int count;
    while ((count = numbers_get_line(data)) != 0) {
        int idx = data[0];
        if (data[1] % power(idx + 1) == 0) {
            int tag = 0;
            for (int k = 0; line[idx]->position[k] != -1; k++) {
                if (line[idx]->position[k] == data[1] + power(idx)) {
                    int l = 0;
                    while (line[idx + 1]->position[l] != -1) l++;
                    line[idx + 1]->position[l] = data[1];
                    line[idx]->position[k] = -2;
                    tag = 1;
                    break;
                }
            }
            if (!tag) {
                int l = 0;
                while (line[idx]->position[l] != -1) l++;
                line[idx]->position[l] = data[1];
            }
        } else {
            int tag = 0;
            for (int k = 0; line[idx]->position[k] != -1; k++) {
                if (line[idx]->position[k] == data[1] - power(idx)) {
                    int l = 0;
                    while (line[idx + 1]->position[l] != -1) l++;
                    line[idx + 1]->position[l] = line[idx]->position[k];
                    line[idx]->position[k] = -2;
                    tag = 1;
                    break;
                }
            }
            if (!tag) {
                int l = 0;
                while (line[idx]->position[l] != -1) l++;
                line[idx]->position[l] = data[1];
            }
        }
    }

    for (int i = 0; i < MAX_SIZE; i++) {
        if (line[i]->position[0] != -1 && line[i]->position[0] != -2) {
            if ((line[i]->position[0] == 0 && line[i]->position[1] == power(i)) ||
                (line[i]->position[1] == 0 && line[i]->position[0] == power(i))) {
                line[i + 1]->position[0] = 0;
                line[i]->position[1] = -2;
                line[i]->position[0] = -2;
            }
        }
        if (line[i]->position[0] != -1 && line[i]->position[0] != -2) {
            if ((line[i]->position[2] % power(i + 1) == 0 &&
                 line[i]->position[0] == power(i) + line[i]->position[2])) {
                int l = 0;
                while (line[i + 1]->position[l] != -1) l++;
                line[i + 1]->position[l] = line[i]->position[2];
                line[i]->position[2] = -2;
                line[i]->position[0] = -2;
            }
        }
    }
}