#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10

void display(int *arr)
{
    printf("[ ");
    for (int i = 0; i < MAX; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("]\n");
    return;
}

void print_mylog(int *arr, int start, int end, char *content)
{
    printf("[log] : %s : [ ", content);
    for (int i = start; i <= end; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
    return;
}

void sort_selection(int *arr)
{ // 가장 베이직한 정렬
    for (int left = 0; left < MAX - 2; left++)
    {
        for (int right = left + 1; right < MAX - 1; right++)
        { // Right인덱스가 left포함 왼편을 제외한 나머지를 쭉 돌면서 작은거 교환
            if (arr[left] > arr[right])
                swap(&arr[left], &arr[right]);
        }
    }
}

void sort_merge(int *arr, int low, int high)
{
    // 1. exit condition
    if (low == high)
        return; // 원소가 하나면 이미 정렬된 것으로 취급

    // 2. divide
    int mid = (low + high) / 2;

    // 3. conquer(recursion)
    sort_merge(arr, low, mid);
    sort_merge(arr, mid + 1, high);
    print_mylog(arr, low, high, "current array");
    // 이 시점부터 배열의 왼편과 오른편은 정렬된 상태로 취급

    // 4. combine(sort sorted parts)
    int left = low; // 두 배열의 시작지점 설정
    int right = mid + 1;
    int length = high - low + 1; // 임시 배열 크기
    int arr_temp[length];


    print_mylog(arr, left, mid, "left side");


    print_mylog(arr, right, high, "right side");

    // // 두 배열의 원소 중 작은 값 대입
    // // 그 후 대입한 쪽의 인덱스를 증가시킴
    // //-> 반복
    for (int i = 0; i < length; i++)
    {
        // 왼쪽 배열의 모든 요소를 사용한 경우
        if (left > mid)
        {
            arr_temp[i] = arr[right];
            right++;
        }
        // 오른쪽 배열의 모든 요소를 사용한 경우
        else if (right > high)
        {
            arr_temp[i] = arr[left];
            left++;
        }
        // 왼쪽 배열의 요소가 클 경우
        else if (arr[left] > arr[right])
        {
            arr_temp[i] = arr[right];
            right++;
        }
        // 오른쪽 배열의 요소가 클 경우
        else if (arr[left] < arr[right])
        {
            arr_temp[i] = arr[left];
            left++;
        }
    }

    // // 5. copy(원래 배열에)
    int j = 0;
    for (int i = low; i <= high; i++)
    {
        arr[i] = arr_temp[j];
        j++;
    }
}

int main()
{
    int arr[MAX] = {5, 8, 3, 1, 10, 15, 2, 9, 12, 18};
    int arr_2[MAX] = {23, 78, 1, 98, 4, 8, 2, 76, 11};
    printf("original array : ");
    display(arr_2);
    sort_merge(arr_2, 0, MAX - 1);
    printf("sorted array : ");
    display(arr_2);
    return 0;
}