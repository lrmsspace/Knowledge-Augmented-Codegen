// Source: https://leetcode.com/problems/arithmetic-subarrays/   |   Difficulty: Medium
//
// Problem Description:
// A sequence of numbers is called arithmetic if it consists of at least two elements, and the difference between every two consecutive elements is the same. More formally, a sequence s is arithmetic if and only if s[i+1] - s[i] == s[1] - s[0] for all valid i.
//
// For example, these are arithmetic sequences:
//
//
// 1, 3, 5, 7, 9
// 7, 7, 7, 7
// 3, -1, -5, -9
//
// The following sequence is not arithmetic:
//
//
// 1, 1, 2, 5, 7
//
// You are given an array of n integers, nums, and two arrays of m integers each, l and r, representing the m range queries, where the ith query is the range [l[i], r[i]]. All the arrays are 0-indexed.
//
// Return a list of boolean elements answer, where answer[i] is true if the subarray nums[l[i]], nums[l[i]+1], ... , nums[r[i]] can be rearranged to form an arithmetic sequence, and false otherwise.
//
// Example:
// Input: nums = [4,6,5,9,3,7], l = [0,0,2], r = [2,3,5]
// Output: [true,false,true]
// Explanation:
// In the 0th query, the subarray is [4,6,5]. This can be rearranged as [6,5,4], which is an arithmetic sequence.
// In the 1st query, the subarray is [4,6,5,9]. This cannot be rearranged as an arithmetic sequence.
// In the 2nd query, the subarray is [5,9,3,7]. This can be rearranged as [3,5,7,9], which is an arithmetic sequence.
//
// Constraints:
// n == nums.length
// 	m == l.length
// 	m == r.length
// 	2 <= n <= 500
// 	1 <= m <= 500
// 	0 <= l[i] < r[i] < n
// 	-105 <= nums[i] <= 105
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
bool* checkArithmeticSubarrays(int* nums, int numsSize, int* l, int lSize, int* r, int rSize, int* returnSize) {
    bool* result = (bool*)malloc(lSize * sizeof(bool));
    *returnSize = lSize;

    for (int i = 0; i < lSize; i++) {
        int start = l[i];
        int end = r[i];
        int length = end - start + 1;

        // Create a temporary array to hold the subarray
        int* subarray = (int*)malloc(length * sizeof(int));
        for (int j = 0; j < length; j++) {
            subarray[j] = nums[start + j];
        }

        // Sort the subarray
        for (int m = 0; m < length - 1; m++) {
            for (int n = 0; n < length - m - 1; n++) {
                if (subarray[n] > subarray[n + 1]) {
                    int temp = subarray[n];
                    subarray[n] = subarray[n + 1];
                    subarray[n + 1] = temp;
                }
            }
        }

        // Check if the sorted subarray is arithmetic
        bool isArithmetic = true;
        int diff = subarray[1] - subarray[0];
        for (int k = 1; k < length - 1; k++) {
            if (subarray[k + 1] - subarray[k] != diff) {
                isArithmetic = false;
                break;
            }
        }

        result[i] = isArithmetic;
        free(subarray);
    }

    return result;      
}
