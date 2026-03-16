// Source: https://leetcode.com/problems/circular-sentence/   |   Difficulty: Easy
//
// Problem Description:
// A sentence is a list of words that are separated by a single space with no leading or trailing spaces.
//
//
// 	For example, "Hello World", "HELLO", "hello world hello world" are all sentences.
//
//
// Words consist of only uppercase and lowercase English letters. Uppercase and lowercase English letters are considered different.
//
// A sentence is circular if:
//
//
// 	The last character of each word in the sentence is equal to the first character of its next word.
// 	The last character of the last word is equal to the first character of the first word.
//
//
// For example, "leetcode exercises sound delightful", "eetcode", "leetcode eats soul" are all circular sentences. However, "Leetcode is cool", "happy Leetcode", "Leetcode" and "I like Leetcode" are not circular sentences.
//
// Given a string sentence, return true if it is circular. Otherwise, return false.
//
// Example:
// Input: sentence = "leetcode exercises sound delightful"
// Output: true
// Explanation: The words in sentence are ["leetcode", "exercises", "sound", "delightful"].
// - leetcode's last character is equal to exercises's first character.
// - exercises's last character is equal to sound's first character.
// - sound's last character is equal to delightful's first character.
// - delightful's last character is equal to leetcode's first character.
// The sentence is circular.
//
// Constraints:
// 1 <= sentence.length <= 500
// 	sentence consist of only lowercase and uppercase English letters and spaces.
// 	The words in sentence are separated by a single space.
// 	There are no leading or trailing spaces.
//

class Solution {
    public boolean isCircularSentence(String sentence) {
        String[] words = sentence.split(" ");
        int n = words.length;

        for (int i = 0; i < n; i++) {
            String currentWord = words[i];
            String nextWord = words[(i + 1) % n];

            char lastCharCurrent = currentWord.charAt(currentWord.length() - 1);
            char firstCharNext = nextWord.charAt(0);

            if (lastCharCurrent != firstCharNext) {
                return false;
            }
        }

        return true;            
    }
}
