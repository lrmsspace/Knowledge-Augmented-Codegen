// Source: https://leetcode.com/problems/length-of-last-word/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s consisting of words and spaces, return the length of the last word in the string.
//
// A word is a maximal substring consisting of non-space characters only.
//
// Example:
// Input: s = "Hello World"
// Output: 5
// Explanation: The last word is "World" with length 5.
//
// Constraints:
// 1 <= s.length <= 104
// 	s consists of only English letters and spaces ' '.
// 	There will be at least one word in s.
//

class Solution {
    public int lengthOfLastWord(String s) {
        String[] words = s.trim().split(" ");
        return words[words.length - 1].length();            
    }
}
