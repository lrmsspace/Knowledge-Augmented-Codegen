// Source: https://leetcode.com/problems/ambiguous-coordinates/   |   Difficulty: Medium
//
// Problem Description:
// We had some 2-dimensional coordinates, like "(1, 3)" or "(2, 0.5)". Then, we removed all commas, decimal points, and spaces and ended up with the string s.
//
//
// 	For example, "(1, 3)" becomes s = "(13)" and "(2, 0.5)" becomes s = "(205)".
//
//
// Return a list of strings representing all possibilities for what our original coordinates could have been.
//
// Our original representation never had extraneous zeroes, so we never started with numbers like "00", "0.0", "0.00", "1.0", "001", "00.01", or any other number that can be represented with fewer digits. Also, a decimal point within a number never occurs without at least one digit occurring before it, so we never started with numbers like ".1".
//
// The final answer list can be returned in any order. All coordinates in the final answer have exactly one space between them (occurring after the comma.)
//
// Example:
// Input: s = "(123)"
// Output: ["(1, 2.3)","(1, 23)","(1.2, 3)","(12, 3)"]
//
// Constraints:
// 4 <= s.length <= 12
// 	s[0] == '(' and s[s.length - 1] == ')'.
// 	The rest of s are digits.
//

/**
 * @param {string} s
 * @return {string[]}
 */
var ambiguousCoordinates = function(s) {
    const generateNumbers = (s) => {
        const results = [];
        const n = s.length;
        if (n === 1 || s[0] !== '0') {
            results.push(s);
        }
        for (let i = 1; i < n; i++) {
            const left = s.slice(0, i);
            const right = s.slice(i);
            if ((left[0] === '0' && left.length > 1) || (right[right.length - 1] === '0')) {
                continue;
            }
            results.push(left + '.' + right);
        }
        return results;
    };

    const result = [];
    const str = s.slice(1, -1);
    const n = str.length;
    for (let i = 1; i < n; i++) {
        const leftPart = str.slice(0, i);
        const rightPart = str.slice(i);
        const leftNumbers = generateNumbers(leftPart);
        const rightNumbers = generateNumbers(rightPart);
        for (const leftNum of leftNumbers) {
            for (const rightNum of rightNumbers) {
                result.push(`(${leftNum}, ${rightNum})`);
            }
        }
    }
    return result;  
};
