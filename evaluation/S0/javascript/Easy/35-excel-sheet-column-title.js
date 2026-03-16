// Source: https://leetcode.com/problems/excel-sheet-column-title/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer columnNumber, return its corresponding column title as it appears in an Excel sheet.
//
// For example:
//
//
// A -> 1
// B -> 2
// C -> 3
// ...
// Z -> 26
// AA -> 27
// AB -> 28 
// ...
//
// Example:
// Input: columnNumber = 1
// Output: "A"
//
// Constraints:
// 1 <= columnNumber <= 231 - 1
//

/**
 * @param {number} columnNumber
 * @return {string}
 */
var convertToTitle = function(columnNumber) {
    let result = '';
    while (columnNumber > 0) {
        columnNumber--; // Adjust for 0-indexing
        const remainder = columnNumber % 26;
        result = String.fromCharCode(remainder + 65) + result; // 65 is ASCII code for 'A'
        columnNumber = Math.floor(columnNumber / 26);
    }
    return result;
};
