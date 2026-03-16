// Source: https://leetcode.com/problems/partition-labels/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s. We want to partition the string into as many parts as possible so that each letter appears in at most one part. For example, the string "ababcc" can be partitioned into ["abab", "cc"], but partitions such as ["aba", "bcc"] or ["ab", "ab", "cc"] are invalid.
//
// Note that the partition is done so that after concatenating all the parts in order, the resultant string should be s.
//
// Return a list of integers representing the size of these parts.
//
// Example:
// Input: s = "ababcbacadefegdehijhklij"
// Output: [9,7,8]
// Explanation:
// The partition is "ababcbaca", "defegde", "hijhklij".
// This is a partition so that each letter appears in at most one part.
// A partition like "ababcbacadefegde", "hijhklij" is incorrect, because it splits s into less parts.
//
// Constraints:
// 1 <= s.length <= 500
// 	s consists of lowercase English letters.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* partitionLabels(char* s, int* returnSize) {
    int lastIndex[26] = {0};
    int length = 0;
    while (s[length] != '\0') {
        lastIndex[s[length] - 'a'] = length;
        length++;
    }

    int* result = (int*)malloc(length * sizeof(int));
    int count = 0;
    int start = 0;
    int end = 0;

    for (int i = 0; i < length; i++) {
        end = (lastIndex[s[i] - 'a'] > end) ? lastIndex[s[i] - 'a'] : end;
        if (i == end) {
            result[count++] = end - start + 1;
            start = end + 1;
        }
    }

    *returnSize = count;
    return result;      
}
