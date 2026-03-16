// Source: https://leetcode.com/problems/removing-stars-from-a-string/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s, which contains stars *.
//
// In one operation, you can:
//
//
// 	Choose a star in s.
// 	Remove the closest non-star character to its left, as well as remove the star itself.
//
//
// Return the string after all stars have been removed.
//
// Note:
//
//
// 	The input will be generated such that the operation is always possible.
// 	It can be shown that the resulting string will always be unique.
//
// Example:
// Input: s = "leet**cod*e"
// Output: "lecoe"
// Explanation: Performing the removals from left to right:
// - The closest character to the 1st star is 't' in "leet**cod*e". s becomes "lee*cod*e".
// - The closest character to the 2nd star is 'e' in "lee*cod*e". s becomes "lecod*e".
// - The closest character to the 3rd star is 'd' in "lecod*e". s becomes "lecoe".
// There are no more stars, so we return "lecoe".
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of lowercase English letters and stars *.
// 	The operation above can be performed on s.
//

class Solution {
    public String removeStars(String s) {
        StringBuilder result = new StringBuilder();
        int starsCount = 0;

        // Traverse the string in reverse
        for (int i = s.length() - 1; i >= 0; i--) {
            char currentChar = s.charAt(i);

            if (currentChar == '*') {
                starsCount++;
            } else {
                if (starsCount > 0) {
                    starsCount--; // Remove the closest non-star character
                } else {
                    result.append(currentChar); // Keep the character
                }
            }
        }

        // Reverse the result to get the final string
        return result.reverse().toString();         
    }
}
