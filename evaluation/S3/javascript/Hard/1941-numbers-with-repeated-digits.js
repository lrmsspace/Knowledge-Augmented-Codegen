// Source: https://leetcode.com/problems/numbers-with-repeated-digits/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer n, return the number of positive integers in the range [1, n] that have at least one repeated digit.
//
// Example:
// Input: n = 20
// Output: 1
// Explanation: The only positive number (<= 20) with at least 1 repeated digit is 11.
//
// Constraints:
// 1 <= n <= 109
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Digit DP (array, number, digit-dp)
//   • When to use: When counting numbers within a given range [A, B] that satisfy certain digit-based properties, or calculating a sum of such properties.
//   • Idea: Digit DP is a dynamic programming technique used to count numbers or calculate sums of properties for numbers within a given range, based on their digits. It typically involves a recursive function with memoization, processing digits from most significant to least significant, achieving a time complexity of O(log(N) * S * T) where S is sum/state range and T is tight constraint.
//   • Invariants: The `idx` parameter always represents the current digit position being processed, from most significant to least significant.; The `tight` boolean parameter accurately indicates if the current digit choice is restricted by the original number's corresponding digit.
//   • Tips: Handle leading zeros carefully, often with a dedicated boolean state in the DP function.; Use a 'tight' or 'limit' boolean parameter to manage the upper bound constraint imposed by the original number.
//   • Pitfalls: Incorrectly handling the 'tight' constraint can lead to overcounting or undercounting.; Forgetting to reset the memoization table for each new query or test case, especially in competitive programming.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} n
 * @return {number}
 */
var numDupDigitsAtMostN = function(n) {
    // Helper function to count numbers with unique digits up to a given limit
    const countUniqueDigits = (limit) => {
        const digits = String(limit).split('').map(Number);
        const len = digits.length;
        let count = 0;  
        // Count numbers with unique digits of length less than len
        for (let i = 1; i < len; i++) {
            count += 9 * perm(9, i - 1); // First digit can be 1-9, then choose from remaining digits
        }   
        // Count numbers with unique digits of length equal to len
        const used = new Set(); 
        for (let i = 0; i < len; i++) {
            const digit = digits[i];
            for (let d = (i === 0 ? 1 : 0); d < digit; d++) {
                if (!used.has(d)) {
                    count += perm(10 - (i + 1), len - (i + 1)); // Choose remaining digits for the rest of the number
                }
                    
            if (used.has(digit)) break; // If digit is already used, stop counting
            used.add(digit);
            }
        return count;
    }   

    // Helper function to calculate permutations P(n, k) = n! / (n-k)!
    const perm = (n, k) => {
        let result = 1;
        for (let i = 0; i < k; i++) {
            result *= (n - i);
        }
        return result;
    }
    
};
