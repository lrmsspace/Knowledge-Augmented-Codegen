// Source: https://leetcode.com/problems/element-appearing-more-than-25-in-sorted-array/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array sorted in non-decreasing order, there is exactly one integer in the array that occurs more than 25% of the time, return that integer.
//
// Example:
// Input: arr = [1,2,2,6,6,6,6,7,10]
// Output: 6
//
// Constraints:
// 1 <= arr.length <= 104
// 	0 <= arr[i] <= 105
//

int findSpecialInteger(int* arr, int arrSize) {
    int threshold = arrSize / 4;
    for (int i = 0; i <= arrSize - threshold - 1; i++) {
        if (arr[i] == arr[i + threshold]) {
            return arr[i];
        }
    }
    return -1; // This line should never be reached due to problem constraints      
}
