// @siliconx
// 2017-05-23 19:58:43
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define OK 0
#define ERROR -1
#define COUNT 6
#define N 99

int bubble_sort(int*, int);  // 冒泡排序
int insert_sort(int*, int);  // 插入排序
int select_sort(int *, int);  // 选择排序
int shell_sort(int*, int);  //  希尔排序
int quick_sort(int*, int, int);  // 快速排序
int partition(int*, int, int);  // 快速排序的分割函数

int heap_sort(int*, int);  // 堆排序
int max_heapify(int*, int, int);  // 保持最大堆的性质

int reset(void);  // 初始化
int swap(int*, int, int);  // 交换数组元素
int *gen_array(int);
int show_array(int*, int);  // 输出数组
int shuffle_array(int*, int);  // 打乱数组

int compare_count, move_count;  // 比较次数、移动次数
char names[COUNT][N] = {
    "bubble_sort", "insert_sort",
    "select_sort", "shell_sort",
    "quick_sort", "heap_sort"
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("one intger argument expected(as the size of array)\nfor example: `./sorting 99`\n");
        return 0;
    }

    int size = atoi(argv[1]);
    time_t now, end;
    double used_time;
    int n = 0;
    int *array  = gen_array(size);

    for (int i=0; i<COUNT; i++) {
        printf("shuffling array...\n");
        shuffle_array(array, size);
        // show_array(array, size);
        reset();
        now = clock();
        printf("%s running...\n", names[i]);
        switch(i) {
            case 0: {
                bubble_sort(array, size);
                break;
            }
            case 1: {
                select_sort(array, size);
                break;
            }
            case 2: {
                insert_sort(array, size);
                break;
            }
            case 3: {
                shell_sort(array, size);
                break;
            }
            case 4: {
                quick_sort(array, 0, size-1);
                break;
            }
            case 5: {
                heap_sort(array, size);
                break;
            }
            default: {
                printf("Bye!\n");
                return OK;
            }
        }
        end = clock();
        used_time = (end - now) * 1.0 / CLOCKS_PER_SEC;
        printf("done!\nused time: %lf s, move count: %d, compare count: %d\n", used_time, move_count, compare_count);
        // show_array(array, size);
        printf("================================================================\n");
    }
    printf("\n");
}

int bubble_sort(int *array, int size) {
    int temp;
    for (int i=0;i<size;i++) {
        for (int j=1;j<size-i;j++) {
            move_count++;
            if (array[j-1] > array[j]) {
                compare_count++;

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
        compare_count++;
        for (int j=i; j > 0 && array[j] < array[j-1]; j--) {
            move_count++;
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
            compare_count++;
            if (array[j] < min) {
                move_count++;
                min = array[j];
                min_index = j;
            }
        }

        compare_count++;
        if (min_index > i) {\
            move_count++;
            swap(array, i, min_index);
        }
    }
}

int shell_sort(int *array, int size) {
    int gap;
    for (gap = size / 3; gap >= 1; gap /= 3) {
        for (int i = gap; i < size; i++) {
            compare_count++;
            for (int j = i; j >= gap && array[j] < array[j-gap]; j -= gap) {
                move_count++;

                swap(array, j, j-gap);
            }
        }
    }
    return OK;
}

int quick_sort(int *array, int low, int high) {
    if (low < high) {
        compare_count++;
        int pivot = partition(array, low, high);
        quick_sort(array, low, pivot - 1);
        quick_sort(array, pivot + 1, high);
    }
    return OK;
}

int partition(int *array, int low, int high) {
    int pivot = array[low];  // 切分元素
    int i = low, j = high + 1;  // 左右扫描指针
    while (1) {  // 左右扫描，检查扫描是否结束并交换元素
        while (array[++i] < pivot) {
            compare_count++;
            if (i >= high) {
                break;
            }
        }
        while (array[--j] > pivot) {
            compare_count++;
            if (j <= low) {
                break;
            }
        }
        if (i >= j) {
            break;
        }
        move_count++;
        swap(array, i, j);
    }
    swap(array, low, j);  // 将pivot = array[j]放入正确的位置
    return j;  // 返回中点位置
}

int heap_sort(int *array, int size) {
    int i;
    //  初始化，i从最后一个父节点开始调整
    for (i = size / 2 - 1; i >= 0; i--)
        max_heapify(array, i, size - 1);
    // 先将第一个元素和已排好的元素前一位做交换在重新调整
    for (i = size - 1; i > 0; i--) {
        move_count++;
        swap(array, 0, i);
        max_heapify(array, 0, i - 1);
    }
    return OK;
}

int max_heapify(int *array, int start, int end) {
    //  建立父节点指针和子节点指针
    int parent = start;
    int child = parent * 2 + 1;
    while (child <= end) {  // 若子节点指针在范围内才做比较
        compare_count++;
        if (child + 1 <= end && array[child] < array[child + 1])  // 先比较两个子节点大小， 选择最大的
            child++;
        compare_count++;
        if (array[parent] > array[child])
            return OK;
        else {
            move_count++;
            swap(array, parent, child);
            parent = child;
            child = parent * 2 + 1;
        }
    }
    return OK;
}

int *gen_array(int size) {
    srand(time(NULL));
    int *array = (int *) malloc(sizeof(int) * size);
    for (int i=0; i<size; i++) {
        array[i] = rand() % size;
    }
    return array;
}

int reset(void) {
    move_count = 0;
    compare_count = 0;
    return OK;
}

int shuffle_array(int *array, int size) {
    srand(time(NULL));
    int a;
    for (int i=0;i<size / 2;i++) {
        a = rand() % size;
        swap(array, a, size - a - 1);
    }
    return OK;
}

int show_array(int *array, int size) {
    for (int i=0;i<size;i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int swap(int *array, int a, int b) {
    if (a == b) {
        return OK;
    }
    int temp = array[a];
    array[a] = array[b];
    array[b] = temp;
    return OK;
}
