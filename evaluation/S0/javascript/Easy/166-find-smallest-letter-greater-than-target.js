// Source: https://leetcode.com/problems/find-smallest-letter-greater-than-target/   |   Difficulty: Easy
//
// Problem Description:
// You are given an array of characters letters that is sorted in non-decreasing order, and a character target. There are at least two different characters in letters.
//
// Return the smallest character in letters that is lexicographically greater than target. If such a character does not exist, return the first character in letters.
//
// Example:
// Input: letters = ["c","f","j"], target = "a"
// Output: "c"
// Explanation: The smallest character that is lexicographically greater than 'a' in letters is 'c'.
//
// Constraints:
// 2 <= letters.length <= 104
// 	letters[i] is a lowercase English letter.
// 	letters is sorted in non-decreasing order.
// 	letters contains at least two different characters.
// 	target is a lowercase English letter.
//

/**
 * @param {character[]} letters
 * @param {character} target
 * @return {character}
 */
var nextGreatestLetter = function(letters, target) {
    for (let i = 0; i < letters.length; i++) {
        if (letters[i] > target) {
            return letters[i];
        }
    }
    return letters[0];
};
