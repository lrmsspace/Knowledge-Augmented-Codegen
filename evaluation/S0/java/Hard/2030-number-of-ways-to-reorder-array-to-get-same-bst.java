// Source: https://leetcode.com/problems/number-of-ways-to-reorder-array-to-get-same-bst/   |   Difficulty: Hard
//
// Problem Description:
// Given an array nums that represents a permutation of integers from 1 to n. We are going to construct a binary search tree (BST) by inserting the elements of nums in order into an initially empty BST. Find the number of different ways to reorder nums so that the constructed BST is identical to that formed from the original array nums.
//
//
// 	For example, given nums = [2,1,3], we will have 2 as the root, 1 as a left child, and 3 as a right child. The array [2,3,1] also yields the same BST but [3,2,1] yields a different BST.
//
//
// Return the number of ways to reorder nums such that the BST formed is identical to the original BST formed from nums.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [2,1,3]
// Output: 1
// Explanation: We can reorder nums to be [2,3,1] which will yield the same BST. There are no other ways to reorder nums which will yield the same BST.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	1 <= nums[i] <= nums.length
// 	All integers in nums are distinct.
//

class Solution {
    public int numOfWays(int[] nums) {
        int mod = (int)1e9 + 7;
        int n = nums.length;

        long[][] comb = new long[n + 1][n + 1];
        for (int i = 0; i <= n; i++) {
            comb[i][0] = 1;
            for (int j = 1; j <= i; j++) {
                comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % mod;
            }
        }

        return (int)(dfs(nums, comb) - 1);                  
    }
}
