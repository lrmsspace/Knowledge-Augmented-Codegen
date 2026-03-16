// Source: https://leetcode.com/problems/count-vowel-substrings-of-a-string/   |   Difficulty: Easy
//
// Problem Description:
// A substring is a contiguous (non-empty) sequence of characters within a string.
//
// A vowel substring is a substring that only consists of vowels ('a', 'e', 'i', 'o', and 'u') and has all five vowels present in it.
//
// Given a string word, return the number of vowel substrings in word.
//
// Example:
// Input: word = "aeiouu"
// Output: 2
// Explanation: The vowel substrings of word are as follows (underlined):
// - "aeiouu"
// - "aeiouu"
//
// Constraints:
// 1 <= word.length <= 100
// 	word consists of lowercase English letters only.
//

class Solution {
public:
    int countVowelSubstrings(string word) {
        int n = word.size();
        int count = 0;
        for (int i = 0; i < n; ++i) {
            set<char> vowels;
            for (int j = i; j < n; ++j) {
                char c = word[j];
                if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
                    vowels.insert(c);
                    if (vowels.size() == 5) {
                        count++;
                    }
                } else {
                    break;
                }
            }
        }
        return count;           
    }
};
