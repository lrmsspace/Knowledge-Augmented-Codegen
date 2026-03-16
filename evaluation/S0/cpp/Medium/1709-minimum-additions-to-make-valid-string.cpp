// Source: https://leetcode.com/problems/minimum-additions-to-make-valid-string/   |   Difficulty: Medium
//
// Problem Description:
// Given a string word to which you can insert letters "a", "b" or "c" anywhere and any number of times, return the minimum number of letters that must be inserted so that word becomes valid.
//
// A string is called valid if it can be formed by concatenating the string "abc" several times.
//
// Example:
// Input: word = "b"
// Output: 2
// Explanation: Insert the letter "a" right before "b", and the letter "c" right next to "b" to obtain the valid string "abc".
//
// Constraints:
// 1 <= word.length <= 50
// 	word consists of letters "a", "b" and "c" only.
//

class Solution {
public:
    int addMinimum(string word) {
        int insertions = 0;
        int expectedCharIndex = 0; // 0 for 'a', 1 for 'b', 2 for 'c'

        for (char ch : word) {
            int currentCharIndex = ch - 'a';

            // Calculate how many characters are missing to reach the current character
            while (expectedCharIndex != currentCharIndex) {
                insertions++;
                expectedCharIndex = (expectedCharIndex + 1) % 3;
            }

            // Move to the next expected character
            expectedCharIndex = (expectedCharIndex + 1) % 3;
        }

        // After processing all characters, if we are not at the start of a new "abc" sequence,
        // we need to add the remaining characters to complete the last sequence.
        if (expectedCharIndex != 0) {
            insertions += (3 - expectedCharIndex);
        }

        return insertions;          
    }
};
