// Source: https://leetcode.com/problems/buddy-strings/   |   Difficulty: Easy
//
// Problem Description:
// Given two strings s and goal, return true if you can swap two letters in s so the result is equal to goal, otherwise, return false.
//
// Swapping letters is defined as taking two indices i and j (0-indexed) such that i != j and swapping the characters at s[i] and s[j].
//
//
// 	For example, swapping at indices 0 and 2 in "abcd" results in "cbad".
//
// Example:
// Input: s = "ab", goal = "ba"
// Output: true
// Explanation: You can swap s[0] = 'a' and s[1] = 'b' to get "ba", which is equal to goal.
//
// Constraints:
// 1 <= s.length, goal.length <= 2 * 104
// 	s and goal consist of lowercase letters.
//

bool buddyStrings(char* s, char* goal) {
    int len_s = 0, len_g = 0;
    while (s[len_s]) len_s++;
    while (goal[len_g]) len_g++;
    if (len_s != len_g) return false;

    int diff_indices[2] = {-1, -1};
    int diff_count = 0;
    int char_count[26] = {0};
    bool has_duplicate = false;

    for (int i = 0; i < len_s; i++) {
        char_count[s[i] - 'a']++;
        if (char_count[s[i] - 'a'] > 1) {
            has_duplicate = true;
        }
        if (s[i] != goal[i]) {
            if (diff_count < 2) {
                diff_indices[diff_count] = i;
            }
            diff_count++;
        }
    }

    if (diff_count == 2) {
        return s[diff_indices[0]] == goal[diff_indices[1]] &&
               s[diff_indices[1]] == goal[diff_indices[0]];
    } else if (diff_count == 0) {
        return has_duplicate;
    } else {
        return false;
    }       
}
