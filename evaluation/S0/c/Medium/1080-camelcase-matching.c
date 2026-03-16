// Source: https://leetcode.com/problems/camelcase-matching/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of strings queries and a string pattern, return a boolean array answer where answer[i] is true if queries[i] matches pattern, and false otherwise.
//
// A query word queries[i] matches pattern if you can insert lowercase English letters into the pattern so that it equals the query. You may insert a character at any position in pattern or you may choose not to insert any characters at all.
//
// Example:
// Input: queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern = "FB"
// Output: [true,false,true,true,false]
// Explanation: "FooBar" can be generated like this "F" + "oo" + "B" + "ar".
// "FootBall" can be generated like this "F" + "oot" + "B" + "all".
// "FrameBuffer" can be generated like this "F" + "rame" + "B" + "uffer".
//
// Constraints:
// 1 <= pattern.length, queries.length <= 100
// 	1 <= queries[i].length <= 100
// 	queries[i] and pattern consist of English letters.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
bool* camelMatch(char** queries, int queriesSize, char* pattern, int* returnSize) {
    bool* result = (bool*)malloc(sizeof(bool) * queriesSize);
    *returnSize = queriesSize;

    for (int i = 0; i < queriesSize; i++) {
        char* query = queries[i];
        int pLen = strlen(pattern);
        int qLen = strlen(query);
        int pIndex = 0;
        int qIndex = 0;
        bool isMatch = true;

        while (qIndex < qLen) {
            if (pIndex < pLen && query[qIndex] == pattern[pIndex]) {
                pIndex++;
                qIndex++;
            } else if (isupper(query[qIndex])) {
                isMatch = false;
                break;
            } else {
                qIndex++;
            }
        }

        if (pIndex < pLen) {
            isMatch = false;
        }

        result[i] = isMatch;
    }

    return result;      
}
