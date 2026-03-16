// Source: https://leetcode.com/problems/minimum-number-of-swaps-to-make-the-binary-string-alternating/   |   Difficulty: Medium
//
// Problem Description:
// Given a binary string s, return the minimum number of character swaps to make it alternating, or -1 if it is impossible.
//
// The string is called alternating if no two adjacent characters are equal. For example, the strings "010" and "1010" are alternating, while the string "0100" is not.
//
// Any two characters may be swapped, even if they are not adjacent.
//
// Example:
// Input: s = "111000"
// Output: 1
// Explanation: Swap positions 1 and 4: "111000" -> "101010"
// The string is now alternating.
//
// Constraints:
// 1 <= s.length <= 1000
// 	s[i] is either '0' or '1'.
//

class Solution {
public:
    int minSwaps(string s) {
        int count0 = 0, count1 = 0;
        for (char c : s) {
            if (c == '0') count0++;
            else count1++;
        }

        int n = s.length();
        if (abs(count0 - count1) > 1) return -1;

        int swaps1 = 0, swaps2 = 0;
        for (int i = 0; i < n; ++i) {
            char expectedChar1 = (i % 2 == 0) ? '0' : '1'; // Pattern "0101..."
            char expectedChar2 = (i % 2 == 0) ? '1' : '0'; // Pattern "1010..."

            if (s[i] != expectedChar1) swaps1++;
            if (s[i] != expectedChar2) swaps2++;
        }

        if (count0 > count1) {
            return swaps1 / 2; // Must follow pattern "0101..."
        } else if (count1 > count0) {
            return swaps2 / 2; // Must follow pattern "1010..."
        } else {
            return min(swaps1, swaps2) / 2; // Can follow either pattern
        }           
    }
};
