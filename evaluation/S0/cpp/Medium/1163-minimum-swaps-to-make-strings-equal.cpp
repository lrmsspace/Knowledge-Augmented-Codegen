// Source: https://leetcode.com/problems/minimum-swaps-to-make-strings-equal/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings s1 and s2 of equal length consisting of letters "x" and "y" only. Your task is to make these two strings equal to each other. You can swap any two characters that belong to different strings, which means: swap s1[i] and s2[j].
//
// Return the minimum number of swaps required to make s1 and s2 equal, or return -1 if it is impossible to do so.
//
// Example:
// Input: s1 = "xx", s2 = "yy"
// Output: 1
// Explanation: Swap s1[0] and s2[1], s1 = "yx", s2 = "yx".
//
// Constraints:
// 1 <= s1.length, s2.length <= 1000
// 	s1.length == s2.length
// 	s1, s2 only contain 'x' or 'y'.
//

class Solution {
public:
    int minimumSwap(string s1, string s2) {
        int xy = 0, yx = 0;
        for (size_t i = 0; i < s1.size(); ++i) {
            if (s1[i] == 'x' && s2[i] == 'y') {
                ++xy;
            } else if (s1[i] == 'y' && s2[i] == 'x') {
                ++yx;
            }
        }

        int total = xy + yx;
        if (total % 2 != 0) {
            return -1;
        }

        int swaps = (xy / 2) + (yx / 2);
        if (xy % 2 == 1) {
            swaps += 2; // one 'xy' and one 'yx' left
        }

        return swaps;           
    }
};
