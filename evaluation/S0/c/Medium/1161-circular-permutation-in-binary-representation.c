// Source: https://leetcode.com/problems/circular-permutation-in-binary-representation/   |   Difficulty: Medium
//
// Problem Description:
// Given 2 integers n and start. Your task is return any permutation p of (0,1,2.....,2^n -1) such that :
//
//
// 	p[0] = start
// 	p[i] and p[i+1] differ by only one bit in their binary representation.
// 	p[0] and p[2^n -1] must also differ by only one bit in their binary representation.
//
// Example:
// Input: n = 2, start = 3
// Output: [3,2,0,1]
// Explanation: The binary representation of the permutation is (11,10,00,01). 
// All the adjacent element differ by one bit. Another valid permutation is [3,1,0,2]
//
// Constraints:
// 1 <= n <= 16
// 	0 <= start < 2 ^ n
//

/**

 * Note: The returned array must be malloced, assume caller calls free().

 */

int* circularPermutation(int n, int start, int* returnSize){


    int size = 1 << n;
    int* result = (int*)malloc(size * sizeof(int));
    *returnSize = size;

    for (int i = 0; i < size; i++) {
        int grayCode = i ^ (i >> 1);
        result[i] = grayCode ^ start ^ (start >> 1);
    }

    return result;
}
