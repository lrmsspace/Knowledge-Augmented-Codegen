// Source: https://leetcode.com/problems/find-the-original-typed-string-i/   |   Difficulty: Easy
//
// Problem Description:
// Alice is attempting to type a specific string on her computer. However, she tends to be clumsy and may press a key for too long, resulting in a character being typed multiple times.
//
// Although Alice tried to focus on her typing, she is aware that she may still have done this at most once.
//
// You are given a string word, which represents the final output displayed on Alice's screen.
//
// Return the total number of possible original strings that Alice might have intended to type.
//
// Example:
// Input: word = "abbcccc"
//
// Output: 5
//
// Explanation:
//
// The possible strings are: "abbcccc", "abbccc", "abbcc", "abbc", and "abcccc".
//
// Constraints:
// 1 <= word.length <= 100
// 	word consists only of lowercase English letters.
//

/**
 * @param {string} word
 * @return {number}
 */
var possibleStringCount = function(word) {
    let count = 1;
    let i = 0;
    while (i < word.length) {
        let j = i;
        while (j < word.length && word[j] === word[i]) {
            j++;
        }
        count += j - i - 1;
        i = j;
    }
    return count;
};