// Source: https://leetcode.com/problems/can-convert-string-in-k-moves/   |   Difficulty: Medium
//
// Problem Description:
// Given two strings s and t, your goal is to convert s into t in k moves or less.
//
// During the ith (1 <= i <= k) move you can:
//
//
// 	Choose any index j (1-indexed) from s, such that 1 <= j <= s.length and j has not been chosen in any previous move, and shift the character at that index i times.
// 	Do nothing.
//
//
// Shifting a character means replacing it by the next letter in the alphabet (wrapping around so that 'z' becomes 'a'). Shifting a character by i means applying the shift operations i times.
//
// Remember that any index j can be picked at most once.
//
// Return true if it's possible to convert s into t in no more than k moves, otherwise return false.
//
// Example:
// Input: s = "input", t = "ouput", k = 9
// Output: true
// Explanation: In the 6th move, we shift 'i' 6 times to get 'o'. And in the 7th move we shift 'n' to get 'u'.
//
// Constraints:
// 1 <= s.length, t.length <= 10^5
// 	0 <= k <= 10^9
// 	s, t contain only lowercase English letters.
//

bool canConvertString(char* s, char* t, int k) {
    int len_s = strlen(s);
    int len_t = strlen(t);
    if (len_s != len_t) {
        return false;
    }

    int shift_count[26];
    memset(shift_count, 0, sizeof(shift_count));

    for (int i = 0; i < len_s; i++) {
        int diff = t[i] - s[i];
        if (diff < 0) {
            diff += 26;
        }
        if (diff > 0) {
            shift_count[diff]++;
        }
    }

    for (int i = 1; i <= 25; i++) {
        if (shift_count[i] > 0) {
            int max_shift_needed = i + (shift_count[i] - 1) * 26;
            if (max_shift_needed > k) {
                return false;
            }
        }
    }

    return true;        
}
