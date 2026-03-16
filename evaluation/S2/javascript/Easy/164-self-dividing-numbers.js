// Source: https://leetcode.com/problems/self-dividing-numbers/   |   Difficulty: Easy
//
// Problem Description:
// A self-dividing number is a number that is divisible by every digit it contains.
//
//
// 	For example, 128 is a self-dividing number because 128 % 1 == 0, 128 % 2 == 0, and 128 % 8 == 0.
//
//
// A self-dividing number is not allowed to contain the digit zero.
//
// Given two integers left and right, return a list of all the self-dividing numbers in the range [left, right] (both inclusive).
//
// Example:
// Input: left = 1, right = 22
// Output: [1,2,3,4,5,6,7,8,9,11,12,15,22]
//
// Constraints:
// 1 <= left <= right <= 104
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// - Manacher's Algorithm - Finding all sub-p (string, array, two-pointers, simulation)
//   • When to use: When you need to find all palindromic substrings or the longest palindromic substring in a given string efficiently. It is particularly useful for achieving linear time complexity by leveraging symmetry.
//   • Idea: Manacher's algorithm finds all palindromic substrings in a string by expanding around centers and utilizing symmetry to avoid redundant comparisons. It achieves a linear time complexity of O(N) by maintaining the rightmost boundary of the longest palindrome found so far.
//   • Invariants: For any index k < i, d[k] correctly stores the radius of the longest palindrome centered at k.; The pair (l, r) always represents the exclusive boundaries of the palindrome that extends furthest to the right among all processed centers.
//   • Tips: Pre-process the string with delimiters (e.g., '#') to uniformly handle both odd and even length palindromes.; Leverage symmetry: for a center 'i' within the current rightmost palindrome, its mirror 'j' provides a lower bound for the palindrome length at 'i'.
//   • Pitfalls: Incorrectly handling boundary conditions when the mirror palindrome extends beyond the current rightmost palindrome.; Forgetting to update the 'l' and 'r' boundaries after finding a new palindrome that extends further to the right.
// - Linear Sieve (array, sieve)
//   • When to use: Use when you need to find all prime numbers up to a given limit N, or compute the least prime factor for all numbers in that range, efficiently in linear time.
//   • Idea: The Linear Sieve finds all prime numbers up to N in O(N) time by ensuring each composite number is marked exactly once by its least prime factor. It also computes the least prime factor for every number up to N.
//   • Invariants: The 'primes' list always contains all prime numbers found so far in increasing order.; lpf[i] stores the least prime factor of 'i' if 'i' is composite, or 'i' itself if 'i' is prime.
//   • Tips: Store the least prime factor (LPF) for each number in an array.; Maintain a dynamically growing list of primes found so far.
//   • Pitfalls: Incorrectly marking multiples can lead to O(N log log N) or worse complexity.; Forgetting to store the least prime factor can break the linear time guarantee.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} left
 * @param {number} right
 * @return {number[]}
 */
var selfDividingNumbers = function(left, right) {
    const result = [];
    
    for (let num = left; num <= right; num++) {
        if (isSelfDividing(num)) {
            result.push(num);
        }
    }
    
    return result;
    
    function isSelfDividing(num) {
        let temp = num;
        
        while (temp > 0) {
            const digit = temp % 10;
            if (digit === 0 || num % digit !== 0) {
                return false;
            }
            temp = Math.floor(temp / 10);
        }
        
        return true;
    }
};
