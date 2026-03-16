// Source: https://leetcode.com/problems/minimum-number-of-operations-to-make-all-array-elements-equal-to-1/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array nums consisiting of positive integers. You can do the following operation on the array any number of times:
//
//
// 	Select an index i such that 0 <= i < n - 1 and replace either of nums[i] or nums[i+1] with their gcd value.
//
//
// Return the minimum number of operations to make all elements of nums equal to 1. If it is impossible, return -1.
//
// The gcd of two integers is the greatest common divisor of the two integers.
//
// Example:
// Input: nums = [2,6,3,4]
// Output: 4
// Explanation: We can do the following operations:
// - Choose index i = 2 and replace nums[2] with gcd(3,4) = 1. Now we have nums = [2,6,1,4].
// - Choose index i = 1 and replace nums[1] with gcd(6,1) = 1. Now we have nums = [2,1,1,4].
// - Choose index i = 0 and replace nums[0] with gcd(2,1) = 1. Now we have nums = [1,1,1,4].
// - Choose index i = 2 and replace nums[3] with gcd(1,4) = 1. Now we have nums = [1,1,1,1].
//
// Constraints:
// 2 <= nums.length <= 50
// 	1 <= nums[i] <= 106
//
// Helpful references (internal KB):
// - Euler's totient function
//  (array, number, sieve, enumeration)
//   • When to use: Use when needing to count positive integers up to a given integer n that are relatively prime to n. It is also useful for problems involving modular arithmetic, group theory, and cryptographic applications.
//   • Idea: Euler's totient function, φ(n), counts the number of positive integers up to a given integer n that are relatively prime to n. It can be computed using prime factorization in O(sqrt(N)) or for a range using a sieve in O(N log log N).
//   • Invariants: For a sieve, phi[i] correctly stores the totient value for i after processing all its prime factors.; When factorizing n, n is continuously reduced by its smallest prime factor until it becomes 1.
//   • Tips: For a single n, find its prime factors and apply the product formula.; For computing φ(n) for all n up to a limit, use a sieve similar to Sieve of Eratosthenes.
//   • Pitfalls: Incorrectly handling repeated prime factors in the formula.; Integer overflow when calculating products for very large n.
// - Operations on polynomials and series (array, gcd)
//   • When to use: When performing algebraic operations on polynomials or power series, such as finding their greatest common divisor, differentiation, integration, or computing series expansions like inverse, logarithm, and exponential, especially in modular arithmetic.
//   • Idea: This card details various algebraic operations on polynomials and power series, including finding their greatest common divisor (GCD) and computing derivatives, integrals, inverses, logarithms, exponentials, and powers. These operations manipulate polynomial coefficients, often within a modular arithmetic context, with many achieving O(N log N) or O(N log NK) complexity.
//   • Invariants: The degree of the resulting polynomial/series is correctly maintained after each operation.; Coefficients are always reduced modulo m if modular arithmetic is applied.
//   • Tips: Represent polynomials as arrays of coefficients, typically from lowest to highest degree.; Modular arithmetic is crucial for many polynomial operations, including GCD, to prevent overflow and ensure results stay within a finite field.
//   • Pitfalls: Forgetting to handle modular inverses for division operations (e.g., integration, polynomial division in GCD, inverse, log).; Incorrectly handling the constant term or leading coefficients, especially for inverse, logarithm, or polynomial division.
// - 0-1 BFS (graph, array, dijkstra, bfs)
//   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently determines minimum costs without a full priority queue.
//   • Idea: A specialized Breadth-First Search variant that finds shortest paths in graphs with only 0 or 1 edge weights. It uses a deque to process 0-weight edges before 1-weight edges, achieving O(V+E) time complexity.
//   • Invariants: All nodes currently in the deque have a distance value of either `k` or `k+1` for some integer `k`.; Nodes pushed to the front of the deque always have a distance equal to the current node's distance.
//   • Tips: Utilize a deque to maintain the order of processing nodes.; Add nodes reached via 0-weight edges to the front of the deque.
//   • Pitfalls: Incorrectly using a standard queue instead of a deque.; Failing to initialize distances to infinity for all nodes except the source.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int minOperations(int[] nums) {
        int n = nums.length;
        int gcd = nums[0];
        for (int num : nums) {
            gcd = gcd(gcd, num);
        }
        if (gcd > 1) {
            return -1;
        }

        int minLength = Integer.MAX_VALUE;
        for (int i = 0; i < n; i++) {
            int currentGcd = nums[i];
            if (currentGcd == 1) {
                minLength = 1;
                break;
            }
            for (int j = i + 1; j < n; j++) {
                currentGcd = gcd(currentGcd, nums[j]);
                if (currentGcd == 1) {
                    minLength = Math.min(minLength, j - i + 1);
                    break;
                }
            }
        }

        return minLength + n - 2;           
    }
}
