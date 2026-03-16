// Source: https://leetcode.com/problems/longest-common-prefix/   |   Difficulty: Easy
//
// Problem Description:
// Write a function to find the longest common prefix string amongst an array of strings.
//
// If there is no common prefix, return an empty string "".
//
// Example:
// Input: strs = ["flower","flow","flight"]
// Output: "fl"
//
// Constraints:
// 1 <= strs.length <= 200
// 	0 <= strs[i].length <= 200
// 	strs[i] consists of only lowercase English letters if it is non-empty.
//

char* longestCommonPrefix(char** strs, int strsSize) {
    if (strsSize == 0) return "";

    for (int prefixLen = 0; prefixLen < 200; prefixLen++) {
        char currentChar = strs[0][prefixLen];
        if (currentChar == '\0') {
            strs[0][prefixLen] = '\0';
            return strs[0];
        }

        for (int i = 1; i < strsSize; i++) {
            if (strs[i][prefixLen] != currentChar) {
                strs[0][prefixLen] = '\0';
                return strs[0];
            }
        }
    }

    return strs[0];     
}
