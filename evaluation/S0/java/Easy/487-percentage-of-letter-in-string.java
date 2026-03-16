// Source: https://leetcode.com/problems/percentage-of-letter-in-string/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s and a character letter, return the percentage of characters in s that equal letter rounded down to the nearest whole percent.
//
// Example:
// Input: s = "foobar", letter = "o"
// Output: 33
// Explanation:
// The percentage of characters in s that equal the letter 'o' is 2 / 6 * 100% = 33% when rounded down, so we return 33.
//
// Constraints:
// 1 <= s.length <= 100
// 	s consists of lowercase English letters.
// 	letter is a lowercase English letter.
//

class Solution {
    public int percentageLetter(String s, char letter) {
        int count = 0;
        for (char c : s.toCharArray()) {
            if (c == letter) {
                count++;
            }
        }
        return (count * 100) / s.length();          
    }
}
