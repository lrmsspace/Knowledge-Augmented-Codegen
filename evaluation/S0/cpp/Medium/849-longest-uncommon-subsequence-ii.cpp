// Source: https://leetcode.com/problems/longest-uncommon-subsequence-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of strings strs, return the length of the longest uncommon subsequence between them. If the longest uncommon subsequence does not exist, return -1.
//
// An uncommon subsequence between an array of strings is a string that is a subsequence of one string but not the others.
//
// A subsequence of a string s is a string that can be obtained after deleting any number of characters from s.
//
//
// 	For example, "abc" is a subsequence of "aebdc" because you can delete the underlined characters in "aebdc" to get "abc". Other subsequences of "aebdc" include "aebdc", "aeb", and "" (empty string).
//
// Example:
// Input: strs = ["aba","cdc","eae"]
// Output: 3
//
// Constraints:
// 2 <= strs.length <= 50
// 	1 <= strs[i].length <= 10
// 	strs[i] consists of lowercase English letters.
//

class Solution {
public:
    int findLUSlength(vector<string>& strs) {
        auto isSubsequence = [](const string& a, const string& b) {
            int i = 0, j = 0;
            while (i < a.size() && j < b.size()) {
                if (a[i] == b[j]) {
                    i++;
                }
                j++;
            }
            return i == a.size();
        };

        int maxLength = -1;
        for (int i = 0; i < strs.size(); ++i) {
            bool isUncommon = true;
            for (int j = 0; j < strs.size(); ++j) {
                if (i != j && isSubsequence(strs[i], strs[j])) {
                    isUncommon = false;
                    break;
                }
            }
            if (isUncommon) {
                maxLength = max(maxLength, static_cast<int>(strs[i].size()));
            }
        }
        return maxLength;           
    }
};
