// Source: https://leetcode.com/problems/minimum-changes-to-make-alternating-binary-string/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string s consisting only of the characters '0' and '1'. In one operation, you can change any '0' to '1' or vice versa.
//
// The string is called alternating if no two adjacent characters are equal. For example, the string "010" is alternating, while the string "0100" is not.
//
// Return the minimum number of operations needed to make s alternating.
//
// Example:
// Input: s = "0100"
// Output: 1
// Explanation: If you change the last character to '1', s will be "0101", which is alternating.
//
// Constraints:
// 1 <= s.length <= 104
// 	s[i] is either '0' or '1'.
//

int minOperations(char* s) {
    int count1 = 0; // Count for pattern "0101..."
    int count2 = 0; // Count for pattern "1010..."
    for (int i = 0; s[i] != '\0'; i++) {
        if (i % 2 == 0) {
            if (s[i] != '0') {
                count1++;
            }
            if (s[i] != '1') {
                count2++;
            }
        } else {
            if (s[i] != '1') {
                count1++;
            }
            if (s[i] != '0') {
                count2++;
            }
        }
    }
    return count1 < count2 ? count1 : count2;       
}
