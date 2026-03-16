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
// - Digit DP (array, number, digit-dp)
//   • When to use: When counting numbers within a given range [A, B] that satisfy certain digit-based properties, or calculating a sum of such properties.
//   • Idea: Digit DP is a dynamic programming technique used to count numbers or calculate sums of properties for numbers within a given range, based on their digits. It typically involves a recursive function with memoization, processing digits from most significant to least significant, achieving a time complexity of O(log(N) * S * T) where S is sum/state range and T is tight constraint.
//   • Invariants: The `idx` parameter always represents the current digit position being processed, from most significant to least significant.; The `tight` boolean parameter accurately indicates if the current digit choice is restricted by the original number's corresponding digit.
//   • Tips: Handle leading zeros carefully, often with a dedicated boolean state in the DP function.; Use a 'tight' or 'limit' boolean parameter to manage the upper bound constraint imposed by the original number.
//   • Pitfalls: Incorrectly handling the 'tight' constraint can lead to overcounting or undercounting.; Forgetting to reset the memoization table for each new query or test case, especially in competitive programming.
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
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
        let num = BigInt(i);
        while (num % 10n === 0n) {
            trailingZeros++;
            num /= 10n;
        }
        product = (product * num) % 1000000000000n; // Keep only last 12 digits to avoid overflow
    }
    let productStr = product.toString();
    let d = productStr.length;
    if (d > 10) {
        return `${productStr.slice(0, 5)}...${productStr.slice(-5)}e${trailingZeros}`;
    } else {
        return `${productStr}e${trailingZeros}`;
    }
    
            
};
