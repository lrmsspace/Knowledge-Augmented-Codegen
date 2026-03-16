// Source: https://leetcode.com/problems/find-the-first-player-to-win-k-games-in-a-row/   |   Difficulty: Medium
//
// Problem Description:
// A competition consists of n players numbered from 0 to n - 1.
//
// You are given an integer array skills of size n and a positive integer k, where skills[i] is the skill level of player i. All integers in skills are unique.
//
// All players are standing in a queue in order from player 0 to player n - 1.
//
// The competition process is as follows:
//
//
// 	The first two players in the queue play a game, and the player with the higher skill level wins.
// 	After the game, the winner stays at the beginning of the queue, and the loser goes to the end of it.
//
//
// The winner of the competition is the first player who wins k games in a row.
//
// Return the initial index of the winning player.
//
// Example:
// Input: skills = [4,2,6,3,9], k = 2
//
// Output: 2
//
// Explanation:
//
// Initially, the queue of players is [0,1,2,3,4]. The following process happens:
//
//
// 	Players 0 and 1 play a game, since the skill of player 0 is higher than that of player 1, player 0 wins. The resulting queue is [0,2,3,4,1].
// 	Players 0 and 2 play a game, since the skill of player 2 is higher than that of player 0, player 2 wins. The resulting queue is [2,3,4,1,0].
// 	Players 2 and 3 play a game, since the skill of player 2 is higher than that of player 3, player 2 wins. The resulting queue is [2,4,1,0,3].
//
//
// Player 2 won k = 2 games in a row, so the winner is player 2.
//
// Constraints:
// n == skills.length
// 	2 <= n <= 105
// 	1 <= k <= 109
// 	1 <= skills[i] <= 106
// 	All integers in skills are unique.
//
// Helpful references (internal KB):
// - kth-largest-element-in-an-array (array, merge-sort)
//   • When to use: Use Merge Sort when a stable, guaranteed O(N log N) time complexity is required, especially for large datasets or linked lists where random access is costly.
//   • Idea: Merge Sort is a divide-and-conquer algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and a space complexity of O(N).
//   • Invariants: Each sub-array passed to merge is sorted.; The merge operation combines two sorted sub-arrays into a single sorted array.
//   • Tips: Implement the merge step carefully to maintain stability.; Consider iterative implementation to avoid recursion depth limits.
//   • Pitfalls: High space complexity due to auxiliary arrays.; Overhead of recursion can be significant for small inputs.
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
// - Josephus Problem (number, dp-1d, recursion)
//   • When to use: Used to determine the position of the last remaining person in a circle where every k-th person is eliminated until only one remains. It models sequential removal processes in a circular arrangement.
//   • Idea: The Josephus Problem determines the position of the survivor in a circle of N people, where every K-th person is eliminated. The standard solution uses a recursive relation or dynamic programming, typically achieving O(N) time complexity.
//   • Invariants: The result J(n, k) represents the survivor's original 0-indexed position among n people.; Each recursive step J(n, k) correctly transforms the result from J(n-1, k) based on the k-th elimination.
//   • Tips: Use 0-indexing for a simpler and more elegant recursive formula.; Establish the base case for N=1 (the survivor is always 0 or 1).
//   • Pitfalls: Off-by-one errors when switching between 0-indexing and 1-indexing.; Incorrectly applying the modulo operator, especially with negative results in some languages.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int findWinningPlayer(vector<int>& skills, int k) {
        int n = skills.size();
        int winner = 0; // Start with the first player as the initial winner
        int consecutiveWins = 0; // Count of consecutive wins for the current winner

        for (int i = 1; i < n; ++i) {
            if (skills[i] > skills[winner]) {
                // If the current player has a higher skill, they become the new winner
                winner = i;
                consecutiveWins = 1; // Reset consecutive wins for the new winner
            } else {
                // If the current player loses, increment the consecutive wins for the current winner
                ++consecutiveWins;
            }

            // Check if the current winner has won k games in a row
            if (consecutiveWins == k) {
                return winner; // Return the index of the winning player
            }
        }

        return winner; // Return the index of the winning player after processing all players           
    }
};
