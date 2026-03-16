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

int minFlips(char* s) {
    int n = strlen(s);
    int total0 = 0, total1 = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '0') {
            total0++;
        } else {
            total1++;
        }
    }

    int curr0 = 0, curr1 = 0;
    int minFlips = n;
    for (int i = 0; i < 2 * n; i++) {
        if (s[i % n] == (i % 2 == 0 ? '0' : '1')) {
            curr1++;
        }
        if (s[i % n] == (i % 2 == 1 ? '0' : '1')) {
            curr0++;
        }

        if (i >= n) {
            if (s[(i - n) % n] == ((i - n) % 2 == 0 ? '0' : '1')) {
                curr1--;
            }
            if (s[(i - n) % n] == ((i - n) % 2 == 1 ? '0' : '1')) {
                curr0--;
            }
        }

        if (i >= n - 1) {
            int flipsForPattern1 = (n / 2 + n % 2) - curr1 + total1 - (n / 2 + n % 2 - curr1);
            int flipsForPattern0 = (n / 2) - curr0 + total0 - (n / 2 - curr0);
            minFlips = fmin(minFlips, fmin(flipsForPattern1, flipsForPattern0));
        }
    }

    return minFlips;        
}
