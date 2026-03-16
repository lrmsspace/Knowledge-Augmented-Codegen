// Source: https://leetcode.com/problems/vowels-game-in-a-string/   |   Difficulty: Medium
//
// Problem Description:
// Alice and Bob are playing a game on a string.
//
// You are given a string s, Alice and Bob will take turns playing the following game where Alice starts first:
//
//
// 	On Alice's turn, she has to remove any non-empty substring from s that contains an odd number of vowels.
// 	On Bob's turn, he has to remove any non-empty substring from s that contains an even number of vowels.
//
//
// The first player who cannot make a move on their turn loses the game. We assume that both Alice and Bob play optimally.
//
// Return true if Alice wins the game, and false otherwise.
//
// The English vowels are: a, e, i, o, and u.
//
// Example:
// Input: s = "leetcoder"
//
// Output: true
//
// Explanation:
// Alice can win the game as follows:
//
//
// 	Alice plays first, she can delete the underlined substring in s = "leetcoder" which contains 3 vowels. The resulting string is s = "der".
// 	Bob plays second, he can delete the underlined substring in s = "der" which contains 0 vowels. The resulting string is s = "er".
// 	Alice plays third, she can delete the whole string s = "er" which contains 1 vowel.
// 	Bob plays fourth, since the string is empty, there is no valid play for Bob. So Alice wins the game.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists only of lowercase English letters.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private boolean isVowel(char c) {
        return "aeiou".indexOf(c) != -1;
    }
    public boolean doesAliceWin(String s) {
        int vowelCount = 0;
        for (char c : s.toCharArray()) {
            if (isVowel(c)) {
                vowelCount++;
            }
        }
        return vowelCount % 2 == 1;         
    }
}
