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
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public String getPermutation(int n, int k) {
        // Create a list of numbers to get the permutation from
        List<Integer> numbers = new ArrayList<>();
        for (int i = 1; i <= n; i++) {
            numbers.add(i);
        }

        // Calculate factorials for numbers from 0 to n-1
        int[] factorials = new int[n];
        factorials[0] = 1;
        for (int i = 1; i < n; i++) {
            factorials[i] = factorials[i - 1] * i;
        }

        // Adjust k to be zero-indexed
        k--;

        StringBuilder result = new StringBuilder();

        // Build the permutation
        for (int i = n - 1; i >= 0; i--) {
            int factorial = factorials[i];
            int index = k / factorial;
            result.append(numbers.get(index));
            numbers.remove(index);
            k %= factorial;
        }

        return result.toString();           
    }
}
