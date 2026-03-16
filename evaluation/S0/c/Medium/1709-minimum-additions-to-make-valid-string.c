// Source: https://leetcode.com/problems/minimum-additions-to-make-valid-string/   |   Difficulty: Medium
//
// Problem Description:
// Given a string word to which you can insert letters "a", "b" or "c" anywhere and any number of times, return the minimum number of letters that must be inserted so that word becomes valid.
//
// A string is called valid if it can be formed by concatenating the string "abc" several times.
//
// Example:
// Input: word = "b"
// Output: 2
// Explanation: Insert the letter "a" right before "b", and the letter "c" right next to "b" to obtain the valid string "abc".
//
// Constraints:
// 1 <= word.length <= 50
// 	word consists of letters "a", "b" and "c" only.
//

int addMinimum(char* word) {
    int res = 0;
    int state = 0; // 0:a, 1:b, 2:c

    for (int i = 0; word[i] != '\0'; i++) {
        char ch = word[i];
        if (ch == 'a') {
            if (state == 0) {
                // stay in state 0
            } else if (state == 1) {
                res += 1; // missing 'c'
            } else if (state == 2) {
                res += 2; // missing 'b' and 'c'
            }
            state = 1; // move to state 1
        } else if (ch == 'b') {
            if (state == 0) {
                res += 1; // missing 'a'
            } else if (state == 1) {
                // stay in state 1
            } else if (state == 2) {
                res += 1; // missing 'c'
            }
            state = 2; // move to state 2
        } else if (ch == 'c') {
            if (state == 0) {
                res += 2; // missing 'a' and 'b'
            } else if (state == 1) {
                res += 1; // missing 'b'
            } else if (state == 2) {
                // stay in state 2
            }
            state = 0; // move to state 0
        }
    }

    // Final adjustments based on the last state
    if (state == 0) {
        res += 2; // need 'b' and 'c'
    } else if (state == 1) {
        res += 1; // need 'c'
    } // if state == 2, no additions needed

    return res;     
}
