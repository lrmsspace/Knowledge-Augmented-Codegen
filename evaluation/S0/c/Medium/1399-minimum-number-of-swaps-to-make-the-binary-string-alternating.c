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

int minSwaps(char* s) {
    int count0 = 0, count1 = 0;
    for (int i = 0; s[i]; i++) {
        if (s[i] == '0') {
            count0++;
        } else {
            count1++;
        }
    }

    int n = count0 + count1;
    if (abs(count0 - count1) > 1) {
        return -1;
    }

    int swaps1 = 0, swaps2 = 0;
    for (int i = 0; s[i]; i++) {
        if (i % 2 == 0) {
            if (s[i] == '0') {
                swaps2++;
            } else {
                swaps1++;
            }
        } else {
            if (s[i] == '0') {
                swaps1++;
            } else {
                swaps2++;
            }
        }
    }

    if (count0 > count1) {
        return swaps2 / 2;
    } else if (count1 > count0) {
        return swaps1 / 2;
    } else {
        return fmin(swaps1 / 2, swaps2 / 2);
    }       
}
