// Source: https://leetcode.com/problems/swap-adjacent-in-lr-string/   |   Difficulty: Medium
//
// Problem Description:
// In a string composed of 'L', 'R', and 'X' characters, like "RXXLRXRXL", a move consists of either replacing one occurrence of "XL" with "LX", or replacing one occurrence of "RX" with "XR". Given the starting string start and the ending string result, return True if and only if there exists a sequence of moves to transform start to result.
//
// Example:
// Input: start = "RXXLRXRXL", result = "XRLXXRRLX"
// Output: true
// Explanation: We can transform start to result following these steps:
// RXXLRXRXL ->
// XRXLRXRXL ->
// XRLXRXRXL ->
// XRLXXRRXL ->
// XRLXXRRLX
//
// Constraints:
// 1 <= start.length <= 104
// 	start.length == result.length
// 	Both start and result will only consist of characters in 'L', 'R', and 'X'.
//

/**
 * @param {string} start
 * @param {string} result
 * @return {boolean}
 */
var canTransform = function(start, result) {
    const n = start.length;
    let i = 0;
    let j = 0;
    while (i < n || j < n) {
        while (i < n && start[i] === 'X') i++;
        while (j < n && result[j] === 'X') j++;

        if (i === n && j === n) return true;
        if (i === n || j === n) return false;
        if (start[i] !== result[j]) return false;
        if (start[i] === 'L' && i < j) return false;
        if (start[i] === 'R' && i > j) return false;
        i++;
        j++;
    }   
    return true;
};
