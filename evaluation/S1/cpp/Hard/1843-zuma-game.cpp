// Source: https://leetcode.com/problems/zuma-game/   |   Difficulty: Hard
//
// Problem Description:
// You are playing a variation of the game Zuma.
//
// In this variation of Zuma, there is a single row of colored balls on a board, where each ball can be colored red 'R', yellow 'Y', blue 'B', green 'G', or white 'W'. You also have several colored balls in your hand.
//
// Your goal is to clear all of the balls from the board. On each turn:
//
//
// 	Pick any ball from your hand and insert it in between two balls in the row or on either end of the row.
// 	If there is a group of three or more consecutive balls of the same color, remove the group of balls from the board.
// 	
// 		If this removal causes more groups of three or more of the same color to form, then continue removing each group until there are none left.
// 	
// 	
// 	If there are no more balls on the board, then you win the game.
// 	Repeat this process until you either win or do not have any more balls in your hand.
//
//
// Given a string board, representing the row of balls on the board, and a string hand, representing the balls in your hand, return the minimum number of balls you have to insert to clear all the balls from the board. If you cannot clear all the balls from the board using the balls in your hand, return -1.
//
// Example:
// Input: board = "WRRBBW", hand = "RB"
// Output: -1
// Explanation: It is impossible to clear all the balls. The best you can do is:
// - Insert 'R' so the board becomes WRRRBBW. WRRRBBW -> WBBW.
// - Insert 'B' so the board becomes WBBBW. WBBBW -> WW.
// There are still balls remaining on the board, and you are out of balls to insert.
//
// Constraints:
// 1 <= board.length <= 16
// 	1 <= hand.length <= 5
// 	board and hand consist of the characters 'R', 'Y', 'B', 'G', and 'W'.
// 	The initial row of balls on the board will not have any groups of three or more consecutive balls of the same color.
//
// Helpful references (internal KB):
// - Breadth-first search (graph, array, stack, bfs, enumeration)
//   • When to use: Use when finding the shortest path in an unweighted graph or traversing a graph level by level. It is suitable for exploring all reachable nodes from a source in increasing order of distance.
//   • Idea: Breadth-First Search (BFS) is a graph traversal algorithm that explores all the neighbor nodes at the current depth level before moving on to nodes at the next depth level. It finds the shortest path in an unweighted graph in O(V + E) time.
//   • Invariants: All nodes currently in the queue are at the same or adjacent depth level.; All 'marked' nodes have been visited, and their 'distTo' values are the shortest path from the source.
//   • Tips: Use a queue to manage nodes to visit, ensuring level-by-level exploration.; Maintain a 'visited' array or set to prevent cycles and redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.; Incorrectly using a stack instead of a queue will result in Depth-First Search behavior.
// - 15 Puzzle Game: Existence Of The Solution (matrix, number, counting)
//   • When to use: Use this to quickly determine if a given 15-puzzle board configuration can be solved, avoiding exhaustive search. It's applicable when the goal is to check solvability rather than finding the solution path.
//   • Idea: This algorithm determines the solvability of a 15-puzzle configuration by analyzing the parity of inversions in the tile permutation and the blank tile's row. It involves counting inversions, which typically takes O(N^2) time for N tiles, or O(N log N) with a more advanced counting method.
//   • Invariants: The permutation used for inversion counting always excludes the blank tile.; Each pair of tiles (i, j) with i < j is considered exactly once for inversion counting.
//   • Tips: Remember to exclude the blank tile (0) when forming the permutation for inversion counting.; For a 4x4 grid, the blank tile's row (from bottom, 1-indexed) is crucial for the parity check.
//   • Pitfalls: Incorrectly including the blank tile (0) in the inversion count.; Miscalculating the blank tile's row index (e.g., 0-indexed from top vs. 1-indexed from bottom).
// - Suffix Automaton (string, simulation)
//   • When to use: Use when needing to efficiently process all substrings or suffixes of a given string, especially for counting distinct substrings, finding occurrences, or other complex string pattern problems. It provides linear time solutions for many tasks.
//   • Idea: A suffix automaton is a directed acyclic graph that compactly represents all distinct substrings of a given string. It enables solving a wide range of string-related problems in linear time, typically O(N) or O(N log A) where N is string length and A is alphabet size.
//   • Invariants: Every path from the initial state corresponds to a distinct substring of the original string.; Each state in the automaton represents a set of substrings that share the same end positions.
//   • Tips: Understand the two types of links: suffix links (parent) and transition links (children).; Construction is typically incremental, adding characters one by one.
//   • Pitfalls: Implementation complexity is high; careful handling of state creation and link updates is crucial.; Off-by-one errors in length calculations or suffix link assignments are common.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int findMinStep(string board, string hand) {
        unordered_map<char, int> handCount;
        for (char c : hand) {
            handCount[c]++;
        }

        queue<pair<string, unordered_map<char, int>>> q;
        q.push({board, handCount});
        int steps = 0;

        auto removeConsecutive = [](string s) {
            bool found = true;
            while (found) {
                found = false;
                for (int i = 0; i < s.size();) {
                    int j = i;
                    while (j < s.size() && s[j] == s[i]) j++;
                    if (j - i >= 3) {
                        s = s.substr(0, i) + s.substr(j);
                        found = true;
                    } else {
                        i = j;
                    }
                }
            }
            return s;
        };

        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                auto [currBoard, currHand] = q.front();
                q.pop();

                if (currBoard.empty()) {
                    return steps;
                }

                for (int j = 0; j <= currBoard.size(); j++) {
                    for (auto& [color, count] : currHand) {
                        if (count == 0) continue;

                        string newBoard = currBoard.substr(0, j) + color + currBoard.substr(j);
                        newBoard = removeConsecutive(newBoard);

                        auto newHand = currHand;
                        newHand[color]--;

                        q.push({newBoard, newHand});
                    }
                }
            }
            steps++;
        }

        return -1;
    }
};
