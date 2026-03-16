// Source: https://leetcode.com/problems/count-of-matches-in-tournament/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer n, the number of teams in a tournament that has strange rules:
//
//
// 	If the current number of teams is even, each team gets paired with another team. A total of n / 2 matches are played, and n / 2 teams advance to the next round.
// 	If the current number of teams is odd, one team randomly advances in the tournament, and the rest gets paired. A total of (n - 1) / 2 matches are played, and (n - 1) / 2 + 1 teams advance to the next round.
//
//
// Return the number of matches played in the tournament until a winner is decided.
//
// Example:
// Input: n = 7
// Output: 6
// Explanation: Details of the tournament: 
// - 1st Round: Teams = 7, Matches = 3, and 4 teams advance.
// - 2nd Round: Teams = 4, Matches = 2, and 2 teams advance.
// - 3rd Round: Teams = 2, Matches = 1, and 1 team is declared the winner.
// Total number of matches = 3 + 2 + 1 = 6.
//
// Constraints:
// 1 <= n <= 200
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



int numberOfMatches(int n){
    int total_matches = 0;
    while (n > 1) {
        if (n % 2 == 0) {
            total_matches += n / 2;
            n = n / 2;
        } else {
            total_matches += (n - 1) / 2;
            n = (n - 1) / 2 + 1;
        }
    }
    return total_matches;
}
