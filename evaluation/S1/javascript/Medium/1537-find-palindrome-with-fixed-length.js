// Source: https://leetcode.com/problems/find-palindrome-with-fixed-length/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array queries and a positive integer intLength, return an array answer where answer[i] is either the queries[i]th smallest positive palindrome of length intLength or -1 if no such palindrome exists.
//
// A palindrome is a number that reads the same backwards and forwards. Palindromes cannot have leading zeros.
//
// Example:
// Input: queries = [1,2,3,4,5,90], intLength = 3
// Output: [101,111,121,131,141,999]
// Explanation:
// The first few palindromes of length 3 are:
// 101, 111, 121, 131, 141, 151, 161, 171, 181, 191, 202, ...
// The 90th palindrome of length 3 is 999.
//
// Constraints:
// 1 <= queries.length <= 5 * 104
// 	1 <= queries[i] <= 109
// 	1 <= intLength <= 15
//
// Helpful references (internal KB):
// - Manacher's Algorithm - Finding all sub-p (string, array, simulation, enumeration)
//   • When to use: When you need to find all palindromic substrings or the longest palindromic substring within a given string efficiently. It is particularly useful for achieving linear time complexity for this task.
//   • Idea: Manacher's algorithm finds all maximal palindromic substrings centered at each position in a string by leveraging symmetry and previously computed results. It achieves an optimal O(N) time complexity.
//   • Invariants: d_odd[i] stores the radius of the longest odd-length palindrome centered at i.; The (l, r) interval always defines the rightmost palindrome found so far.
//   • Tips: Preprocess the string with delimiters to unify odd and even length palindromes.; Maintain the current rightmost boundary `r` of the largest palindrome found.
//   • Pitfalls: Forgetting to update the `(l, r)` boundaries after processing each center.; Incorrectly calculating mirror positions or handling boundary cases for `i > r`.
// - Modular Multiplicative Inverse (array, number, prefix-sum, mod-exp)
//   • When to use: Use when needing to compute modular inverses for multiple numbers in an array or a range, especially when efficiency is critical, by leveraging prefix and suffix products to reduce inverse computations.
//   • Idea: This technique efficiently computes modular inverses for multiple numbers by transforming individual inverse calculations into a product of prefix, suffix, and a single overall inverse. It achieves O(N + log M) complexity for an array or O(M) for a range.
//   • Invariants: For 0 <= i < N, prefix_products[i] holds (arr[0] * ... * arr[i-1]) % m.; For 0 <= i < N, suffix_products[i] holds (arr[i+1] * ... * arr[N-1]) % m.
//   • Tips: Precompute prefix products and suffix products of the array elements modulo m.; Calculate the modular inverse of the total product of all elements once using modular exponentiation.
//   • Pitfalls: Ensure all numbers for which an inverse is sought are coprime to the modulus m.; Watch for off-by-one errors when calculating prefix and suffix product indices.
// - Generating all K-combinations (bitset, enumeration)
//   • When to use: When all subsets of a fixed size K need to be generated, either in lexicographical order or such that successive combinations differ by exactly one element.
//   • Idea: This algorithm enumerates all K-combinations from a set, either in lexicographical order or using a Gray code approach where adjacent combinations differ by a single element. It typically runs in O(N choose K) time, generating each combination in O(K) or O(1) amortized time.
//   • Invariants: Each generated combination contains exactly K distinct elements.; All elements within a combination are unique and from the original set.
//   • Tips: For lexicographical generation, find the rightmost element that can be incremented without exceeding its maximum possible value.; After incrementing an element, set all subsequent elements to their minimum valid values.
//   • Pitfalls: Incorrectly handling boundary conditions for the rightmost element or its maximum value.; Off-by-one errors when assigning subsequent elements after an increment.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} queries
 * @param {number} intLength
 * @return {number[]}
 */
var kthPalindrome = function(queries, intLength) {
    const results = [];
    const halfLength = Math.floor((intLength + 1) / 2);
    const start = BigInt(10) ** BigInt(halfLength - 1);

    for (const query of queries) {
        const leftHalfNum = start + BigInt(query - 1);
        const leftHalfStr = leftHalfNum.toString();

        let palindromeStr;
        if (intLength % 2 === 0) {
            // Even length palindrome
            const rightHalfStr = leftHalfStr.split('').reverse().join('');
            palindromeStr = leftHalfStr + rightHalfStr;
        } else {
            // Odd length palindrome
            const rightHalfStr = leftHalfStr.slice(0, -1).split('').reverse().join('');
            palindromeStr = leftHalfStr + rightHalfStr;
        }

        const palindromeNum = BigInt(palindromeStr);
        // Check if the palindrome exceeds the maximum possible value for the given length
        if (palindromeStr.length > intLength) {
            results.push(-1);
        } else {
            results.push(Number(palindromeNum));
        }
    }

    return results;
};
