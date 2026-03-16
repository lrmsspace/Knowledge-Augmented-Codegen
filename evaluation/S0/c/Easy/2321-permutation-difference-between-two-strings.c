// Source: https://leetcode.com/problems/permutation-difference-between-two-strings/   |   Difficulty: Easy
//
// Problem Description:
// You are given two strings s and t such that every character occurs at most once in s and t is a permutation of s.
//
// The permutation difference between s and t is defined as the sum of the absolute difference between the index of the occurrence of each character in s and the index of the occurrence of the same character in t.
//
// Return the permutation difference between s and t.
//
// Example:
// Input: s = "abc", t = "bac"
//
// Output: 2
//
// Explanation:
//
// For s = "abc" and t = "bac", the permutation difference of s and t is equal to the sum of:
//
//
// 	The absolute difference between the index of the occurrence of "a" in s and the index of the occurrence of "a" in t.
// 	The absolute difference between the index of the occurrence of "b" in s and the index of the occurrence of "b" in t.
// 	The absolute difference between the index of the occurrence of "c" in s and the index of the occurrence of "c" in t.
//
//
// That is, the permutation difference between s and t is equal to |0 - 1| + |1 - 0| + |2 - 2| = 2.
//
// Constraints:
// 1 <= s.length <= 26
// 	Each character occurs at most once in s.
// 	t is a permutation of s.
// 	s consists only of lowercase English letters.
//

int findPermutationDifference(char* s, char* t) {
    int index_s[26] = {0};
    int index_t[26] = {0};
    int i = 0;
    int result = 0;

    while (s[i] != '\0') {
        index_s[s[i] - 'a'] = i;
        index_t[t[i] - 'a'] = i;
        i++;
    }

    for (i = 0; i < 26; i++) {
        if (index_s[i] != 0 || s[0] - 'a' == i) {
            result += abs(index_s[i] - index_t[i]);
        }
    }

    return result;      
}
