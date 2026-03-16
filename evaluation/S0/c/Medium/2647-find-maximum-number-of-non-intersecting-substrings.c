// Source: https://leetcode.com/problems/find-maximum-number-of-non-intersecting-substrings/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string word.
//
// Return the maximum number of non-intersecting substrings of word that are at least four characters long and start and end with the same letter.
//
// Example:
// Input: word = "abcdeafdef"
//
// Output: 2
//
// Explanation:
//
// The two substrings are "abcdea" and "fdef".
//
// Constraints:
// 1 <= word.length <= 2 * 105
// 	word consists only of lowercase English letters.
//

int maxSubstrings(char* word) {
    int n = strlen(word);
    int left[26], right[26];
    for (int i = 0; i < 26; ++i) {
        left[i] = n;
        right[i] = -1;
    }
    for (int i = 0; i < n; ++i) {
        int idx = word[i] - 'a';
        if (i < left[idx]) left[idx] = i;
        if (i > right[idx]) right[idx] = i;
    }

    int intervals[26][2];
    int intervalCount = 0;
    for (int i = 0; i < 26; ++i) {
        if (right[i] - left[i] + 1 >= 4) {
            int start = left[i];
            int end = right[i];
            for (int j = start; j <= end; ++j) {
                int idx = word[j] - 'a';
                if (left[idx] < start) {
                    start = left[idx];
                    j = start - 1;
                }
                if (right[idx] > end) {
                    end = right[idx];
                }
            }
            if (end - start + 1 >= 4) {
                intervals[intervalCount][0] = start;
                intervals[intervalCount][1] = end;
                intervalCount++;
            }
        }
    }

    qsort(intervals, intervalCount, sizeof(intervals[0]), [](const void* a, const void* b) {
        return ((int*)a)[1] - ((int*)b)[1];
    });

    int count = 0;
    int lastEnd = -1;
    for (int i = 0; i < intervalCount; ++i) {
        if (intervals[i][0] > lastEnd) {
            count++;
            lastEnd = intervals[i][1];
        }
    }

    return count;       
}
