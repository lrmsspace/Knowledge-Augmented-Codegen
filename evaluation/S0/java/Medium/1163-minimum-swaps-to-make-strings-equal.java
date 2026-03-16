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
    public int minimumSwap(String s1, String s2) {
        int xy = 0; // Count of positions where s1 has 'x' and s2 has 'y'
        int yx = 0; // Count of positions where s1 has 'y' and s2 has 'x'

        // Count the mismatches
        for (int i = 0; i < s1.length(); i++) {
            char c1 = s1.charAt(i);
            char c2 = s2.charAt(i);
            if (c1 == 'x' && c2 == 'y') {
                xy++;
            } else if (c1 == 'y' && c2 == 'x') {
                yx++;
            }
        }

        // If the total number of mismatches is odd, it's impossible to make the strings equal
        if ((xy + yx) % 2 != 0) {
            return -1;
        }

        // Calculate the minimum swaps needed
        int swaps = (xy / 2) + (yx / 2); // Each pair of mismatches can be resolved with one swap
        if (xy % 2 == 1) { // If there's an odd mismatch left in both counts
            swaps += 2; // It takes two swaps to resolve one 'xy' and one 'yx'
        }

        return swaps;           
    }
}
