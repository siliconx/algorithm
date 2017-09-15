// @silicon
// 2017-04-06 13:40:13
#include <stdio.h>
#define N 8
#define TRUE 1
#define FALSE 0
int can_place();
int place();
int output();

int sum = 0;

int main(void) {
    int matrix[N][N];
    for (int i=0;i<N;i++) {
        for (int j=0;j<N;j++) {
            matrix[i][j] = 0;
        }
    }
    // 从第0行开始放置皇后
    place(matrix, 0);
    printf("sum: %d\n", sum);
    return 0;
}

int can_place(int matrix[N][N], int row, int col) {
    // 检查当前位置是否可以放置皇后
    if (row == 0) {
        return TRUE;
    }
    int i, j;

    // 上下检查
    for (i=0;i<N;i++) {
        if (matrix[i][col] == 1) {
            return FALSE;
        }
    }


    // 左右检查
    for (j=0;j<N;j++) {
        if (matrix[row][j] == 1) {
            return FALSE;
        }
    }

    // 左上
    for (i=row, j=col;i>=0 && j>=0;i--, j--) {
        if (matrix[i][j] == 1) {
            return FALSE;
        }
    }

    // 右上
    for (i=row, j=col;i<N && j>=0; i++, j--) {
        if (matrix[i][j] == 1) {
            return FALSE;
        }
    }

    // 左下
    for (i=row, j=col;i>=0 && j<N;i--, j++) {
        if (matrix[i][j] == 1) {
            return FALSE;
        }
    }

    // 右下
    for (i=row, j=col;i<N && j<N;i++, j++) {
        if (matrix[i][j] == 1) {
            return FALSE;
        }
    }

    return TRUE;
}

int place(int matrix[N][N], int row) {
    // 从当前行(第row行)，遍历每一列是否可以放置皇后
    for (int j=0;j<N;j++) {
        if (can_place(matrix, row, j) == TRUE) {
            matrix[row][j] = 1;
            if (row == N - 1) {
                // 到达最后一行, 获得一个解
                sum++;
                printf("No.%d\n", sum);
                output(matrix);
            } else {
                // 当前列可以放置皇后，且未到达最后一行，在下一行尝试放置皇后, 继续搜索求解
                place(matrix, row + 1);
            }
            matrix[row][j] = 0;  // 回溯，取回该列的皇后，向下一列进行尝试
        }
    }
    return 0;
}

int output(int matrix[N][N]) {
    // 输出棋盘布局
    for (int i=0;i<N;i++) {
        for (int j=0;j<N;j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}