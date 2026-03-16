// Source: https://leetcode.com/problems/minimum-number-of-frogs-croaking/   |   Difficulty: Medium
//
// Problem Description:
// You are given the string croakOfFrogs, which represents a combination of the string "croak" from different frogs, that is, multiple frogs can croak at the same time, so multiple "croak" are mixed.
//
// Return the minimum number of different frogs to finish all the croaks in the given string.
//
// A valid "croak" means a frog is printing five letters 'c', 'r', 'o', 'a', and 'k' sequentially. The frogs have to print all five letters to finish a croak. If the given string is not a combination of a valid "croak" return -1.
//
// Example:
// Input: croakOfFrogs = "croakcroak"
// Output: 1 
// Explanation: One frog yelling "croak" twice.
//
// Constraints:
// 1 <= croakOfFrogs.length <= 105
// 	croakOfFrogs is either 'c', 'r', 'o', 'a', or 'k'.
//

/**
 * @param {string} croakOfFrogs
 * @return {number}
 */
var minNumberOfFrogs = function(croakOfFrogs) {
    const count = { 'c': 0, 'r': 0, 'o': 0, 'a': 0, 'k': 0 };
    let frogs = 0;
    for (const char of croakOfFrogs) {
        count[char]++;
        if (char === 'c') {
            frogs = Math.max(frogs, count['c'] - count['k']);
        } else if (char === 'r') {
            if (count['r'] > count['c']) return -1;
        } else if (char === 'o') {
            if (count['o'] > count['r']) return -1;
        } else if (char === 'a') {
            if (count['a'] > count['o']) return -1;
        } else if (char === 'k') {
            if (count['k'] > count['a']) return -1;
        }
    }
    return (count['c'] === count['r'] && count['r'] === count['o'] && count['o'] === count['a'] && count['a'] === count['k']) ? frogs : -1;
        
};
