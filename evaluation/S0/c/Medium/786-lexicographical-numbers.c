// Source: https://leetcode.com/problems/lexicographical-numbers/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer n, return all the numbers in the range [1, n] sorted in lexicographical order.
//
// You must write an algorithm that runs in O(n) time and uses O(1) extra space.
//
// Example:
// Input: n = 13
// Output: [1,10,11,12,13,2,3,4,5,6,7,8,9]
//
// Constraints:
// 1 <= n <= 5 * 104
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* lexicalOrder(int n, int* returnSize) {
    int *result = (int *)malloc(n * sizeof(int));
    int index = 0;
    int current = 1;

    while (index < n) {
        result[index++] = current;

        if (current * 10 <= n) {
            current *= 10;
        } else {
            if (current >= n) {
                current /= 10;
            }
            current++;
            while (current % 10 == 0) {
                current /= 10;
            }
        }
    }

    *returnSize = n;
    return result;      
}
