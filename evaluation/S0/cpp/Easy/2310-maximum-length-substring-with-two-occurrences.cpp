// Source: https://leetcode.com/problems/maximum-length-substring-with-two-occurrences/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s, return the maximum length of a substring such that it contains at most two occurrences of each character.
//
// Example:
// Input: s = "bcbbbcba"
//
// Output: 4
//
// Explanation:
// The following substring has a length of 4 and contains at most two occurrences of each character: "bcbbbcba".
//
// Constraints:
// 2 <= s.length <= 100
// 	s consists only of lowercase English letters.
//

class Solution {
public:
    int maximumLengthSubstring(string s) {
        int maxLength = 0;
        int n = s.length();

        for (int i = 0; i < n; ++i) {
            vector<int> charCount(26, 0);
            int currentLength = 0;

            for (int j = i; j < n; ++j) {
                charCount[s[j] - 'a']++;
                
                if (charCount[s[j] - 'a'] > 2) {
                    break;
                }
                
                currentLength++;
            }

            maxLength = max(maxLength, currentLength);
        }

        return maxLength;           
    }
};
