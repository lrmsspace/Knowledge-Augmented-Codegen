// Source: https://leetcode.com/problems/check-if-a-string-can-break-another-string/   |   Difficulty: Medium
//
// Problem Description:
// Given two strings: s1 and s2 with the same size, check if some permutation of string s1 can break some permutation of string s2 or vice-versa. In other words s2 can break s1 or vice-versa.
//
// A string x can break string y (both of size n) if x[i] >= y[i] (in alphabetical order) for all i between 0 and n-1.
//
// Example:
// Input: s1 = "abc", s2 = "xya"
// Output: true
// Explanation: "ayx" is a permutation of s2="xya" which can break to string "abc" which is a permutation of s1="abc".
//
// Constraints:
// s1.length == n
// 	s2.length == n
// 	1 <= n <= 10^5
// 	All strings consist of lowercase English letters.
//

bool checkIfCanBreak(char* s1, char* s2) {
    int count1[26] = {0}, count2[26] = {0};
    for (int i = 0; s1[i]; i++) {
        count1[s1[i] - 'a']++;
        count2[s2[i] - 'a']++;
    }

    int diff1 = 0, diff2 = 0;
    for (int i = 0; i < 26; i++) {
        diff1 += count1[i] - count2[i];
        diff2 += count2[i] - count1[i];
        if (diff1 < 0 && diff2 < 0) {
            return false;
        }
    }
    return true;        
}
