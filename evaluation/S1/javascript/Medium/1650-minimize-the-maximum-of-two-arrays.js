// Source: https://leetcode.com/problems/minimize-the-maximum-of-two-arrays/   |   Difficulty: Medium
//
// Problem Description:
// We have two arrays arr1 and arr2 which are initially empty. You need to add positive integers to them such that they satisfy all the following conditions:
//
//
// 	arr1 contains uniqueCnt1 distinct positive integers, each of which is not divisible by divisor1.
// 	arr2 contains uniqueCnt2 distinct positive integers, each of which is not divisible by divisor2.
// 	No integer is present in both arr1 and arr2.
//
//
// Given divisor1, divisor2, uniqueCnt1, and uniqueCnt2, return the minimum possible maximum integer that can be present in either array.
//
// Example:
// Input: divisor1 = 2, divisor2 = 7, uniqueCnt1 = 1, uniqueCnt2 = 3
// Output: 4
// Explanation: 
// We can distribute the first 4 natural numbers into arr1 and arr2.
// arr1 = [1] and arr2 = [2,3,4].
// We can see that both arrays satisfy all the conditions.
// Since the maximum value is 4, we return it.
//
// Constraints:
// 2 <= divisor1, divisor2 <= 105
// 	1 <= uniqueCnt1, uniqueCnt2 < 109
// 	2 <= uniqueCnt1 + uniqueCnt2 <= 109
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
// - Euclidean algorithm for computing the greatest common divisor (number, gcd)
//   • When to use: Use this algorithm to efficiently find the greatest common divisor of two or more integers, or as a subroutine for tasks like simplifying fractions or finding the least common multiple.
//   • Idea: The Euclidean algorithm is an efficient method for computing the greatest common divisor (GCD) of two non-negative integers by repeatedly applying the division algorithm. It operates in logarithmic time complexity, O(log min(a, b)).
//   • Invariants: The greatest common divisor of the current pair (a, b) remains constant and equal to the GCD of the original inputs.; The second number (b) is always non-negative.
//   • Tips: Handle the base case where one of the numbers is zero; gcd(a, 0) = a.; The algorithm works for any order of inputs; if a < b, the first step swaps them effectively.
//   • Pitfalls: Forgetting to take absolute values if negative inputs are possible, as GCD is typically defined for non-negative integers.; Incorrectly handling the zero input case, which can lead to infinite loops or incorrect results.
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} divisor1
 * @param {number} divisor2
 * @param {number} uniqueCnt1
 * @param {number} uniqueCnt2
 * @return {number}
 */
var minimizeSet = function(divisor1, divisor2, uniqueCnt1, uniqueCnt2) {
    const gcd = (a, b) => {
        while (b !== 0) {
            [a, b] = [b, a % b];
        }
        return a;
    };
    
    const lcm = (divisor1 * divisor2) / gcd(divisor1, divisor2);
    
    const countNotDivisible = (n) => {
        const divisibleByDivisor1 = Math.floor(n / divisor1);
        const divisibleByDivisor2 = Math.floor(n / divisor2);
        const divisibleByBoth = Math.floor(n / lcm);
        
        return n - divisibleByDivisor1 - divisibleByDivisor2 + divisibleByBoth;
    };
    
    let low = 1;
    let high = 2 * (uniqueCnt1 + uniqueCnt2); // A safe upper bound
    
    while (low < high) {
        const mid = Math.floor((low + high) / 2);
        
        if (countNotDivisible(mid) >= uniqueCnt1 + uniqueCnt2) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    
    return low;
};
