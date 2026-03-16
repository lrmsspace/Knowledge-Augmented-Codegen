// Source: https://leetcode.com/problems/reverse-prefix-of-word/   |   Difficulty: Easy
//
// Problem Description:
// Given a 0-indexed string word and a character ch, reverse the segment of word that starts at index 0 and ends at the index of the first occurrence of ch (inclusive). If the character ch does not exist in word, do nothing.
//
//
// 	For example, if word = "abcdefd" and ch = "d", then you should reverse the segment that starts at 0 and ends at 3 (inclusive). The resulting string will be "dcbaefd".
//
//
// Return the resulting string.
//
// Example:
// Input: word = "abcdefd", ch = "d"
// Output: "dcbaefd"
// Explanation: The first occurrence of "d" is at index 3. 
// Reverse the part of word from 0 to 3 (inclusive), the resulting string is "dcbaefd".
//
// Constraints:
// 1 <= word.length <= 250
// 	word consists of lowercase English letters.
// 	ch is a lowercase English letter.
//

class Solution {
    public String reversePrefix(String word, char ch) {
        int index = word.indexOf(ch);
        if (index == -1) {
            return word;
        }
        StringBuilder sb = new StringBuilder();
        for (int i = index; i >= 0; i--) {
            sb.append(word.charAt(i));
        }
        sb.append(word.substring(index + 1));
        return sb.toString();           
    }
}
