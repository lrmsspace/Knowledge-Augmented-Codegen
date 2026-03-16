// Source: https://leetcode.com/problems/minimum-number-of-chairs-in-a-waiting-room/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string s. Simulate events at each second i:
//
//
// 	If s[i] == 'E', a person enters the waiting room and takes one of the chairs in it.
// 	If s[i] == 'L', a person leaves the waiting room, freeing up a chair.
//
//
// Return the minimum number of chairs needed so that a chair is available for every person who enters the waiting room given that it is initially empty.
//
// Example:
// Input: s = "EEEEEEE"
//
// Output: 7
//
// Explanation:
//
// After each second, a person enters the waiting room and no person leaves it. Therefore, a minimum of 7 chairs is needed.
//
// Constraints:
// 1 <= s.length <= 50
// 	s consists only of the letters 'E' and 'L'.
// 	s represents a valid sequence of entries and exits.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minimumChairs(char* s) {
    int current_chairs = 0;
    int max_chairs = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == 'E') {
            current_chairs++;
            if (current_chairs > max_chairs) {
                max_chairs = current_chairs;
            }
        } else if (s[i] == 'L') {
            current_chairs--;
        }
    }

    return max_chairs;      
}
