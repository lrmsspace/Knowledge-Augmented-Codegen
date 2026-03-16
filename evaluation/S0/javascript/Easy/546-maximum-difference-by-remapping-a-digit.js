// Source: https://leetcode.com/problems/maximum-difference-by-remapping-a-digit/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer num. You know that Bob will sneakily remap one of the 10 possible digits (0 to 9) to another digit.
//
// Return the difference between the maximum and minimum values Bob can make by remapping exactly one digit in num.
//
// 	The resulting number after remapping can contain leading zeroes.
//
// Example:
// Input: num = 11891
// Output: 99009
// Explanation: 
// To achieve the maximum value, Bob can remap the digit 1 to the digit 9 to yield 99899.
// To achieve the minimum value, Bob can remap the digit 1 to the digit 0, yielding 890.
// The difference between these two numbers is 99009.
//
// Constraints:
// 1 <= num <= 108
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} num
 * @return {number}
 */
var minMaxDifference = function(num) {  
    const numStr = num.toString();

    // Function to get the maximum number by remapping one digit
    const getMaxNumber = (str) => {
        for (const ch of str) {
            if (ch !== '9') {
                const remapped = str.split(ch).join('9');
                return parseInt(remapped, 10);
            }
        }
        return parseInt(str, 10); // All digits are '9'
    };
    // Function to get the minimum number by remapping one digit
    const getMinNumber = (str) => {
        const firstChar = str[0];
        if (firstChar !== '1') {
            const remapped = str.split(firstChar).join('1');
            return parseInt(remapped, 10);
        } else {
            for (let i = 1; i < str.length; i++) {
                const ch = str[i];
                if (ch !== '0' && ch !== '1') {
                    const remapped = str.split(ch).join('0');
                    return parseInt(remapped, 10);
                }
            }
            return parseInt(str, 10); // All digits are '0' or '1'
        }
    };
    const maxNum = getMaxNumber(numStr);
    const minNum = getMinNumber(numStr);
    return maxNum - minNum;
    
};
