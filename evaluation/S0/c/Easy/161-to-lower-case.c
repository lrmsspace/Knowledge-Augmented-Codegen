// Source: https://leetcode.com/problems/to-lower-case/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s, return the string after replacing every uppercase letter with the same lowercase letter.
//
// Example:
// Input: s = "Hello"
// Output: "hello"
//
// Constraints:
// 1 <= s.length <= 100
// 	s consists of printable ASCII characters.
//

char* toLowerCase(char* s) {
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] = s[i] + ('a' - 'A');
        }
    }
    return s;       
}
