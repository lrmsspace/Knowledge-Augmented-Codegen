// Source: https://leetcode.com/problems/kth-smallest-amount-with-single-denomination-combination/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array coins representing coins of different denominations and an integer k.
//
// You have an infinite number of coins of each denomination. However, you are not allowed to combine coins of different denominations.
//
// Return the kth smallest amount that can be made using these coins.
//
// Example:
// Input: coins = [3,6,9], k = 3
//
// Output:  9
//
// Explanation: The given coins can make the following amounts:
// Coin 3 produces multiples of 3: 3, 6, 9, 12, 15, etc.
// Coin 6 produces multiples of 6: 6, 12, 18, 24, etc.
// Coin 9 produces multiples of 9: 9, 18, 27, 36, etc.
// All of the coins combined produce: 3, 6, 9, 12, 15, etc.
//
// Constraints:
// 1 <= coins.length <= 15
// 	1 <= coins[i] <= 25
// 	1 <= k <= 2 * 109
// 	coins contains pairwise distinct integers.
//
// Helpful references (internal KB):
// - The Inclusion-Exclusion Principle (array, number, counting, sieve)
//   • When to use: Use when direct counting of elements satisfying specific conditions is difficult due to overlaps, and you need to find the count of elements satisfying at least one, exactly k, or none of several properties.
//   • Idea: The Inclusion-Exclusion Principle counts the size of a union of sets by alternately adding and subtracting the sizes of intersections of increasing numbers of sets. Its complexity is often exponential in the number of properties.
//   • Invariants: At the start of processing subsets of size k, the running total correctly accounts for all intersections of size less than k.; For every element x, its contribution to the total sum is 1 if it satisfies the target condition, and 0 otherwise.
//   • Tips: Clearly define the properties (P1, P2, ..., Pn) for which elements are counted.; Systematically calculate the sizes of all relevant intersections of properties.
//   • Pitfalls: Incorrectly defining the properties or the universe of elements being counted.; Errors in calculating the sizes of specific intersections of properties.
// - Euclidean algorithm for computing the greatest common divisor (number, gcd)
//   • When to use: Use this algorithm to efficiently find the greatest common divisor of two non-negative integers, or as a subroutine for calculating the least common multiple.
//   • Idea: The Euclidean algorithm is an efficient method for computing the greatest common divisor (GCD) of two integers by repeatedly applying the division algorithm. It has a logarithmic time complexity, typically O(log(min(a,b))).
//   • Invariants: The GCD of the current pair (a, b) is always equal to the GCD of the original input numbers.; If a and b are non-negative, then the current values of a and b remain non-negative.
//   • Tips: The GCD of any number and zero is the number itself (e.g., gcd(a, 0) = a).; To calculate LCM, use the formula lcm(a, b) = (a / gcd(a, b)) * b to prevent potential overflow.
//   • Pitfalls: Ensure inputs are non-negative; if negative, take absolute values first.; Be careful with `gcd(0, 0)` definition, which is often undefined or 0.
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private long countLessEqual(int[] coins, long target) {
        int n = coins.length;
        long total = 0;
        // Iterate over all non-empty subsets of coins
        for (int mask = 1; mask < (1 << n); mask++) {
            long lcm = 1;
            int bitsCount = Integer.bitCount(mask);
            for (int i = 0; i < n; i++) {
                if ((mask & (1 << i)) != 0) {
                    lcm = lcm(lcm, coins[i]);
                    if (lcm > target) {
                        break; // No need to continue if lcm exceeds target
                    }
                }
            }
            if (lcm > target) {
                continue;
            }
            long count = target / lcm;
            if (bitsCount % 2 == 1) {
                total += count; // Add for odd-sized subsets
            } else {
                total -= count; // Subtract for even-sized subsets
            }
        }
        return total;
    }
    
    private long gcd(long a, long b) {
        while (b != 0) {
            long temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    private long lcm(long a, long b) {
        return a / gcd(a, b) * b;
    }

    public long findKthSmallest(int[] coins, int k) {
        long left = 1, right = (long) 1e18;
        while (left < right) {
            long mid = left + (right - left) / 2;
            if (countLessEqual(coins, mid) < k) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return left;            
    }
}
