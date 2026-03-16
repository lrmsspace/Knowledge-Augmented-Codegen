// Source: https://leetcode.com/problems/reverse-words-in-a-string-iii/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s, reverse the order of characters in each word within a sentence while still preserving whitespace and initial word order.
//
// Example:
// Input: s = "Let's take LeetCode contest"
// Output: "s'teL ekat edoCteeL tsetnoc"
//
// Constraints:
// 1 <= s.length <= 5 * 104
// 	s contains printable ASCII characters.
// 	s does not contain any leading or trailing spaces.
// 	There is at least one word in s.
// 	All the words in s are separated by a single space.
//

class Solution {
    public String reverseWords(String s) {
        String[] words = s.split(" ");
        StringBuilder result = new StringBuilder();

        for (int i = 0; i < words.length; i++) {
            StringBuilder reversedWord = new StringBuilder(words[i]);
            reversedWord.reverse();
            result.append(reversedWord);

            if (i < words.length - 1) {
                result.append(" ");
            }
        }

        return result.toString();           
    }
}
