// Source: https://leetcode.com/problems/maximum-number-of-occurrences-of-a-substring/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, return the maximum number of occurrences of any substring under the following rules:
//
//
// 	The number of unique characters in the substring must be less than or equal to maxLetters.
// 	The substring size must be between minSize and maxSize inclusive.
//
// Example:
// Input: s = "aababcaab", maxLetters = 2, minSize = 3, maxSize = 4
// Output: 2
// Explanation: Substring "aab" has 2 occurrences in the original string.
// It satisfies the conditions, 2 unique letters and size 3 (between minSize and maxSize).
//
// Constraints:
// 1 <= s.length <= 105
// 	1 <= maxLetters <= 26
// 	1 <= minSize <= maxSize <= min(26, s.length)
// 	s consists of only lowercase English letters.
//

class Solution {
public:
    int maxFreq(string s, int maxLetters, int minSize, int maxSize) {
        unordered_map<string, int> substringCount;
        int n = s.size();
        int maxOccurrence = 0;

        for (int i = 0; i <= n - minSize; ++i) {
            string substring = s.substr(i, minSize);
            unordered_set<char> uniqueChars(substring.begin(), substring.end());

            if (uniqueChars.size() <= maxLetters) {
                substringCount[substring]++;
                maxOccurrence = max(maxOccurrence, substringCount[substring]);
            }
        }

        return maxOccurrence;           
    }
};
