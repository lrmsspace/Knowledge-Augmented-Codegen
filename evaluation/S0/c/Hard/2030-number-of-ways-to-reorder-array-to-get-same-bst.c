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

int numOfWays(int* nums, int numsSize) {
    const int MOD = 1000000007;

    /* Precompute binomial coefficients C(n, k) % MOD using Pascal's triangle */
    int C[1001][1001];
    memset(C, 0, sizeof(C));
    for (int n = 0; n <= 1000; ++n) {
        C[n][0] = 1;
        for (int k = 1; k <= n; ++k) {
            C[n][k] = (C[n - 1][k - 1] + C[n - 1][k]) % MOD;
        }
    }

    /* Recursive function to count ways */
    int dfs(int* arr, int size) {
        if (size <= 2) return 1;

        int root = arr[0];
        int left[1000], right[1000];
        int lSize = 0, rSize = 0;

        for (int i = 1; i < size; ++i) {
            if (arr[i] < root) left[lSize++] = arr[i];
            else right[rSize++] = arr[i];
        }

        long long leftWays = dfs(left, lSize);
        long long rightWays = dfs(right, rSize);

        long long ways = (C[size - 1][lSize] * leftWays) % MOD;
        ways = (ways * rightWays) % MOD;

        return (int)ways;
    }

    return (dfs(nums, numsSize) - 1 + MOD) % MOD; /* subtract 1 for the original ordering */        
}
