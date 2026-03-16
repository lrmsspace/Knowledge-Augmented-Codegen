// Source: https://leetcode.com/problems/isomorphic-strings/   |   Difficulty: Easy
//
// Problem Description:
// Given two strings s and t, determine if they are isomorphic.
//
// Two strings s and t are isomorphic if the characters in s can be replaced to get t.
//
// All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character, but a character may map to itself.
//
// Example:
// Input: s = "egg", t = "add"
//
// Output: true
//
// Explanation:
//
// The strings s and t can be made identical by:
//
//
// 	Mapping 'e' to 'a'.
// 	Mapping 'g' to 'd'.
//
// Constraints:
// 1 <= s.length <= 5 * 104
// 	t.length == s.length
// 	s and t consist of any valid ascii character.
//

/**
 * @param {string} s
 * @param {string} t
 * @return {boolean}
 */
var isIsomorphic = function(s, t) {
    const mapSToT = new Map();
    const mapTToS = new Map();
    for (let i = 0; i < s.length; i++) {
        const charS = s[i];
        const charT = t[i];

        if (mapSToT.has(charS) && mapSToT.get(charS) !== charT) {
            return false;
        }
        if (mapTToS.has(charT) && mapTToS.get(charT) !== charS) {
            return false;
        }

        mapSToT.set(charS, charT);
        mapTToS.set(charT, charS);
    }
    return true;
};