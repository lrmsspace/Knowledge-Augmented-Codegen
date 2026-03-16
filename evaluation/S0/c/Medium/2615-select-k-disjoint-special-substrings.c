// Source: https://leetcode.com/problems/select-k-disjoint-special-substrings/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s of length n and an integer k, determine whether it is possible to select k disjoint special substrings.
//
// A special substring is a substring where:
//
//
// 	Any character present inside the substring should not appear outside it in the string.
// 	The substring is not the entire string s.
//
//
// Note that all k substrings must be disjoint, meaning they cannot overlap.
//
// Return true if it is possible to select k such disjoint special substrings; otherwise, return false.
//
// Example:
// Input: s = "abcdbaefab", k = 2
//
// Output: true
//
// Explanation:
//
//
// 	We can select two disjoint special substrings: "cd" and "ef".
// 	"cd" contains the characters 'c' and 'd', which do not appear elsewhere in s.
// 	"ef" contains the characters 'e' and 'f', which do not appear elsewhere in s.
//
// Constraints:
// 2 <= n == s.length <= 5 * 104
// 	0 <= k <= 26
// 	s consists only of lowercase English letters.
//

bool maxSubstringLength(char* s, int k) {
    int n = strlen(s);
    int first[26], last[26];
    for (int i = 0; i < 26; i++) {
        first[i] = -1;
        last[i] = -1;
    }
    for (int i = 0; i < n; i++) {
        int idx = s[i] - 'a';
        if (first[idx] == -1) {
            first[idx] = i;
        }
        last[idx] = i;
    }
    int count = 0;
    int end = -1;
    for (int i = 0; i < 26; i++) {
        if (first[i] == -1) {
            continue;
        }
        if (first[i] > end) {
            count++;
            end = last[i];
        } else {
            end = fmax(end, last[i]);
        }
    }
    return count >= k;      
}
