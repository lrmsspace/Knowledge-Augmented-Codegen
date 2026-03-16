// Source: https://leetcode.com/problems/remove-digit-from-number-to-maximize-result/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string number representing a positive integer and a character digit.
//
// Return the resulting string after removing exactly one occurrence of digit from number such that the value of the resulting string in decimal form is maximized. The test cases are generated such that digit occurs at least once in number.
//
// Example:
// Input: number = "123", digit = "3"
// Output: "12"
// Explanation: There is only one '3' in "123". After removing '3', the result is "12".
//
// Constraints:
// 2 <= number.length <= 100
// 	number consists of digits from '1' to '9'.
// 	digit is a digit from '1' to '9'.
// 	digit occurs at least once in number.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} number
 * @param {character} digit
 * @return {string}
 */
var removeDigit = function(number, digit) {
    let maxResult = "";
    for (let i = 0; i < number.length; i++) {
        if (number[i] === digit) {
            const newNumber = number.slice(0, i) + number.slice(i + 1);
            if (newNumber > maxResult) {
                maxResult = newNumber;
            }
        }
    }
    return maxResult;   
};
