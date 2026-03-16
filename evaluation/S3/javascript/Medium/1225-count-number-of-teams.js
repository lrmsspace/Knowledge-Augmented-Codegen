// Source: https://leetcode.com/problems/count-number-of-teams/   |   Difficulty: Medium
//
// Problem Description:
// There are n soldiers standing in a line. Each soldier is assigned a unique rating value.
//
// You have to form a team of 3 soldiers amongst them under the following rules:
//
//
// 	Choose 3 soldiers with index (i, j, k) with rating (rating[i], rating[j], rating[k]).
// 	A team is valid if: (rating[i] < rating[j] < rating[k]) or (rating[i] > rating[j] > rating[k]) where (0 <= i < j < k < n).
//
//
// Return the number of teams you can form given the conditions. (soldiers can be part of multiple teams).
//
// Example:
// Input: rating = [2,5,3,4,1]
// Output: 3
// Explanation: We can form three teams given the conditions. (2,3,4), (5,4,1), (5,3,1).
//
// Constraints:
// n == rating.length
// 	3 <= n <= 1000
// 	1 <= rating[i] <= 105
// 	All the integers in rating are unique.
//
// Helpful references (internal KB):
// - Binomial Coefficients (array, enumeration)
//   • When to use: When you need to calculate the number of ways to choose k items from n distinct items, often under modular constraints.
//   • Idea: Binomial coefficients represent the number of ways to choose k items from a set of n distinct items. They can be computed using Pascal's identity or factorials, with complexity varying based on the method and modulo requirements.
//   • Invariants: For Pascal's triangle, dp[i][j] stores C(i, j).; For factorial method, fact[i] stores i! % M.
//   • Tips: Use Pascal's triangle for small n and k values.; Precompute factorials and inverse factorials for larger n modulo a prime.
//   • Pitfalls: Overflow with large factorials if not using modular arithmetic.; Division by zero when computing inverse modulo if modulus is not prime.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// -  
// Kth order statistic in O(N) (array, enumeration)
//   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
//   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
//   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
//   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
//   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} rating
 * @return {number}
 */
var numTeams = function(rating) {
    let count = 0;
    const n = rating.length;
    
    for (let j = 1; j < n - 1; j++) {
        let leftSmaller = 0, leftGreater = 0;
        let rightSmaller = 0, rightGreater = 0;
        
        for (let i = 0; i < j; i++) {
            if (rating[i] < rating[j]) {
                leftSmaller++;
            } else if (rating[i] > rating[j]) {
                leftGreater++;
            }
        }
        
        for (let k = j + 1; k < n; k++) {
            if (rating[k] < rating[j]) {
                rightSmaller++;
            } else if (rating[k] > rating[j]) {
                rightGreater++;
            }
        }
        
        count += leftSmaller * rightGreater + leftGreater * rightSmaller;
    }
    
    return count;
};
