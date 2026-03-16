// Source: https://leetcode.com/problems/longest-chunked-palindrome-decomposition/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string text. You should split it to k substrings (subtext1, subtext2, ..., subtextk) such that:
//
//
// 	subtexti is a non-empty string.
// 	The concatenation of all the substrings is equal to text (i.e., subtext1 + subtext2 + ... + subtextk == text).
// 	subtexti == subtextk - i + 1 for all valid values of i (i.e., 1 <= i <= k).
//
//
// Return the largest possible value of k.
//
// Example:
// Input: text = "ghiabcdefhelloadamhelloabcdefghi"
// Output: 7
// Explanation: We can split the string on "(ghi)(abcdef)(hello)(adam)(hello)(abcdef)(ghi)".
//
// Constraints:
// 1 <= text.length <= 1000
// 	text consists only of lowercase English characters.
//

/**
 * @param {string} text
 * @return {number}
 */
var longestDecomposition = function(text) {
    const n = text.length;
    let left = 0;
    let right = n - 1;
    let count = 0;
    while (left <= right) {
        let found = false;
        for (let length = 1; left + length - 1 < right - length + 1; length++) {
            const leftSubstring = text.substring(left, left + length);
            const rightSubstring = text.substring(right - length + 1, right + 1);
            if (leftSubstring === rightSubstring) {
                count += 2;
                left += length;
                right -= length;
                found = true;
                break;
            }
        }
        if (!found) {
            count++;
            break;
        }
    }
    return count;
};
