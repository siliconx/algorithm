// @siliconx
// 2017-05-23 19:58:43
#include <stdio.h>

#define OK 0
#define ERROR -1

int bubble_sort(int*, int);  // 冒泡排序
int insert_sort(int*, int);  // 插入排序
int select_sort(int *, int);  // 选择排序
int shell_sort(int*, int);

int swap(int*, int, int);  // 交换数组元素
int output_array(int*, int);  // 输出数组

int main(void) {
    int size;
    scanf("%d", &size);
    printf("%d>>1=%d\n", size, size>>1);
    int array[size];
    for (int i=0;i<size;i++) {
        scanf("%d", &array[i]);
    }
    // bubble_sort(array, size);
    // select_sort(array, size);
    insert_sort(array, size);
    // shell_sort(array, size);
    output_array(array, size);
}

int bubble_sort(int *array, int size) {
    int temp;
    for (int i=0;i<size;i++) {
        for (int j=1;j<size;j++) {
            if (array[j-1] > array[j]) {
                swap(array, j-1, j);
            }
        }
    }
    return OK;
}

int insert_sort(int *array, int size) {
    int index, temp;
    for (int i=1;i<size;i++) {
        // insert
        for (int j=i; j > 0 && array[j] < array[j-1];j--) {
            swap(array, j, j-1);
        }
    }
    return OK;
}

int select_sort(int *array, int size) {
    if (size <= 0) {
        return ERROR;
    }

    int temp;
    int min_index;
    int min;

    for (int i=0;i<size;i++) {
        min_index = i;
        min = array[min_index];
        // 选择剩余元素中的最小值以及对应的下标
        for (int j=i;j<size;j++) {
            if (array[j] < min) {
                min = array[j];
                min_index = j;
            }
        }
        if (min_index > i) {
            // temp = array[min_index];
            // array[min_index] = array[i];
            // array[i] = temp;
            swap(array, i, min_index);
        }
    }
}

int shell_sort(int *array, int size) {
    int index, temp, gap;
    for (gap = size / 3; gap >= 1; gap /= 3) {
        for (int i = gap; i < size; i++) {
            for (int j = i; j >= gap && array[j] < array[j-gap]; j -= gap) {
                swap(array, j, j-gap);
            }
        }
    }
    return OK;
}

int output_array(int *array, int size) {
    for (int i=0;i<size;i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int swap(int *array, int a, int b) {
    int temp = array[a];
    array[a] = array[b];
    array[b] = temp;
    return OK;
}

