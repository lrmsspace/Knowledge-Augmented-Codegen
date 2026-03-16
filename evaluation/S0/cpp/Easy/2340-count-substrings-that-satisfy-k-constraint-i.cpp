// Source: https://leetcode.com/problems/count-substrings-that-satisfy-k-constraint-i/   |   Difficulty: Easy
//
// Problem Description:
// You are given a binary string s and an integer k.
//
// A binary string satisfies the k-constraint if either of the following conditions holds:
//
//
// 	The number of 0's in the string is at most k.
// 	The number of 1's in the string is at most k.
//
//
// Return an integer denoting the number of substrings of s that satisfy the k-constraint.
//
// Example:
// Input: s = "10101", k = 1
//
// Output: 12
//
// Explanation:
//
// Every substring of s except the substrings "1010", "10101", and "0101" satisfies the k-constraint.
//
// Constraints:
// 1 <= s.length <= 50 
// 	1 <= k <= s.length
// 	s[i] is either '0' or '1'.
//

class Solution {
public:
    int countKConstraintSubstrings(string s, int k) {
        int n = s.size();
        int result = 0;

        for (int i = 0; i < n; ++i) {
            int count0 = 0;
            int count1 = 0;

            for (int j = i; j < n; ++j) {
                if (s[j] == '0') {
                    count0++;
                } else {
                    count1++;
                }

                if (count0 <= k || count1 <= k) {
                    result++;
                }
            }
        }

        return result;          
    }
};
