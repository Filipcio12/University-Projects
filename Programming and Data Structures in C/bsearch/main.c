#include <stdio.h>

void* bsearch( const void *key, const void *ptr, size_t count, size_t size,
               int (*comp)(const void*, const void*) );

int intcmp(const void* a, const void* b);

int main()
{
    int arr[] = {1, 4, 11, 19, 33, 42, 48, 55};
    int (*cmpPtr)(const void* a, const void* b) = &intcmp;

    int* item;
    int num = 11;
    
    item = (int*) bsearch(&num, arr, sizeof(arr) / sizeof(arr[0]), sizeof(int), cmpPtr);

    if (item == NULL) {
        printf("Item not found.");
    }
    else {
        printf("Index of the found item = %ld.", item - arr);
    }
    return 0;
}

void* bsearch( const void *key, const void *ptr, size_t count, size_t size,
               int (*comp)(const void*, const void*) )
{
    char* p = (char*) ptr; // char has a size of 1 byte
    int left = 0;
    int right = count - 1;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (comp(key, (void*)(p + mid * size)) == 0) {
            return (void*)(p + mid * size);
        }
        else if (comp(key, (void*)(p + mid * size)) > 0) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return NULL;
}

int intcmp(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}