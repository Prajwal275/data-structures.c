#include <stdio.h>

int main() {
    int arr[5] = {1, 3, 2, 4, 5};
    int ele = 4;
    int pos = -1; 

    for (int i = 0; i < 5; i++) {
        if (ele == arr[i]) {
            pos = i; 
            break; 
        }
    }

    if (pos == -1) {
        printf("Element not found in the array.\n");
    } else {
        printf("Position of the element: %d\n", pos);
    }

    return 0;
}
