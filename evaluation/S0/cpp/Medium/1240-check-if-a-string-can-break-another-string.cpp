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

class Solution {
public:
    bool checkIfCanBreak(string s1, string s2) {
        sort(s1.begin(), s1.end());
        sort(s2.begin(), s2.end());

        bool s1BreaksS2 = true;
        bool s2BreaksS1 = true;

        for (int i = 0; i < s1.size(); ++i) {
            if (s1[i] < s2[i]) {
                s1BreaksS2 = false;
            }
            if (s2[i] < s1[i]) {
                s2BreaksS1 = false;
            }
        }

        return s1BreaksS2 || s2BreaksS1;            
    }
};
