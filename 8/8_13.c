#include <stdio.h>
#include <stdlib.h>

struct MemBlock {
    int tag;
    int begin;
    int length;
};

int main() {
    int data[3];
    struct MemBlock *blocks[100];
    int blockCount = 0;

    // 分配内存
    for (int i = 0; i < 100; i++) {
        blocks[i] = malloc(sizeof(struct MemBlock));
    }

    while (scanf("%d %d %d", &data[0], &data[1], &data[2]) != EOF) {
        if (data[0] == 1) {
            int j;
            for (j = 0; j < blockCount; j++) {
                int b = blocks[j]->begin;
                int e = blocks[j]->begin + blocks[j]->length;
                int nb = data[1];
                int ne = data[1] + data[2];

                if (nb <= b && ne >= b && ne <= e) {
                    blocks[j]->length = e - nb;
                    blocks[j]->begin = nb;
                    break;
                } else if (nb <= b && ne >= b && ne >= e) {
                    blocks[j]->length = ne - b;
                    blocks[j]->begin = nb;
                    break;
                }
            }
            if (j == blockCount) {
                blocks[j]->begin = data[1];
                blocks[j]->length = data[2];
                blocks[j]->tag = 0;
                blockCount++;
            }
        } else if (data[0] == 0) {
            blocks[blockCount]->tag = 0;
            blocks[blockCount]->length = data[2];
            blocks[blockCount]->begin = data[1];
            blockCount++;
        }
    }

    // 冒泡排序按begin升序
    for (int j = blockCount - 1; j > 0; j--) {
        for (int k = 0; k < j; k++) {
            if (blocks[k]->begin > blocks[k + 1]->begin) {
                struct MemBlock *tmp = blocks[k];
                blocks[k] = blocks[k + 1];
                blocks[k + 1] = tmp;
            }
        }
    }

    // 合并重叠区间
    for (int j = 1; j < blockCount; j++) {
        int end0 = blocks[0]->begin + blocks[0]->length;
        if (blocks[j]->begin <= end0) {
            blocks[j]->tag = 1;
            int newEnd = blocks[j]->begin + blocks[j]->length;
            if (newEnd > end0) {
                blocks[0]->length = newEnd - blocks[0]->begin;
            }
        }
    }

    // 输出未合并的区间
    for (int j = 0; j < blockCount; j++) {
        if (blocks[j]->tag == 0) {
            printf("%d %d %d\n", blocks[j]->tag, blocks[j]->begin, blocks[j]->length);
        }
    }

    // 释放内存
    for (int i = 0; i < 100; i++) {
        free(blocks[i]);
    }

    return 0;
}
