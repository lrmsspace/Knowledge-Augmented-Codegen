// Source: https://leetcode.com/problems/check-if-word-is-valid-after-substitutions/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, determine if it is valid.
//
// A string s is valid if, starting with an empty string t = "", you can transform t into s after performing the following operation any number of times:
//
//
// 	Insert string "abc" into any position in t. More formally, t becomes tleft + "abc" + tright, where t == tleft + tright. Note that tleft and tright may be empty.
//
//
// Return true if s is a valid string, otherwise, return false.
//
// Example:
// Input: s = "aabcbc"
// Output: true
// Explanation:
// "" -> "abc" -> "aabcbc"
// Thus, "aabcbc" is valid.
//
// Constraints:
// 1 <= s.length <= 2 * 104
// 	s consists of letters 'a', 'b', and 'c'
//

bool isValid(char* s) {
    char stack[20000];
    int top = -1;
    for (int i = 0; s[i] != '\0'; i++) {
        char c = s[i];
        if (c == 'c') {
            if (top < 1 || stack[top] != 'b' || stack[top - 1] != 'a') {
                return false;
            }
            top -= 2; // Pop 'b' and 'a'
        } else {
            stack[++top] = c; // Push 'a' or 'b'
        }
    }
    return top == -1; // Stack should be empty if valid     
}
