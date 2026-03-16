// Source: https://leetcode.com/problems/maximum-number-of-vowels-in-a-substring-of-given-length/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s and an integer k, return the maximum number of vowel letters in any substring of s with length k.
//
// Vowel letters in English are 'a', 'e', 'i', 'o', and 'u'.
//
// Example:
// Input: s = "abciiidef", k = 3
// Output: 3
// Explanation: The substring "iii" contains 3 vowel letters.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of lowercase English letters.
// 	1 <= k <= s.length
//

class Solution {
public:
    int maxVowels(string s, int k) {
        unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u'};
        int maxCount = 0, currentCount = 0;

        // Count vowels in the first window
        for (int i = 0; i < k; ++i) {
            if (vowels.count(s[i])) {
                currentCount++;
            }
        }
        maxCount = currentCount;

        // Slide the window
        for (int i = k; i < s.length(); ++i) {
            if (vowels.count(s[i])) {
                currentCount++;
            }
            if (vowels.count(s[i - k])) {
                currentCount--;
            }
            maxCount = max(maxCount, currentCount);
        }

        return maxCount;            
    }
};
