// Source: https://leetcode.com/problems/maximum-number-of-non-overlapping-substrings/   |   Difficulty: Hard
//
// Problem Description:
// Given a string s of lowercase letters, you need to find the maximum number of non-empty substrings of s that meet the following conditions:
//
//
// 	The substrings do not overlap, that is for any two substrings s[i..j] and s[x..y], either j < x or i > y is true.
// 	A substring that contains a certain character c must also contain all occurrences of c.
//
//
// Find the maximum number of substrings that meet the above conditions. If there are multiple solutions with the same number of substrings, return the one with minimum total length. It can be shown that there exists a unique solution of minimum total length.
//
// Notice that you can return the substrings in any order.
//
// Example:
// Input: s = "adefaddaccc"
// Output: ["e","f","ccc"]
// Explanation: The following are all the possible substrings that meet the conditions:
// [
//   "adefaddaccc"
//   "adefadda",
//   "ef",
//   "e",
//   "f",
//   "ccc",
// ]
// If we choose the first string, we cannot choose anything else and we'd get only 1. If we choose "adefadda", we are left with "ccc" which is the only one that doesn't overlap, thus obtaining 2 substrings. Notice also, that it's not optimal to choose "ef" since it can be split into two. Therefore, the optimal way is to choose ["e","f","ccc"] which gives us 3 substrings. No other solution of the same number of substrings exist.
//
// Constraints:
// 1 <= s.length <= 105
// 	s contains only lowercase English letters.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** maxNumOfSubstrings(char* s, int* returnSize) {
    int n = strlen(s);
    int left[26], right[26];
    for (int i = 0; i < 26; ++i) {
        left[i] = n; right[i] = -1;
    }
    for (int i = 0; i < n; ++i) {
        int c = s[i] - 'a';
        if (i < left[c]) left[c] = i;
        if (i > right[c]) right[c] = i;
    }

    int intervals[26][2];
    int intervalCount = 0;
    for (int i = 0; i < 26; ++i) {
        if (right[i] == -1) continue;
        int l = left[i], r = right[i];
        for (int j = l; j <= r; ++j) {
            int cj = s[j] - 'a';
            if (left[cj] < l) { l = -1; break; }
            if (right[cj] > r) r = right[cj];
        }
        if (l != -1) {
            intervals[intervalCount][0] = l;
            intervals[intervalCount][1] = r;
            intervalCount++;
        }
    }

    qsort(intervals, intervalCount, sizeof(intervals[0]),
          [](const void *a, const void *b) {
              return ((int*)a)[1] - ((int*)b)[1];
          });

    char **results = (char**)malloc(intervalCount * sizeof(char*));
    int resSize = 0;
    int prevEnd = -1;
    for (int i = 0; i < intervalCount; ++i) {
        int l = intervals[i][0], r = intervals[i][1];
        if (l > prevEnd) {
            int len = r - l + 1;
            char *substr = (char*)malloc((len + 1) * sizeof(char));
            strncpy(substr, s + l, len);
            substr[len] = '\0';
            results[resSize++] = substr;
            prevEnd = r;
        }
    }

    *returnSize = resSize;
    return results;     
}
