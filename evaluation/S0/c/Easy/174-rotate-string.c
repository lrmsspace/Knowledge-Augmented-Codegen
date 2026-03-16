// Source: https://leetcode.com/problems/rotate-string/   |   Difficulty: Easy
//
// Problem Description:
// Given two strings s and goal, return true if and only if s can become goal after some number of shifts on s.
//
// A shift on s consists of moving the leftmost character of s to the rightmost position.
//
//
// 	For example, if s = "abcde", then it will be "bcdea" after one shift.
//
// Example:
// Input: s = "abcde", goal = "cdeab"
// Output: true
//
// Constraints:
// 1 <= s.length, goal.length <= 100
// 	s and goal consist of lowercase English letters.
//

bool rotateString(char* s, char* goal) {
    int len_s = 0, len_goal = 0;
    while (s[len_s]) len_s++;
    while (goal[len_goal]) len_goal++;
    if (len_s != len_goal) return false;

    for (int i = 0; i < len_s; i++) {
        bool match = true;
        for (int j = 0; j < len_s; j++) {
            if (s[(i + j) % len_s] != goal[j]) {
                match = false;
                break;
            }
        }
        if (match) return true;
    }
    return false;       
}
