// Source: https://leetcode.com/problems/duplicate-zeros/   |   Difficulty: Easy
//
// Problem Description:
// Given a fixed-length integer array arr, duplicate each occurrence of zero, shifting the remaining elements to the right.
//
// Note that elements beyond the length of the original array are not written. Do the above modifications to the input array in place and do not return anything.
//
// Example:
// Input: arr = [1,0,2,3,0,4,5,0]
// Output: [1,0,0,2,3,0,0,4]
// Explanation: After calling your function, the input array is modified to: [1,0,0,2,3,0,0,4]
//
// Constraints:
// 1 <= arr.length <= 104
// 	0 <= arr[i] <= 9
//

void duplicateZeros(int* arr, int arrSize) {
    int possibleDups = 0;
    int length_ = arrSize - 1;

    for (int left = 0; left <= length_ - possibleDups; left++) {
        if (arr[left] == 0) {
            if (left == length_ - possibleDups) {
                arr[length_] = 0;
                length_ -= 1;
                break;
            }
            possibleDups++;
        }
    }

    int last = length_ - possibleDups;

    for (int i = last; i >= 0; i--) {
        if (arr[i] == 0) {
            arr[i + possibleDups] = 0;
            possibleDups--;
            arr[i + possibleDups] = 0;
        } else {
            arr[i + possibleDups] = arr[i];
        }
    }       
}
