//
// Created by leo on 24-11-4.
//


typedef int Ty;


//直接插入排序
void InsertSort(Ty a[],int n) {
    for(int i = 2, j;i <= n;i++) {
        if(a[i] < a[i - 1]) {
            Ty tmp = a[i];
            for(j = i - 1;tmp < a[j];--j) {
                a[j + 1] = a[j];
            }
            a[j + 1] = tmp;
        }
    }
}

//折半插入排序
void Insert_Sort(Ty a[],int n) {
    for(int i = 2;i <= n;i++) {
        Ty tmp = a[i];
        int low = 1,high = i - 1;
        while(low <= high) {
            int mid = (low + high) / 2;
            if(a[mid] > tmp)high = mid - 1;
            else high = mid + 1;
        }
        for(int j = i - 1;j >= high ;j--) {
            a[j + 1] = a[j];
        }
        a[high + 1] = tmp;
    }
}


//希尔排序
void ShellSort(Ty a[],int n) {
    for(int _k = n / 2;_k >= 1; _k = _k / 2) {
        //_k 为增量
        for(int i = _k + 1;i <= n;i++) {
            if(a[i] < a[i - _k]) {
                int tmp = a[i], j;
                for(j = i - _k;j > 0 && tmp < a[j] ; j -= _k)
                    a[j + _k] = a[j];
                a[j + _k] = tmp;
            }
        }
    }
}

