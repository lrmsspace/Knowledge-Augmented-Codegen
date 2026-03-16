// Source: https://leetcode.com/problems/stone-game-viii/   |   Difficulty: Hard
//
// Problem Description:
// Alice and Bob take turns playing a game, with Alice starting first.
//
// There are n stones arranged in a row. On each player's turn, while the number of stones is more than one, they will do the following:
//
//
// 	Choose an integer x > 1, and remove the leftmost x stones from the row.
// 	Add the sum of the removed stones' values to the player's score.
// 	Place a new stone, whose value is equal to that sum, on the left side of the row.
//
//
// The game stops when only one stone is left in the row.
//
// The score difference between Alice and Bob is (Alice's score - Bob's score). Alice's goal is to maximize the score difference, and Bob's goal is the minimize the score difference.
//
// Given an integer array stones of length n where stones[i] represents the value of the ith stone from the left, return the score difference between Alice and Bob if they both play optimally.
//
// Example:
// Input: stones = [-1,2,-3,4,-5]
// Output: 5
// Explanation:
// - Alice removes the first 4 stones, adds (-1) + 2 + (-3) + 4 = 2 to her score, and places a stone of
//   value 2 on the left. stones = [2,-5].
// - Bob removes the first 2 stones, adds 2 + (-5) = -3 to his score, and places a stone of value -3 on
//   the left. stones = [-3].
// The difference between their scores is 2 - (-3) = 5.
//
// Constraints:
// n == stones.length
// 	2 <= n <= 105
// 	-104 <= stones[i] <= 104
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
// - Knapsack Problem (array, knapsack, dp-1d, enumeration)
//   • When to use: Use when selecting items from a set to maximize or minimize a value under a capacity constraint. It's also applicable for partitioning problems with a fixed budget.
//   • Idea: This algorithm finds the maximum value that can be obtained by selecting a subset of items, each with a weight and a value, such that their total weight does not exceed a given capacity. It typically uses dynamic programming with a time complexity of O(N*W), where N is the number of items and W is the capacity.
//   • Invariants: After processing item `i`, `dp[w]` stores the maximum value for capacity `w` using items up to `i`.; For each item, `dp[w]` is updated considering either including or excluding the current item.
//   • Tips: Use a 2D DP table `dp[i][w]` for item `i` and weight `w` for clarity, then optimize to 1D.; When optimizing to 1D, iterate weights downwards to avoid using an item multiple times.
//   • Pitfalls: Incorrectly initializing the DP table can lead to wrong results or infinite loops.; Forgetting to iterate weights downwards in 1D DP can lead to items being picked multiple times (unbounded knapsack).
// - Sieve of Eratosthenes (array, sieve, enumeration)
//   • When to use: Use when you need to find all prime numbers up to a certain limit or precompute primality for a range. It is efficient for generating primes within a reasonable upper bound.
//   • Idea: The Sieve of Eratosthenes efficiently finds all prime numbers up to a specified integer by iteratively marking multiples of primes as composite. It achieves a time complexity of O(N log log N).
//   • Invariants: All numbers less than the current prime 'p' have already been processed.; If 'i' is marked as prime, then all its multiples less than 'i*i' have been marked composite by smaller primes.
//   • Tips: Optimize by starting inner loop from p*p, as smaller multiples would have been marked.; Use a boolean array for primality, or an integer array to store smallest prime factor (SPF).
//   • Pitfalls: Incorrectly handling 0 and 1, which are neither prime nor composite.; Off-by-one errors when setting array bounds or loop conditions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.



int stoneGameVIII(int* stones, int stonesSize){
    long long prefixSum = 0;
    for (int i = 0; i < stonesSize; i++) {
        prefixSum += stones[i];
        stones[i] = prefixSum;
    }

    long long maxDiff = stones[stonesSize - 1];
    long long currentMax = stones[1];

    for (int i = 2; i < stonesSize - 1; i++) {
        if (stones[i] - currentMax > maxDiff) {
            maxDiff = stones[i] - currentMax;
        }
        if (stones[i] < currentMax) {
            currentMax = stones[i];
        }
    }

    return (int)maxDiff;
}
