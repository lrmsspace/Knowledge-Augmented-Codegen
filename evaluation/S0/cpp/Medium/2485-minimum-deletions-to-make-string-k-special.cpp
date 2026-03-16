// Source: https://leetcode.com/problems/minimum-deletions-to-make-string-k-special/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string word and an integer k.
//
// We consider word to be k-special if |freq(word[i]) - freq(word[j])| <= k for all indices i and j in the string.
//
// Here, freq(x) denotes the frequency of the character x in word, and |y| denotes the absolute value of y.
//
// Return the minimum number of characters you need to delete to make word k-special.
//
// Example:
// Input: word = "aabcaba", k = 0
//
// Output: 3
//
// Explanation: We can make word 0-special by deleting 2 occurrences of "a" and 1 occurrence of "c". Therefore, word becomes equal to "baba" where freq('a') == freq('b') == 2.
//
// Constraints:
// 1 <= word.length <= 105
// 	0 <= k <= 105
// 	word consists only of lowercase English letters.
//

class Solution {
public:
    int minimumDeletions(string word, int k) {
        vector<int> freq(26, 0);
        for (char c : word) {
            freq[c - 'a']++;
        }

        sort(freq.begin(), freq.end(), greater<int>());

        int n = freq.size();
        int minDeletions = INT_MAX;

        for (int targetFreq = 0; targetFreq <= freq[0]; ++targetFreq) {
            int deletions = 0;
            for (int i = 0; i < n; ++i) {
                if (freq[i] > targetFreq + k) {
                    deletions += freq[i] - (targetFreq + k);
                } else if (freq[i] < targetFreq) {
                    deletions += freq[i];
                }
            }
            minDeletions = min(minDeletions, deletions);
        }

        return minDeletions;            
    }
};
