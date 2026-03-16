// Source: https://leetcode.com/problems/binary-trees-with-factors/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of unique integers, arr, where each integer arr[i] is strictly greater than 1.
//
// We make a binary tree using these integers, and each number may be used for any number of times. Each non-leaf node's value should be equal to the product of the values of its children.
//
// Return the number of binary trees we can make. The answer may be too large so return the answer modulo 109 + 7.
//
// Example:
// Input: arr = [2,4]
// Output: 3
// Explanation: We can make these trees: [2], [4], [4, 2, 2]
//
// Constraints:
// 1 <= arr.length <= 1000
// 	2 <= arr[i] <= 109
// 	All the values of arr are unique.
//

class Solution {
    public int numFactoredBinaryTrees(int[] arr) {
        final int MOD = 1_000_000_007;
        int n = arr.length;
        Arrays.sort(arr);
        long[] dp = new long[n];
        Arrays.fill(dp, 1); // Each element can form a single-node tree

        Map<Integer, Integer> indexMap = new HashMap<>();
        for (int i = 0; i < n; i++) {
            indexMap.put(arr[i], i);
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (arr[i] % arr[j] == 0) { // arr[j] is a potential left child
                    int rightChild = arr[i] / arr[j];
                    if (indexMap.containsKey(rightChild)) {
                        int k = indexMap.get(rightChild);
                        dp[i] = (dp[i] + dp[j] * dp[k]) % MOD;
                    }
                }
            }
        }

        long result = 0;
        for (long count : dp) {
            result = (result + count) % MOD;
        }

        return (int) result;            
    }
}
