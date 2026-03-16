// Source: https://leetcode.com/problems/excel-sheet-column-number/   |   Difficulty: Easy
//
// Problem Description:
// Given a string columnTitle that represents the column title as appears in an Excel sheet, return its corresponding column number.
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
// Input: columnTitle = "A"
// Output: 1
//
// Constraints:
// 1 <= columnTitle.length <= 7
// 	columnTitle consists only of uppercase English letters.
// 	columnTitle is in the range ["A", "FXSHRXW"].
//

/**
 * @param {string} columnTitle
 * @return {number}
 */
var titleToNumber = function(columnTitle) {
    let result = 0;
    for (let i = 0; i < columnTitle.length; i++) {
        const charCode = columnTitle.charCodeAt(i) - 64; // 'A' is 65 in ASCII
        result = result * 26 + charCode;
    }
    return result;
};
