// Source: https://leetcode.com/problems/beautiful-arrangement-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given two integers n and k, construct a list answer that contains n different positive integers ranging from 1 to n and obeys the following requirement:
//
//
// 	Suppose this list is answer = [a1, a2, a3, ... , an], then the list [|a1 - a2|, |a2 - a3|, |a3 - a4|, ... , |an-1 - an|] has exactly k distinct integers.
//
//
// Return the list answer. If there multiple valid answers, return any of them.
//
// Example:
// Input: n = 3, k = 1
// Output: [1,2,3]
// Explanation: The [1,2,3] has three different positive integers ranging from 1 to 3, and the [1,1] has exactly 1 distinct integer: 1
//
// Constraints:
// 1 <= k < n <= 104
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* constructArray(int n, int k, int* returnSize) {
    int* result = (int*)malloc(n * sizeof(int));
    *returnSize = n;

    int left = 1;
    int right = k + 1;
    int index = 0;

    // Create the first k+1 elements with alternating high and low values
    while (left <= right) {
        if (index % 2 == 0) {
            result[index++] = left++;
        } else {
            result[index++] = right--;
        }
    }

    // Fill the remaining elements in ascending order
    for (int i = k + 2; i <= n; i++) {
        result[index++] = i;
    }

    return result;      
}
