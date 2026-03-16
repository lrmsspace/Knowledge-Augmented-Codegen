// Source: https://leetcode.com/problems/find-and-replace-in-string/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed string s that you must perform k replacement operations on. The replacement operations are given as three 0-indexed parallel arrays, indices, sources, and targets, all of length k.
//
// To complete the ith replacement operation:
//
//
// 	Check if the substring sources[i] occurs at index indices[i] in the original string s.
// 	If it does not occur, do nothing.
// 	Otherwise if it does occur, replace that substring with targets[i].
//
//
// For example, if s = "abcd", indices[i] = 0, sources[i] = "ab", and targets[i] = "eee", then the result of this replacement will be "eeecd".
//
// All replacement operations must occur simultaneously, meaning the replacement operations should not affect the indexing of each other. The testcases will be generated such that the replacements will not overlap.
//
//
// 	For example, a testcase with s = "abc", indices = [0, 1], and sources = ["ab","bc"] will not be generated because the "ab" and "bc" replacements overlap.
//
//
// Return the resulting string after performing all replacement operations on s.
//
// A substring is a contiguous sequence of characters in a string.
//
// Example:
// Input: s = "abcd", indices = [0, 2], sources = ["a", "cd"], targets = ["eee", "ffff"]
// Output: "eeebffff"
// Explanation:
// "a" occurs at index 0 in s, so we replace it with "eee".
// "cd" occurs at index 2 in s, so we replace it with "ffff".
//
// Constraints:
// 1 <= s.length <= 1000
// 	k == indices.length == sources.length == targets.length
// 	1 <= k <= 100
// 	0 <= indexes[i] < s.length
// 	1 <= sources[i].length, targets[i].length <= 50
// 	s consists of only lowercase English letters.
// 	sources[i] and targets[i] consist of only lowercase English letters.
//

char* findReplaceString(char* s, int* indices, int indicesSize, char** sources, int sourcesSize, char** targets, int targetsSize) {
    int n = strlen(s);
    char* result = (char*)malloc(3000 * sizeof(char));
    int resultIndex = 0;
    int i = 0, j = 0;

    while (i < n) {
        if (j < indicesSize && i == indices[j]) {
            int sourceLen = strlen(sources[j]);
            if (strncmp(&s[i], sources[j], sourceLen) == 0) {
                int targetLen = strlen(targets[j]);
                strncpy(&result[resultIndex], targets[j], targetLen);
                resultIndex += targetLen;
                i += sourceLen;
            } else {
                result[resultIndex++] = s[i++];
            }
            j++;
        } else {
            result[resultIndex++] = s[i++];
        }
    }

    result[resultIndex] = '\0';
    return result;      
}
