// Source: https://leetcode.com/problems/reorganize-string/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, rearrange the characters of s so that any two adjacent characters are not the same.
//
// Return any possible rearrangement of s or return "" if not possible.
//
// Example:
// Input: s = "aab"
// Output: "aba"
//
// Constraints:
// 1 <= s.length <= 500
// 	s consists of lowercase English letters.
//

/**
 * @param {string} s
 * @return {string}
 */
var reorganizeString = function(s) {
    const charCount = {};
    for (const char of s) {
        charCount[char] = (charCount[char] || 0) + 1;
    }

    const maxHeap = new MaxPriorityQueue({ priority: x => x[1] });
    for (const char in charCount) {
        maxHeap.enqueue([char, charCount[char]]);
    }

    let result = "";
    let prevChar = null;
    let prevCount = 0;

    while (!maxHeap.isEmpty()) {
        const [char, count] = maxHeap.dequeue().element;
        result += char;

        if (prevChar !== null && prevCount > 0) {
            maxHeap.enqueue([prevChar, prevCount]);
        }

        prevChar = char;
        prevCount = count - 1;
    }

    return result.length === s.length ? result : "";
};