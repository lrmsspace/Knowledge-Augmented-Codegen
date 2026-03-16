// Source: https://leetcode.com/problems/sum-of-beauty-of-all-substrings/   |   Difficulty: Medium
//
// Problem Description:
// The beauty of a string is the difference in frequencies between the most frequent and least frequent characters.
//
//
// 	For example, the beauty of "abaacc" is 3 - 1 = 2.
//
//
// Given a string s, return the sum of beauty of all of its substrings.
//
// Example:
// Input: s = "aabcb"
// Output: 5
// Explanation: The substrings with non-zero beauty are ["aab","aabc","aabcb","abcb","bcb"], each with beauty equal to 1.
//
// Constraints:
// 1 <= s.length <= 500
// 	s consists of only lowercase English letters.
//

class Solution {
public:
    int beautySum(string s) {
        int n = s.size();
        int totalBeauty = 0;

        for (int i = 0; i < n; ++i) {
            vector<int> freq(26, 0);
            for (int j = i; j < n; ++j) {
                freq[s[j] - 'a']++;
                
                int maxFreq = 0;
                int minFreq = n + 1; // Initialize to a large number
                
                for (int k = 0; k < 26; ++k) {
                    if (freq[k] > 0) {
                        maxFreq = max(maxFreq, freq[k]);
                        minFreq = min(minFreq, freq[k]);
                    }
                }
                
                totalBeauty += (maxFreq - minFreq);
            }
        }

        return totalBeauty;         
    }
};
