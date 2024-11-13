//
// Created by ElegyNine on 24-11-12.
//

//将一个数组调整成一个堆
void adjustHeap(int a[], int k, int len) {
    //对以k为根的子树进行调整
    int tmp = a[k];
    for (int i = 2 * k; i <= len; i *= 2) {
        if (i < len && a[i] < a[i + 1]) {
            i++;
        }
        if (tmp > a[i])break;
        else {
            a[k] = a[i];
            k = i;
        }
    }
    a[k] = tmp;
}

//用一个数组建一个大顶堆
void BuildMaxHeap(int a[], int len) {
    for (int i = len / 2; i ; i--) {
        adjustHeap(a, i, len);
    }
}



