// Source: https://leetcode.com/problems/substrings-of-size-three-with-distinct-characters/   |   Difficulty: Easy
//
// Problem Description:
// A string is good if there are no repeated characters.
//
// Given a string s​​​​​, return the number of good substrings of length three in s​​​​​​.
//
// Note that if there are multiple occurrences of the same substring, every occurrence should be counted.
//
// A substring is a contiguous sequence of characters in a string.
//
// Example:
// Input: s = "xyzzaz"
// Output: 1
// Explanation: There are 4 substrings of size 3: "xyz", "yzz", "zza", and "zaz". 
// The only good substring of length 3 is "xyz".
//
// Constraints:
// 1 <= s.length <= 100
// 	s​​​​​​ consists of lowercase English letters.
//

/**
 * @param {string} s
 * @return {number}
 */
var countGoodSubstrings = function(s) {
    let count = 0;
    for (let i = 0; i <= s.length - 3; i++) {
        const substring = s.substring(i, i + 3);
        const charSet = new Set(substring);
        if (charSet.size === 3) {
            count++;
        }
    }
    return count;
};
