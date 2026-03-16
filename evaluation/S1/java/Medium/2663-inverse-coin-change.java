// Source: https://leetcode.com/problems/inverse-coin-change/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 1-indexed integer array numWays, where numWays[i] represents the number of ways to select a total amount i using an infinite supply of some fixed coin denominations. Each denomination is a positive integer with value at most numWays.length.
//
// However, the exact coin denominations have been lost. Your task is to recover the set of denominations that could have resulted in the given numWays array.
//
// Return a sorted array containing unique integers which represents this set of denominations.
//
// If no such set exists, return an empty array.
//
// Example:
// Input: numWays = [0,1,0,2,0,3,0,4,0,5]
//
// Output: [2,4,6]
//
// Explanation:
//
//
// 	
// 		
// 			Amount
// 			Number of ways
// 			Explanation
// 		
// 		
// 			1
// 			0
// 			There is no way to select coins with total value 1.
// 		
// 		
// 			2
// 			1
// 			The only way is [2].
// 		
// 		
// 			3
// 			0
// 			There is no way to select coins with total value 3.
// 		
// 		
// 			4
// 			2
// 			The ways are [2, 2] and [4].
// 		
// 		
// 			5
// 			0
// 			There is no way to select coins with total value 5.
// 		
// 		
// 			6
// 			3
// 			The ways are [2, 2, 2], [2, 4], and [6].
// 		
// 		
// 			7
// 			0
// 			There is no way to select coins with total value 7.
// 		
// 		
// 			8
// 			4
// 			The ways are [2, 2, 2, 2], [2, 2, 4], [2, 6], and [4, 4].
// 		
// 		
// 			9
// 			0
// 			There is no way to select coins with total value 9.
// 		
// 		
// 			10
// 			5
// 			The ways are [2, 2, 2, 2, 2], [2, 2, 2, 4], [2, 4, 4], [2, 2, 6], and [4, 6].
//
// Constraints:
// 1 <= numWays.length <= 100
// 	0 <= numWays[i] <= 2 * 108
//
// Helpful references (internal KB):
// - Fibonacci Numbers (array, dp-1d)
//   • When to use: Use this when calculating the n-th Fibonacci number or similar sequences where each term depends on a fixed number of preceding terms. It efficiently avoids redundant computations for moderate 'n' values.
//   • Idea: This algorithm calculates Fibonacci numbers iteratively by storing previously computed values in an array, building up to the desired n-th term. This approach achieves O(N) time complexity and O(N) space complexity.
//   • Invariants: dp[i] correctly stores the i-th Fibonacci number.; For i >= 2, dp[i] is computed as the sum of dp[i-1] and dp[i-2].
//   • Tips: Initialize base cases (F0, F1) correctly to start the sequence.; Use an array or two variables to store only the necessary previous terms.
//   • Pitfalls: Incorrectly initializing the base cases can lead to wrong results.; A naive recursive solution without memoization will lead to exponential time complexity.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public List<Integer> findCoins(int[] numWays) {
        List<Integer> result = new ArrayList<>();
        int n = numWays.length;
        int[] ways = new int[n];
        ways[0] = 1; // Base case: one way to make amount 0

        for (int amount = 1; amount < n; amount++) {
            if (ways[amount] != numWays[amount]) {
                int coin = amount;
                result.add(coin);
                // Update the ways array with the new coin
                for (int j = coin; j < n; j++) {
                    ways[j] += ways[j - coin];
                }
            }
        }

        // Verify if the constructed ways array matches numWays
        for (int i = 0; i < n; i++) {
            if (ways[i] != numWays[i]) {
                return new ArrayList<>(); // Return empty list if no valid set exists
            }
        }

        Collections.sort(result);
        return result;          
    }
}
