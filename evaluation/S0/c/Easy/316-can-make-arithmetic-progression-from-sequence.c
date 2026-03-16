// Source: https://leetcode.com/problems/can-make-arithmetic-progression-from-sequence/   |   Difficulty: Easy
//
// Problem Description:
// A sequence of numbers is called an arithmetic progression if the difference between any two consecutive elements is the same.
//
// Given an array of numbers arr, return true if the array can be rearranged to form an arithmetic progression. Otherwise, return false.
//
// Example:
// Input: arr = [3,5,1]
// Output: true
// Explanation: We can reorder the elements as [1,3,5] or [5,3,1] with differences 2 and -2 respectively, between each consecutive elements.
//
// Constraints:
// 2 <= arr.length <= 1000
// 	-106 <= arr[i] <= 106
//

bool canMakeArithmeticProgression(int* arr, int arrSize) {
    // Sort the array using qsort
    int compare(const void* a, const void* b) {
        return (*(int*)a - *(int*)b);
    }
    qsort(arr, arrSize, sizeof(int), compare);

    // Calculate the common difference
    int common_diff = arr[1] - arr[0];

    // Check if the difference between consecutive elements is the same
    for (int i = 2; i < arrSize; i++) {
        if (arr[i] - arr[i - 1] != common_diff) {
            return false;
        }
    }

    return true;        
}
