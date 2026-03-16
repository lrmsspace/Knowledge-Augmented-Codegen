// Source: https://leetcode.com/problems/previous-permutation-with-one-swap/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of positive integers arr (not necessarily distinct), return the lexicographically largest permutation that is smaller than arr, that can be made with exactly one swap. If it cannot be done, then return the same array.
//
// Note that a swap exchanges the positions of two numbers arr[i] and arr[j]
//
// Example:
// Input: arr = [3,2,1]
// Output: [3,1,2]
// Explanation: Swapping 2 and 1.
//
// Constraints:
// 1 <= arr.length <= 104
// 	1 <= arr[i] <= 104
//

class Solution {
    public int[] prevPermOpt1(int[] arr) {
        int n = arr.length;
        int i = n - 2;

        // Find the first decreasing element from the right
        while (i >= 0 && arr[i] <= arr[i + 1]) {
            i--;
        }

        // If the entire array is non-decreasing, return it as is
        if (i < 0) {
            return arr;
        }

        int j = n - 1;

        // Find the largest element to the right of arr[i] that is smaller than arr[i]
        while (arr[j] >= arr[i] || arr[j] == arr[j - 1]) {
            j--;
        }

        // Swap the found elements
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;

        return arr;         
    }
}
