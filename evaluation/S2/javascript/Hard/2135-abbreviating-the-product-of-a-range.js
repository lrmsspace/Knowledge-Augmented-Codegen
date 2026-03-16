// Source: https://leetcode.com/problems/abbreviating-the-product-of-a-range/   |   Difficulty: Hard
//
// Problem Description:
// You are given two positive integers left and right with left <= right. Calculate the product of all integers in the inclusive range [left, right].
//
// Since the product may be very large, you will abbreviate it following these steps:
//
//
// 	Count all trailing zeros in the product and remove them. Let us denote this count as C.
//
// 	
// 		For example, there are 3 trailing zeros in 1000, and there are 0 trailing zeros in 546.
// 	
// 	
// 	Denote the remaining number of digits in the product as d. If d > 10, then express the product as <pre>...<suf> where <pre> denotes the first 5 digits of the product, and <suf> denotes the last 5 digits of the product after removing all trailing zeros. If d <= 10, we keep it unchanged.
// 	
// 		For example, we express 1234567654321 as 12345...54321, but 1234567 is represented as 1234567.
// 	
// 	
// 	Finally, represent the product as a string "<pre>...<suf>eC".
// 	
// 		For example, 12345678987600000 will be represented as "12345...89876e5".
// 	
// 	
//
//
// Return a string denoting the abbreviated product of all integers in the inclusive range [left, right].
//
// Example:
// Input: left = 1, right = 4
// Output: "24e0"
// Explanation: The product is 1 × 2 × 3 × 4 = 24.
// There are no trailing zeros, so 24 remains the same. The abbreviation will end with "e0".
// Since the number of digits is 2, which is less than 10, we do not have to abbreviate it further.
// Thus, the final representation is "24e0".
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
// - Factorial modulo 
// p (number, counting)
//   • When to use: Use this when calculating factorials or expressions involving factorials in fractions modulo a prime `p`, especially when `p` is small and factors of `p` need to be explicitly handled for cancellation.
//   • Idea: This technique computes `n! mod p` by separating the factors of `p` from the remaining product, allowing for correct modular division in expressions like binomial coefficients.
//   • Invariants: The running product `P` always holds the value of `(i-1)!` with all factors of `p` removed, modulo `p`.; The variable `count_p` accurately stores the total exponent of `p` in `(i-1)!`.
//   • Tips: Precompute factorials and inverse factorials modulo `p` for terms not divisible by `p`.; Use Fermat's Little Theorem to find modular inverses when `p` is prime.
//   • Pitfalls: Incorrectly applying modular inverse when the divisor is a multiple of `p` or `p` is not prime.; Forgetting to handle the exponent of `p` separately, which can lead to an incorrect zero result.
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
 * @return {string}
 */
var abbreviateProduct = function(left, right) {
    let product = 1n;
    let trailingZeros = 0;
    for (let i = left; i <= right; i++) {
        product *= BigInt(i);
        while (product % 10n === 0n) {
            trailingZeros++;
            product /= 10n;
        }
    }
    const productStr = product.toString();
    if (productStr.length > 10) {
        return `${productStr.substring(0, 5)}...${productStr.substring(productStr.length - 5)} ${trailingZeros}`;
    }
    return `${productStr} ${trailingZeros}`;
};
