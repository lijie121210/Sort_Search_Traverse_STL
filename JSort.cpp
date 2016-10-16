//
//  JSort.cpp
//  Sort_Search_Traverse_STL
//
//  Created by jie on 2016/10/14.
//  Copyright © 2016年 jie. All rights reserved.
//

#include <stdio.h>
#include <vector>

using namespace std;

class JSort {
    // dataset
    vector<int> arr;
    // size of dataset == array.size()
    int n;
    
    int quick_partition(/*const int *arr, */int low/* = 0*/, int high/* = n*/);
    
    void heap_adjust(int s, int m);
public:
    /* 
     * designed constructure
     * array: Initialization data set
     */
    inline JSort(vector<int> array) :arr(array), n((int)array.size()) {};
    
    // basic sort algorithm
    
    void selectSort();
    
    void bubbleSort();
    
    void insertSort();
    
    void shellSort();
    
    // 两种实现 flag == 0 || flag == 1
    void quickSort(/*const int *arr, */int low/* = 0*/, int high/* = n*/, int flag = 0);
    
    void headSort();
};

void JSort::selectSort() {
    int i = 0,
        j = 0,
        tmp = 0, // 用于交换元素
        k = 0; // 保存从i到n-1的最小值索引
    for (i=0; i<n; ++i) {
        for (k=i, j=i+1; j<n; ++j) {
            if (arr[j] < arr[k]) {
                k=j;
            }
        }
        if (k!=i) {
            tmp = arr[i];
            arr[i] = arr[k];
            arr[k] = tmp;
        }
    }
}

void JSort::bubbleSort() {
    int i = 0,
        j = (int)n - 1,
        tmp = 0; // 用于交换元素
    bool changed = true;
    
    for (i=0; i<n-1 && changed; ++i) {
        
        changed = false;
        
        for (; j>i; --j) {
            if (arr[j]<arr[j-1]) {
                tmp = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = tmp;
                
                changed = true;
            }
        }
    }
}

void JSort::insertSort() {
    int i = 0,
        j = 0,
        tmp = 0; // 临时保存i索引指向的值
    for (i=1; i<n; ++i) {
        tmp = arr[i];
        for (j=i-1; j>=0 && tmp<arr[j]; --j) {
            arr[j+1] = arr[j];
        }
        arr[j+1] = tmp;
    }
}

void JSort::shellSort() {
    int i = 0,
        j = 0,
        d = n>>1,
        tmp = 0;
    for (d=n>>1; d>0; d>>=1) {
        for (i=d; i<n; ++i) { // 以d为阶跃的插排
            tmp = arr[i];
            for (j=i-d; j>=0 && tmp<arr[j]; j-=d) {
                arr[j+d] = arr[j];
            }
            arr[j+d] = tmp;
        }
    }

}

int JSort::quick_partition(int low, int high) {
    int key = arr[high];
    int i = low - 1;
    int j = 0,
        tmp = 0;
    for (j=low; j<n; ++j) {
        if (arr[j] <= key) {
            ++i;
            
            tmp = arr[j];
            arr[j] = arr[i];
            arr[i] = tmp;
        }
    }
    arr[high] = arr[i+1];
    arr[i+1] = key;
    return i+1;
}

void JSort::quickSort(/*const int *arr, */int low/* = 0*/, int high/* = n*/, int flag/* = 0*/) {
    if (low >= high) {
        return;
    }
    if (flag == 0) {
        
        // method 1.
        int qivot = quick_partition(low, high);
        quickSort(low,  qivot- 1, flag);
        quickSort(qivot + 1, high, flag);
        
    } else {
        
        // method 2.
        int i = low,
            j = high,
            key = arr[low];
        while(i < j) {
            while (i<j && arr[j] > key) {
                --j;
            }
            if (i<j) {
                arr[i] = arr[j];
                ++i;
            }
            while (i<j && arr[i] < key) {
                ++i;
            }
            if (i<j) {
                arr[j] = arr[i];
                --j;
            }
        }
        arr[i] = key;
        
        quickSort(low, i-1, flag);
        quickSort(i+1, high, flag);
    }
}

void JSort::heap_adjust(int s, int m) {
    if (s>m) {
        return;
    }
    
    int tmp = arr[s],
        j = 0;
    for (j = 2*s + 1; j<m; j = 2*s + 1) {
        if (j<m-1 && arr[j]<arr[j+1]) {
            ++j;
        }
        if (arr[j]>tmp) {
            arr[s] = arr[j];
            s = j;
        } else {
            break;
        }
    }
    arr[s] = tmp;
}

void JSort::headSort() {
    int i = 0,
        tmp = 0;
    for (i=n>>1; i>=0; --i) {
        heap_adjust(i, n);
    }
    for (i=n-1; i>1; --i) {
        tmp = arr[0];
        arr[0] = arr[i];
        arr[i] = tmp;
        
        heap_adjust(0, i-1);
    }
}
