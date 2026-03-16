// Source: https://leetcode.com/problems/minimum-number-of-flips-to-make-the-binary-string-alternating/   |   Difficulty: Medium
//
// Problem Description:
// You are given a binary string s. You are allowed to perform two types of operations on the string in any sequence:
//
//
// 	Type-1: Remove the character at the start of the string s and append it to the end of the string.
// 	Type-2: Pick any character in s and flip its value, i.e., if its value is '0' it becomes '1' and vice-versa.
//
//
// Return the minimum number of type-2 operations you need to perform such that s becomes alternating.
//
// The string is called alternating if no two adjacent characters are equal.
//
//
// 	For example, the strings "010" and "1010" are alternating, while the string "0100" is not.
//
// Example:
// Input: s = "111000"
// Output: 2
// Explanation: Use the first operation two times to make s = "100011".
// Then, use the second operation on the third and sixth elements to make s = "101010".
//
// Constraints:
// 1 <= s.length <= 105
// 	s[i] is either '0' or '1'.
//

class Solution {
public:
    int minFlips(string s) {
        int n = s.length();
        string s2 = s + s; // Simulate rotations by concatenation
        int minFlips = INT_MAX;

        // Precompute the two alternating patterns
        string alt1, alt2;
        for (int i = 0; i < 2 * n; ++i) {
            alt1 += (i % 2 == 0) ? '0' : '1';
            alt2 += (i % 2 == 0) ? '1' : '0';
        }

        int flips1 = 0, flips2 = 0;
        for (int i = 0; i < 2 * n; ++i) {
            if (s2[i] != alt1[i]) flips1++;
            if (s2[i] != alt2[i]) flips2++;

            // Once we have processed n characters, we need to slide the window
            if (i >= n) {
                if (s2[i - n] != alt1[i - n]) flips1--;
                if (s2[i - n] != alt2[i - n]) flips2--;
            }

            // When we have a full window of size n, update the minimum flips
            if (i >= n - 1) {
                minFlips = min(minFlips, min(flips1, flips2));
            }
        }

        return minFlips;            
    }
};
