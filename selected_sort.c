#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
void selection_sort(int arr[], int n) {
    int i, j, max_idx;
    // 가장 큰 수  찾기, 맨뒤와 보내기
    for(i=0;i< n-1; i++) {
        max_idx = -1;
        int temp_idx = 0;
        int temp_num = 0;
        for(j =0; j<n-i; j++) {
            if(arr[j] > max_idx) {       // 큰 수 찾기
                max_idx = arr[j];
                temp_idx = j;

            }
        }
        temp_num = arr[n-i-1];
        arr[n-i-1] = arr[temp_idx];
        arr[temp_idx] = temp_num;
    }

    
}
 
int main() {
    const int n = 10;
    int arr[n];
 
    srand(time(NULL)); // 시드값 설정
 
    // 1~64까지의 숫자를 배열에 할당
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
 
    // 랜덤하게 배열 섞기
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
 
    // 정렬 전 배열 출력
    printf("Before sorting: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
 
    // 선택 정렬 수행
    selection_sort(arr, n);
 
    // 정렬 후 배열 출력
    printf("After sorting: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
 
    return 0;
}