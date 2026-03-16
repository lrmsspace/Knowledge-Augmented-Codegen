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
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int numberOfMatches(int n) {
        int totalMatches = 0;
        while (n > 1) {
            if (n % 2 == 0) {
                // 偶数队伍：进行 n/2 场比赛，n/2 队伍晋级
                totalMatches += n / 2;
                n = n / 2;
            } else {
                // 奇数队伍：进行 (n-1)/2 场比赛，(n-1)/2 + 1 队伍晋级
                totalMatches += (n - 1) / 2;
                n = (n - 1) / 2 + 1;
            }
        }
        return totalMatches;
    }
};
