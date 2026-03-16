// Source: https://leetcode.com/problems/adding-two-negabinary-numbers/   |   Difficulty: Medium
//
// Problem Description:
// Given two numbers arr1 and arr2 in base -2, return the result of adding them together.
//
// Each number is given in array format:  as an array of 0s and 1s, from most significant bit to least significant bit.  For example, arr = [1,1,0,1] represents the number (-2)^3 + (-2)^2 + (-2)^0 = -3.  A number arr in array, format is also guaranteed to have no leading zeros: either arr == [0] or arr[0] == 1.
//
// Return the result of adding arr1 and arr2 in the same format: as an array of 0s and 1s with no leading zeros.
//
// Example:
// Input: arr1 = [1,1,1,1,1], arr2 = [1,0,1]
// Output: [1,0,0,0,0]
// Explanation: arr1 represents 11, arr2 represents 5, the output represents 16.
//
// Constraints:
// 1 <= arr1.length, arr2.length <= 1000
// 	arr1[i] and arr2[i] are 0 or 1
// 	arr1 and arr2 have no leading zeros
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* addNegabinary(int* arr1, int arr1Size, int* arr2, int arr2Size, int* returnSize) {
    int maxSize = arr1Size > arr2Size ? arr1Size : arr2Size;
    int* result = (int*)calloc(maxSize + 2, sizeof(int));
    int carry = 0;
    int i = arr1Size - 1;
    int j = arr2Size - 1;
    int k = 0;

    while (i >= 0 || j >= 0 || carry != 0) {
        int sum = carry;
        if (i >= 0) {
            sum += arr1[i--];
        }
        if (j >= 0) {
            sum += arr2[j--];
        }

        result[k++] = (sum & 1);
        carry = -(sum >> 1);
    }

    // Remove leading zeros
    while (k > 1 && result[k - 1] == 0) {
        k--;
    }

    // Reverse the result array
    for (int left = 0, right = k - 1; left < right; left++, right--) {
        int temp = result[left];
        result[left] = result[right];
        result[right] = temp;
    }

    *returnSize = k;
    return result;      
}
