// Source: https://leetcode.com/problems/number-of-beautiful-integers-in-the-range/   |   Difficulty: Hard
//
// Problem Description:
// You are given positive integers low, high, and k.
//
// A number is beautiful if it meets both of the following conditions:
//
//
// 	The count of even digits in the number is equal to the count of odd digits.
// 	The number is divisible by k.
//
//
// Return the number of beautiful integers in the range [low, high].
//
// Example:
// Input: low = 10, high = 20, k = 3
// Output: 2
// Explanation: There are 2 beautiful integers in the given range: [12,18]. 
// - 12 is beautiful because it contains 1 odd digit and 1 even digit, and is divisible by k = 3.
// - 18 is beautiful because it contains 1 odd digit and 1 even digit, and is divisible by k = 3.
// Additionally we can see that:
// - 16 is not beautiful because it is not divisible by k = 3.
// - 15 is not beautiful because it does not contain equal counts even and odd digits.
// It can be shown that there are only 2 beautiful integers in the given range.
//
// Constraints:
// 0 < low <= high <= 109
// 	0 < k <= 20
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
 * @param {number} low
 * @param {number} high
 * @param {number} k
 * @return {number}
 */
var numberOfBeautifulIntegers = function(low, high, k) {
    
    const countBeautiful = (num) => {
        const digits = String(num).split('').map(Number);
        const n = digits.length;
        const memo = new Map();
        
        const dp = (idx, tight, sum, count) => {
            if (idx === n) {
                return sum % k === 0 && count % 2 === 0 ? 1 : 0;
            }
            const key = `${idx}-${tight}-${sum}-${count}`;
            if (memo.has(key)) {
                return memo.get(key);
            }
            const maxDigit = tight ? digits[idx] : 9;
            let result = 0;
            for (let digit = 0; digit <= maxDigit; digit++) {
                const newSum = sum + digit;
                const newCount = count + (digit === 0 ? 0 : 1);
                result += dp(idx + 1, tight && digit === maxDigit, newSum, newCount);
            }
            memo.set(key, result);
            return result;
        };
        return dp(0, true, 0, 0);
    
    
    };
    