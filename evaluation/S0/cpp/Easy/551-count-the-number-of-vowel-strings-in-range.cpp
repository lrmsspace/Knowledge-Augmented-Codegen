// Source: https://leetcode.com/problems/count-the-number-of-vowel-strings-in-range/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed array of string words and two integers left and right.
//
// A string is called a vowel string if it starts with a vowel character and ends with a vowel character where vowel characters are 'a', 'e', 'i', 'o', and 'u'.
//
// Return the number of vowel strings words[i] where i belongs to the inclusive range [left, right].
//
// Example:
// Input: words = ["are","amy","u"], left = 0, right = 2
// Output: 2
// Explanation: 
// - "are" is a vowel string because it starts with 'a' and ends with 'e'.
// - "amy" is not a vowel string because it does not end with a vowel.
// - "u" is a vowel string because it starts with 'u' and ends with 'u'.
// The number of vowel strings in the mentioned range is 2.
//
// Constraints:
// 1 <= words.length <= 1000
// 	1 <= words[i].length <= 10
// 	words[i] consists of only lowercase English letters.
// 	0 <= left <= right < words.length
//

class Solution {
public:
    int vowelStrings(vector<string>& words, int left, int right) {
        auto isVowel = [](char c) {
            return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
        };

        int count = 0;
        for (int i = left; i <= right; ++i) {
            if (isVowel(words[i].front()) && isVowel(words[i].back())) {
                ++count;
            }
        }
        return count;           
    }
};
