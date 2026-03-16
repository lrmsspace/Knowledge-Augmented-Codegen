// Source: https://leetcode.com/problems/count-substrings-that-can-be-rearranged-to-contain-a-string-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings word1 and word2.
//
// A string x is called valid if x can be rearranged to have word2 as a prefix.
//
// Return the total number of valid substrings of word1.
//
// Example:
// Input: word1 = "bcca", word2 = "abc"
//
// Output: 1
//
// Explanation:
//
// The only valid substring is "bcca" which can be rearranged to "abcc" having "abc" as a prefix.
//
// Constraints:
// 1 <= word1.length <= 105
// 	1 <= word2.length <= 104
// 	word1 and word2 consist only of lowercase English letters.
//

class Solution {
public:
    long long validSubstringCount(string word1, string word2) {
        vector<int> targetCount(26, 0);
        for (char c : word2) {
            targetCount[c - 'a']++;
        }

        int requiredLength = word2.length();
        vector<int> windowCount(26, 0);
        long long validCount = 0;

        for (int i = 0; i < word1.length(); ++i) {
            windowCount[word1[i] - 'a']++;

            if (i >= requiredLength) {
                windowCount[word1[i - requiredLength] - 'a']--;
            }

            if (i >= requiredLength - 1) {
                bool isValid = true;
                for (int j = 0; j < 26; ++j) {
                    if (windowCount[j] < targetCount[j]) {
                        isValid = false;
                        break;
                    }
                }
                if (isValid) {
                    validCount++;
                }
            }
        }

        return validCount;          
    }
};
