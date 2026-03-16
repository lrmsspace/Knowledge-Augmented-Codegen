// Source: https://leetcode.com/problems/zigzag-conversion/   |   Difficulty: Medium
//
// Problem Description:
// The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)
//
//
// P   A   H   N
// A P L S I I G
// Y   I   R
//
//
// And then read line by line: "PAHNAPLSIIGYIR"
//
// Write the code that will take a string and make this conversion given a number of rows:
//
//
// string convert(string s, int numRows);
//
// Example:
// Input: s = "PAYPALISHIRING", numRows = 3
// Output: "PAHNAPLSIIGYIR"
//
// Constraints:
// 1 <= s.length <= 1000
// 	s consists of English letters (lower-case and upper-case), ',' and '.'.
// 	1 <= numRows <= 1000
//

/**
 * @param {string} s
 * @param {number} numRows
 * @return {string}
 */
var convert = function(s, numRows) {
    if (numRows === 1 || s.length <= numRows) {
        return s;
    }

    let rows = new Array(Math.min(numRows, s.length)).fill("");
    let currentRow = 0;
    let goingDown = false;

    for (let char of s) {
        rows[currentRow] += char;

        if (currentRow === 0 || currentRow === numRows - 1) {
            goingDown = !goingDown;
        }

        currentRow += goingDown ? 1 : -1;
    }

    return rows.join("");   
};
