// Source: https://leetcode.com/problems/next-greater-element-iii/   |   Difficulty: Medium
//
// Problem Description:
// Given a positive integer n, find the smallest integer which has exactly the same digits existing in the integer n and is greater in value than n. If no such positive integer exists, return -1.
//
// Note that the returned integer should fit in 32-bit integer, if there is a valid answer but it does not fit in 32-bit integer, return -1.
//
// Example:
// Input: n = 12
// Output: 21
//
// Constraints:
// 1 <= n <= 231 - 1
//

class Solution {
    public int nextGreaterElement(int n) {
        char[] arr = String.valueOf(n).toCharArray();
        int i = arr.length - 2;

        // Step 1: Find the first decreasing element from the right
        while (i >= 0 && arr[i] >= arr[i + 1]) {
            i--;
        }

        // If no such element is found, return -1
        if (i < 0) {
            return -1;
        }

        // Step 2: Find the element just larger than arr[i] to its right
        int j = arr.length - 1;
        while (arr[j] <= arr[i]) {
            j--;
        }

        // Step 3: Swap elements at i and j
        swap(arr, i, j);

        // Step 4: Reverse the elements to the right of i
        reverse(arr, i + 1, arr.length - 1);

        // Convert back to integer and check for overflow
        long result = Long.parseLong(new String(arr));
        return result <= Integer.MAX_VALUE ? (int) result : -1;         
    }
}
