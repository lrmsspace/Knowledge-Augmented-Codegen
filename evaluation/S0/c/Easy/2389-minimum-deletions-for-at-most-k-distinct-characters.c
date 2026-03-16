// Source: https://leetcode.com/problems/minimum-deletions-for-at-most-k-distinct-characters/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string s consisting of lowercase English letters, and an integer k.
//
// Your task is to delete some (possibly none) of the characters in the string so that the number of distinct characters in the resulting string is at most k.
//
// Return the minimum number of deletions required to achieve this.
//
// Example:
// Input: s = "abc", k = 2
//
// Output: 1
//
// Explanation:
//
//
// 	s has three distinct characters: 'a', 'b' and 'c', each with a frequency of 1.
// 	Since we can have at most k = 2 distinct characters, remove all occurrences of any one character from the string.
// 	For example, removing all occurrences of 'c' results in at most k distinct characters. Thus, the answer is 1.
//
// Constraints:
// 1 <= s.length <= 16
// 	1 <= k <= 16
// 	s consists only of lowercase English letters.
//

int minDeletion(char* s, int k) {
    int freq[26] = {0};
    for (char* p = s; *p; ++p) {
        freq[*p - 'a']++;
    }

    int counts[16];
    int distinct_count = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            counts[distinct_count++] = freq[i];
        }
    }

    if (distinct_count <= k) {
        return 0;
    }

    // Sort counts in ascending order
    for (int i = 0; i < distinct_count - 1; ++i) {
        for (int j = i + 1; j < distinct_count; ++j) {
            if (counts[i] > counts[j]) {
                int temp = counts[i];
                counts[i] = counts[j];
                counts[j] = temp;
            }
        }
    }

    int deletions = 0;
    for (int i = 0; i < distinct_count - k; ++i) {
        deletions += counts[i];
    }

    return deletions;       
}
