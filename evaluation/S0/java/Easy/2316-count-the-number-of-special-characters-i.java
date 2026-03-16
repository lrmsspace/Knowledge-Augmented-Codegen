// Source: https://leetcode.com/problems/count-the-number-of-special-characters-i/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string word. A letter is called special if it appears both in lowercase and uppercase in word.
//
// Return the number of special letters in word.
//
// Example:
// Input: word = "aaAbcBC"
//
// Output: 3
//
// Explanation:
//
// The special characters in word are 'a', 'b', and 'c'.
//
// Constraints:
// 1 <= word.length <= 50
// 	word consists of only lowercase and uppercase English letters.
//

class Solution {
    public int numberOfSpecialChars(String word) {
        int count = 0;
        for (char ch = 'a'; ch <= 'z'; ch++) {
            if (word.indexOf(ch) != -1 && word.indexOf(Character.toUpperCase(ch)) != -1) {
                count++;
            }
        }
        return count;           
    }
}
