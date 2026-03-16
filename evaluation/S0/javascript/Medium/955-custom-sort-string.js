// Source: https://leetcode.com/problems/custom-sort-string/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings order and s. All the characters of order are unique and were sorted in some custom order previously.
//
// Permute the characters of s so that they match the order that order was sorted. More specifically, if a character x occurs before a character y in order, then x should occur before y in the permuted string.
//
// Return any permutation of s that satisfies this property.
//
// Example:
// Input:   order = "cba", s = "abcd" 
//
// Output:   "cbad" 
//
// Explanation:  "a", "b", "c" appear in order, so the order of "a", "b", "c" should be "c", "b", and "a".
//
// Since "d" does not appear in order, it can be at any position in the returned string. "dcba", "cdba", "cbda" are also valid outputs.
//
// Constraints:
// 1 <= order.length <= 26
// 	1 <= s.length <= 200
// 	order and s consist of lowercase English letters.
// 	All the characters of order are unique.
//

/**
 * @param {string} order
 * @param {string} s
 * @return {string}
 */
var customSortString = function(order, s) {
    const orderMap = new Map();
    for (let i = 0; i < order.length; i++) {
        orderMap.set(order[i], i);
    }
    const chars = s.split('');
    chars.sort((a, b) => {
        const indexA = orderMap.has(a) ? orderMap.get(a) : Infinity;
        const indexB = orderMap.has(b) ? orderMap.get(b) : Infinity;
        return indexA - indexB;
    });
    return chars.join('');
};