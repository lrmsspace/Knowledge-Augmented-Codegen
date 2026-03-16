// Source: https://leetcode.com/problems/minimum-substring-partition-of-equal-character-frequency/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, you need to partition it into one or more balanced substrings. For example, if s == "ababcc" then ("abab", "c", "c"), ("ab", "abc", "c"), and ("ababcc") are all valid partitions, but ("a", "bab", "cc"), ("aba", "bc", "c"), and ("ab", "abcc") are not. The unbalanced substrings are bolded.
//
// Return the minimum number of substrings that you can partition s into.
//
// Note: A balanced string is a string where each character in the string occurs the same number of times.
//
// Example:
// Input: s = "fabccddg"
//
// Output: 3
//
// Explanation:
//
// We can partition the string s into 3 substrings in one of the following ways: ("fab, "ccdd", "g"), or ("fabc", "cd", "dg").
//
// Constraints:
// 1 <= s.length <= 1000
// 	s consists only of English lowercase letters.
//

class Solution {
public:
    int minimumSubstringsInPartition(string s) {
        int n = s.size();
        int result = 0;
        int i = 0;

        while (i < n) {
            unordered_map<char, int> charCount;
            int maxFreq = 0;
            int j = i;

            while (j < n) {
                charCount[s[j]]++;
                maxFreq = max(maxFreq, charCount[s[j]]);

                bool isBalanced = true;
                for (const auto& entry : charCount) {
                    if (entry.second != maxFreq) {
                        isBalanced = false;
                        break;
                    }
                }

                if (isBalanced) {
                    j++;
                    break;
                }
                j++;
            }

            result++;
            i = j;
        }

        return result;          
    }
};
