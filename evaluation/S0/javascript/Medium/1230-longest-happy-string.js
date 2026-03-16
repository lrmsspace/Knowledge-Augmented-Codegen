// Source: https://leetcode.com/problems/longest-happy-string/   |   Difficulty: Medium
//
// Problem Description:
// A string s is called happy if it satisfies the following conditions:
//
//
// 	s only contains the letters 'a', 'b', and 'c'.
// 	s does not contain any of "aaa", "bbb", or "ccc" as a substring.
// 	s contains at most a occurrences of the letter 'a'.
// 	s contains at most b occurrences of the letter 'b'.
// 	s contains at most c occurrences of the letter 'c'.
//
//
// Given three integers a, b, and c, return the longest possible happy string. If there are multiple longest happy strings, return any of them. If there is no such string, return the empty string "".
//
// A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: a = 1, b = 1, c = 7
// Output: "ccaccbcc"
// Explanation: "ccbccacc" would also be a correct answer.
//
// Constraints:
// 0 <= a, b, c <= 100
// 	a + b + c > 0
//

/**
 * @param {number} a
 * @param {number} b
 * @param {number} c
 * @return {string}
 */
var longestDiverseString = function(a, b, c) {
    const heap = [];
    if (a > 0) heap.push([-a, 'a']);
    if (b > 0) heap.push([-b, 'b']);
    if (c > 0) heap.push([-c, 'c']);
    const result = [];
    while (heap.length) {
        heap.sort((x, y) => x[0] - y[0]);
        let [count, char] = heap.shift();
        if (result.length >= 2 && result[result.length - 1] === char && result[result.length - 2] === char) {
            if (heap.length === 0) break;
            let [nextCount, nextChar] = heap.shift();
            result.push(nextChar);
            if (nextCount + 1 < 0) heap.push([nextCount + 1, nextChar]);
            heap.push([count, char]);
        } else {
            result.push(char);
            if (count + 1 < 0) heap.push([count + 1, char]);
        }
    }
    return result.join('');
        
};
