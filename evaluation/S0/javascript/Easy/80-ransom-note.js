// Source: https://leetcode.com/problems/ransom-note/   |   Difficulty: Easy
//
// Problem Description:
// Given two strings ransomNote and magazine, return true if ransomNote can be constructed by using the letters from magazine and false otherwise.
//
// Each letter in magazine can only be used once in ransomNote.
//
// Example:
// Input: ransomNote = "a", magazine = "b"
// Output: false
//
// Constraints:
// 1 <= ransomNote.length, magazine.length <= 105
// 	ransomNote and magazine consist of lowercase English letters.
//

/**
 * @param {string} ransomNote
 * @param {string} magazine
 * @return {boolean}
 */
var canConstruct = function(ransomNote, magazine) {
    const charCount = new Array(26).fill(0);
    for (const char of magazine) {
        charCount[char.charCodeAt(0) - 97]++;
    }
    for (const char of ransomNote) {
        if (--charCount[char.charCodeAt(0) - 97] < 0) {
            return false;
        }
    }
    return true;
};