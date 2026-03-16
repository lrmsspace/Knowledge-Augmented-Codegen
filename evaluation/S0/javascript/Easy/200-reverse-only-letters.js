// Source: https://leetcode.com/problems/reverse-only-letters/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s, reverse the string according to the following rules:
//
//
// 	All the characters that are not English letters remain in the same position.
// 	All the English letters (lowercase or uppercase) should be reversed.
//
//
// Return s after reversing it.
//
// Example:
// Input: s = "ab-cd"
// Output: "dc-ba"
//
// Constraints:
// 1 <= s.length <= 100
// 	s consists of characters with ASCII values in the range [33, 122].
// 	s does not contain '\"' or '\\'.
//

/**
 * @param {string} s
 * @return {string}
 */
var reverseOnlyLetters = function(s) {
    const isLetter = (c) => /[a-zA-Z]/.test(c);     
    let arr = s.split('');   
    let left = 0;
    let right = arr.length - 1; 
    while (left < right) {
        if (!isLetter(arr[left])) {
            left++;
        } else if (!isLetter(arr[right])) {
            right--;
        } else {
            [arr[left], arr[right]] = [arr[right], arr[left]];
            left++;
            right--;
        }
    }
    return arr.join('');
};