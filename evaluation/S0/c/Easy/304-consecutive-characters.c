// Source: https://leetcode.com/problems/consecutive-characters/   |   Difficulty: Easy
//
// Problem Description:
// The power of the string is the maximum length of a non-empty substring that contains only one unique character.
//
// Given a string s, return the power of s.
//
// Example:
// Input: s = "leetcode"
// Output: 2
// Explanation: The substring "ee" is of length 2 with the character 'e' only.
//
// Constraints:
// 1 <= s.length <= 500
// 	s consists of only lowercase English letters.
//

int maxPower(char* s) {
    int max_power = 1;
    int current_power = 1;
    int length = strlen(s);

    for (int i = 1; i < length; i++) {
        if (s[i] == s[i - 1]) {
            current_power++;
        } else {
            if (current_power > max_power) {
                max_power = current_power;
            }
            current_power = 1;
        }
    }

    if (current_power > max_power) {
        max_power = current_power;
    }

    return max_power;       
}
