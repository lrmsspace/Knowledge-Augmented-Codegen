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

int findLUSlength(char** strs, int strsSize) {
    int maxLen = -1;

    for (int i = 0; i < strsSize; i++) {
        int isUncommon = 1;
        for (int j = 0; j < strsSize; j++) {
            if (i != j) {
                // Check if strs[i] is a subsequence of strs[j]
                int m = strlen(strs[i]);
                int n = strlen(strs[j]);
                int p1 = 0, p2 = 0;

                while (p1 < m && p2 < n) {
                    if (strs[i][p1] == strs[j][p2]) {
                        p1++;
                    }
                    p2++;
                }

                if (p1 == m) { // strs[i] is a subsequence of strs[j]
                    isUncommon = 0;
                    break;
                }
            }
        }

        if (isUncommon) {
            int len = strlen(strs[i]);
            if (len > maxLen) {
                maxLen = len;
            }
        }
    }

    return maxLen;      
}
