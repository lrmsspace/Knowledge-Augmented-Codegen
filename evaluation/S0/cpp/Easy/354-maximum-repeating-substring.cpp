// Source: https://leetcode.com/problems/maximum-repeating-substring/   |   Difficulty: Easy
//
// Problem Description:
// For a string sequence, a string word is k-repeating if word concatenated k times is a substring of sequence. The word's maximum k-repeating value is the highest value k where word is k-repeating in sequence. If word is not a substring of sequence, word's maximum k-repeating value is 0.
//
// Given strings sequence and word, return the maximum k-repeating value of word in sequence.
//
// Example:
// Input: sequence = "ababc", word = "ab"
// Output: 2
// Explanation: "abab" is a substring in "ababc".
//
// Constraints:
// 1 <= sequence.length <= 100
// 	1 <= word.length <= 100
// 	sequence and word contains only lowercase English letters.
//

class Solution {
public:
    int maxRepeating(string sequence, string word) {
        int maxCount = 0;
        string repeatedWord = word;

        while (sequence.find(repeatedWord) != string::npos) {
            maxCount++;
            repeatedWord += word;
        }

        return maxCount;            
    }
};
