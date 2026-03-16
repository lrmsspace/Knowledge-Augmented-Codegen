// Source: https://leetcode.com/problems/second-largest-digit-in-a-string/   |   Difficulty: Easy
//
// Problem Description:
// Given an alphanumeric string s, return the second largest numerical digit that appears in s, or -1 if it does not exist.
//
// An alphanumeric string is a string consisting of lowercase English letters and digits.
//
// Example:
// Input: s = "dfa12321afd"
// Output: 2
// Explanation: The digits that appear in s are [1, 2, 3]. The second largest digit is 2.
//
// Constraints:
// 1 <= s.length <= 500
// 	s consists of only lowercase English letters and digits.
//

int secondHighest(char* s) {
    int digits[10] = {0};
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            digits[s[i] - '0'] = 1;
        }
    }

    int largest = -1;
    int second_largest = -1;

    for (int i = 9; i >= 0; i--) {
        if (digits[i]) {
            if (largest == -1) {
                largest = i;
            } else if (second_largest == -1) {
                second_largest = i;
                break;
            }
        }
    }

    return second_largest;      
}
