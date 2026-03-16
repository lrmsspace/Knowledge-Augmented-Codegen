// Source: https://leetcode.com/problems/reverse-vowels-of-a-string/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s, reverse only all the vowels in the string and return it.
//
// The vowels are 'a', 'e', 'i', 'o', and 'u', and they can appear in both lower and upper cases, more than once.
//
// Example:
// Input: s = "IceCreAm"
//
// Output: "AceCreIm"
//
// Explanation:
//
// The vowels in s are ['I', 'e', 'e', 'A']. On reversing the vowels, s becomes "AceCreIm".
//
// Constraints:
// 1 <= s.length <= 3 * 105
// 	s consist of printable ASCII characters.
//

/**
 * @param {string} s
 * @return {string}
 */
var reverseVowels = function(s) {
    const vowels = new Set(['a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U']);
    const chars = s.split('');
    let left = 0;
    let right = chars.length - 1;
    while (left < right) {
        if (!vowels.has(chars[left])) {
            left++;
            continue;
        }
        if (!vowels.has(chars[right])) {
            right--;
            continue;
        }
        const temp = chars[left];
        chars[left] = chars[right];
        chars[right] = temp;
        left++;
        right--;
    }
    return chars.join('');
};