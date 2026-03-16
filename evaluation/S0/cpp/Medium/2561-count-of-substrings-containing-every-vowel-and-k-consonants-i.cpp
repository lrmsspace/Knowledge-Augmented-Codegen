// Source: https://leetcode.com/problems/count-of-substrings-containing-every-vowel-and-k-consonants-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string word and a non-negative integer k.
//
// Return the total number of substrings of word that contain every vowel ('a', 'e', 'i', 'o', and 'u') at least once and exactly k consonants.
//
// Example:
// Input: word = "aeioqq", k = 1
//
// Output: 0
//
// Explanation:
//
// There is no substring with every vowel.
//
// Constraints:
// 5 <= word.length <= 250
// 	word consists only of lowercase English letters.
// 	0 <= k <= word.length - 5
//

class Solution {
public:
    int countOfSubstrings(string word, int k) {
        int n = word.size();
        int result = 0;

        for (int i = 0; i < n; ++i) {
            unordered_set<char> vowels;
            int consonantCount = 0;

            for (int j = i; j < n; ++j) {
                char ch = word[j];
                if (isVowel(ch)) {
                    vowels.insert(ch);
                } else {
                    consonantCount++;
                }

                if (vowels.size() == 5 && consonantCount == k) {
                    result++;
                }
            }
        }

        return result;          
    }
};
