// Source: https://leetcode.com/problems/sum-game/   |   Difficulty: Medium
//
// Problem Description:
// Alice and Bob take turns playing a game, with Alice starting first.
//
// You are given a string num of even length consisting of digits and '?' characters. On each turn, a player will do the following if there is still at least one '?' in num:
//
//
// 	Choose an index i where num[i] == '?'.
// 	Replace num[i] with any digit between '0' and '9'.
//
//
// The game ends when there are no more '?' characters in num.
//
// For Bob to win, the sum of the digits in the first half of num must be equal to the sum of the digits in the second half. For Alice to win, the sums must not be equal.
//
//
// 	For example, if the game ended with num = "243801", then Bob wins because 2+4+3 = 8+0+1. If the game ended with num = "243803", then Alice wins because 2+4+3 != 8+0+3.
//
//
// Assuming Alice and Bob play optimally, return true if Alice will win and false if Bob will win.
//
// Example:
// Input: num = "5023"
// Output: false
// Explanation: There are no moves to be made.
// The sum of the first half is equal to the sum of the second half: 5 + 0 = 2 + 3.
//
// Constraints:
// 2 <= num.length <= 105
// 	num.length is even.
// 	num consists of only digits and '?'.
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

bool sumGame(char* num) {
    int len = strlen(num);
    int half = len / 2;
    int sumFirstHalf = 0, sumSecondHalf = 0;
    int countFirstHalf = 0, countSecondHalf = 0;

    for (int i = 0; i < half; i++) {
        if (num[i] == '?') {
            countFirstHalf++;
        } else {
            sumFirstHalf += num[i] - '0';
        }
    }

    for (int i = half; i < len; i++) {
        if (num[i] == '?') {
            countSecondHalf++;
        } else {
            sumSecondHalf += num[i] - '0';
        }
    }

    // Calculate the difference in sums and counts
    int diffSum = sumFirstHalf - sumSecondHalf;
    int diffCount = countFirstHalf - countSecondHalf;

    // Alice wins if the difference in sums cannot be balanced by the remaining '?' characters
    return diffSum * 2 != diffCount * 9;        
}
