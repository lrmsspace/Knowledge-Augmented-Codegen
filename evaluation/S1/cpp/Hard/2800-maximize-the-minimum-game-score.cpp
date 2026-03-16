// Source: https://leetcode.com/problems/maximize-the-minimum-game-score/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array points of size n and an integer m. There is another array gameScore of size n, where gameScore[i] represents the score achieved at the ith game. Initially, gameScore[i] == 0 for all i.
//
// You start at index -1, which is outside the array (before the first position at index 0). You can make at most m moves. In each move, you can either:
//
//
// 	Increase the index by 1 and add points[i] to gameScore[i].
// 	Decrease the index by 1 and add points[i] to gameScore[i].
//
//
// Note that the index must always remain within the bounds of the array after the first move.
//
// Return the maximum possible minimum value in gameScore after at most m moves.
//
// Example:
// Input: points = [2,4], m = 3
//
// Output: 4
//
// Explanation:
//
// Initially, index i = -1 and gameScore = [0, 0].
//
//
// 	
// 		
// 			Move
// 			Index
// 			gameScore
// 		
// 	
// 	
// 		
// 			Increase i
// 			0
// 			[2, 0]
// 		
// 		
// 			Increase i
// 			1
// 			[2, 4]
// 		
// 		
// 			Decrease i
// 			0
// 			[4, 4]
// 		
// 	
//
//
// The minimum value in gameScore is 4, and this is the maximum possible minimum among all configurations. Hence, 4 is the output.
//
// Constraints:
// 2 <= n == points.length <= 5 * 104
// 	1 <= points[i] <= 106
// 	1 <= m <= 109
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - 15 Puzzle Game: Existence Of The Solution (matrix, number, counting)
//   • When to use: Use this to quickly determine if a given 15-puzzle board configuration can be solved, avoiding exhaustive search. It's applicable when the goal is to check solvability rather than finding the solution path.
//   • Idea: This algorithm determines the solvability of a 15-puzzle configuration by analyzing the parity of inversions in the tile permutation and the blank tile's row. It involves counting inversions, which typically takes O(N^2) time for N tiles, or O(N log N) with a more advanced counting method.
//   • Invariants: The permutation used for inversion counting always excludes the blank tile.; Each pair of tiles (i, j) with i < j is considered exactly once for inversion counting.
//   • Tips: Remember to exclude the blank tile (0) when forming the permutation for inversion counting.; For a 4x4 grid, the blank tile's row (from bottom, 1-indexed) is crucial for the parity check.
//   • Pitfalls: Incorrectly including the blank tile (0) in the inversion count.; Miscalculating the blank tile's row index (e.g., 0-indexed from top vs. 1-indexed from bottom).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    long long maxScore(vector<int>& points, int m) {
        int n = points.size();
        long long left = 0, right = 1e15, answer = 0;

        auto canAchieve = [&](long long minScore) {
            long long movesUsed = 0;
            long long currentScore = 0;
            for (int i = 0; i < n; ++i) {
                currentScore += points[i];
                if (currentScore < minScore) {
                    long long needed = (minScore - currentScore + points[i] - 1) / points[i];
                    movesUsed += needed;
                    currentScore += needed * points[i];
                }
                if (movesUsed > m) return false;
            }
            return movesUsed <= m;
        };

        while (left <= right) {
            long long mid = left + (right - left) / 2;
            if (canAchieve(mid)) {
                answer = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return answer;          
    }
};
