// Source: https://leetcode.com/problems/largest-3-same-digit-number-in-string/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string num representing a large integer. An integer is good if it meets the following conditions:
//
//
// 	It is a substring of num with length 3.
// 	It consists of only one unique digit.
//
//
// Return the maximum good integer as a string or an empty string "" if no such integer exists.
//
// Note:
//
//
// 	A substring is a contiguous sequence of characters within a string.
// 	There may be leading zeroes in num or a good integer.
//
// Example:
// Input: num = "6777133339"
// Output: "777"
// Explanation: There are two distinct good integers: "777" and "333".
// "777" is the largest, so we return "777".
//
// Constraints:
// 3 <= num.length <= 1000
// 	num only consists of digits.
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
 * @param {string} num
 * @return {string}
 */
var largestGoodInteger = function(num) {
    let maxGoodInteger = "";
    
    for (let i = 0; i <= num.length - 3; i++) {
        const substring = num.substring(i, i + 3);
        if (substring[0] === substring[1] && substring[1] === substring[2]) {
            if (maxGoodInteger === "" || substring > maxGoodInteger) {
                maxGoodInteger = substring;
            }
        }
    }
    
    return maxGoodInteger;
};
