// Source: https://leetcode.com/problems/minimum-moves-to-reach-target-score/   |   Difficulty: Medium
//
// Problem Description:
// You are playing a game with integers. You start with the integer 1 and you want to reach the integer target.
//
// In one move, you can either:
//
//
// 	Increment the current integer by one (i.e., x = x + 1).
// 	Double the current integer (i.e., x = 2 * x).
//
//
// You can use the increment operation any number of times, however, you can only use the double operation at most maxDoubles times.
//
// Given the two integers target and maxDoubles, return the minimum number of moves needed to reach target starting with 1.
//
// Example:
// Input: target = 5, maxDoubles = 0
// Output: 4
// Explanation: Keep incrementing by 1 until you reach target.
//
// Constraints:
// 1 <= target <= 109
// 	0 <= maxDoubles <= 100
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
    int minMoves(int target, int maxDoubles) {
        int moves = 0;
        while (target > 1) {
            if (maxDoubles > 0 && target % 2 == 0) {
                target /= 2;
                maxDoubles--;
            } else {
                target -= 1;
            }
            moves++;
        }
        return moves;           
    }
};
