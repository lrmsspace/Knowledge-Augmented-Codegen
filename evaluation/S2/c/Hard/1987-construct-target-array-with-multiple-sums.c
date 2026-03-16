// Source: https://leetcode.com/problems/construct-target-array-with-multiple-sums/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array target of n integers. From a starting array arr consisting of n 1's, you may perform the following procedure :
//
//
// 	let x be the sum of all elements currently in your array.
// 	choose index i, such that 0 <= i < n and set the value of arr at index i to x.
// 	You may repeat this procedure as many times as needed.
//
//
// Return true if it is possible to construct the target array from arr, otherwise, return false.
//
// Example:
// Input: target = [9,3,5]
// Output: true
// Explanation: Start with arr = [1, 1, 1] 
// [1, 1, 1], sum = 3 choose index 1
// [1, 3, 1], sum = 5 choose index 2
// [1, 3, 5], sum = 9 choose index 0
// [9, 3, 5] Done
//
// Constraints:
// n == target.length
// 	1 <= n <= 5 * 104
// 	1 <= target[i] <= 109
//
// Helpful references (internal KB):
// - Sprague-Grundy theorem. Nim (array, number, game-theory, prefix-xor)
//   • When to use: Use when analyzing impartial games with perfect information and no draws, especially to determine winning/losing states or to find a winning strategy. It's particularly useful for games that can be reduced to Nim.
//   • Idea: The Sprague-Grundy theorem states that every impartial game under the normal play convention is equivalent to a Nim pile of a certain size (its nim-value or grundy number). For Nim, a position is a winning position if and only if the XOR sum of all pile sizes is non-zero, allowing for O(N) classification.
//   • Invariants: The XOR sum of the pile sizes (nim-sum) represents the game's current nim-value.; If the nim-sum is zero, any valid move will result in a non-zero nim-sum for the opponent.
//   • Tips: Understand the definition of impartial games and their properties.; Calculate the XOR sum of game components to determine the nim-sum.
//   • Pitfalls: Confusing impartial games with partisan games where players have different moves.; Incorrectly calculating the XOR sum, leading to wrong state classifications.
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
// - Fibonacci Numbers (array, dp-1d)
//   • When to use: Use this when calculating the n-th Fibonacci number or similar sequences where each term depends on a fixed number of preceding terms. It efficiently avoids redundant computations for moderate 'n' values.
//   • Idea: This algorithm calculates Fibonacci numbers iteratively by storing previously computed values in an array, building up to the desired n-th term. This approach achieves O(N) time complexity and O(N) space complexity.
//   • Invariants: dp[i] correctly stores the i-th Fibonacci number.; For i >= 2, dp[i] is computed as the sum of dp[i-1] and dp[i-2].
//   • Tips: Initialize base cases (F0, F1) correctly to start the sequence.; Use an array or two variables to store only the necessary previous terms.
//   • Pitfalls: Incorrectly initializing the base cases can lead to wrong results.; A naive recursive solution without memoization will lead to exponential time complexity.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool isPossible(int* target, int targetSize) {
    long long sum = 0;
    for (int i = 0; i < targetSize; ++i) {
        sum += target[i];
    }

    while (true) {
        int maxIndex = 0;
        for (int i = 1; i < targetSize; ++i) {
            if (target[i] > target[maxIndex]) {
                maxIndex = i;
            }
        }

        long long maxValue = target[maxIndex];
        long long restSum = sum - maxValue;

        if (maxValue == 1 || restSum == 1) {
            return true;
        }
        if (restSum == 0 || maxValue < restSum) {
            return false;
        }

        long long newValue = maxValue % restSum;
        if (newValue == 0) {
            return false;
        }

        target[maxIndex] = newValue;
        sum = restSum + newValue;
    }       
}
