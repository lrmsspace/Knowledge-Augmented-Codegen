// Source: https://leetcode.com/problems/minimum-number-of-changes-to-make-binary-string-beautiful/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed binary string s having an even length.
//
// A string is beautiful if it's possible to partition it into one or more substrings such that:
//
//
// 	Each substring has an even length.
// 	Each substring contains only 1's or only 0's.
//
//
// You can change any character in s to 0 or 1.
//
// Return the minimum number of changes required to make the string s beautiful.
//
// Example:
// Input: s = "1001"
// Output: 2
// Explanation: We change s[1] to 1 and s[3] to 0 to get string "1100".
// It can be seen that the string "1100" is beautiful because we can partition it into "11|00".
// It can be proven that 2 is the minimum number of changes needed to make the string beautiful.
//
// Constraints:
// 2 <= s.length <= 105
// 	s has an even length.
// 	s[i] is either '0' or '1'.
//

int minChanges(char* s) {
    int count1 = 0;
    int count0 = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (i % 2 == 0) {
            if (s[i] == '0') {
                count1++;
            } else {
                count0++;
            }
        } else {
            if (s[i] == '0') {
                count0++;
            } else {
                count1++;
            }
        }
    }
    return count0 < count1 ? count0 : count1;       
}
