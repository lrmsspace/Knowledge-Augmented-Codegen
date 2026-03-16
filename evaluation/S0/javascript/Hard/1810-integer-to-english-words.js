// Source: https://leetcode.com/problems/integer-to-english-words/   |   Difficulty: Hard
//
// Problem Description:
// Convert a non-negative integer num to its English words representation.
//
// Example:
// Input: num = 123
// Output: "One Hundred Twenty Three"
//
// Constraints:
// 0 <= num <= 231 - 1
//

/**
 * @param {number} num
 * @return {string}
 */
var numberToWords = function(num) {
    
    if (num === 0) {
        return "Zero";
    }
    const below20 = ["", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"];
    const tens = ["", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"];
    const thousands = ["", "Thousand", "Million", "Billion"];
    let result = "";
    let i = 0;
    while (num > 0) {
        if (num % 1000 !== 0) {
            result = helper(num % 1000) + thousands[i] + " " + result;
        }
        num = Math.floor(num / 1000);
        i++;
    }
    return result.trim();   
};
