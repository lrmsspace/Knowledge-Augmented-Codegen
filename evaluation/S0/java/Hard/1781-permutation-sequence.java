// Source: https://leetcode.com/problems/permutation-sequence/   |   Difficulty: Hard
//
// Problem Description:
// The set [1, 2, 3, ..., n] contains a total of n! unique permutations.
//
// By listing and labeling all of the permutations in order, we get the following sequence for n = 3:
//
//
// 	"123"
// 	"132"
// 	"213"
// 	"231"
// 	"312"
// 	"321"
//
//
// Given n and k, return the kth permutation sequence.
//
// Example:
// Input: n = 3, k = 3
// Output: "213"
//
// Constraints:
// 1 <= n <= 9
// 	1 <= k <= n!
//

class Solution {
    public String getPermutation(int n, int k) {
        List<Integer> numbers = new ArrayList<>();
        int[] factorial = new int[n + 1];
        StringBuilder result = new StringBuilder();

        // Precompute factorials
        factorial[0] = 1;
        for (int i = 1; i <= n; i++) {
            factorial[i] = factorial[i - 1] * i;
            numbers.add(i);
        }

        // Adjust k to be zero-based index
        k--;

        for (int i = n; i >= 1; i--) {
            int idx = k / factorial[i - 1];
            result.append(numbers.get(idx));
            numbers.remove(idx);
            k %= factorial[i - 1];
        }

        return result.toString();           
    }
}
