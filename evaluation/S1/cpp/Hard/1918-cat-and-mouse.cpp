// Source: https://leetcode.com/problems/cat-and-mouse/   |   Difficulty: Hard
//
// Problem Description:
// A game on an undirected graph is played by two players, Mouse and Cat, who alternate turns.
//
// The graph is given as follows: graph[a] is a list of all nodes b such that ab is an edge of the graph.
//
// The mouse starts at node 1 and goes first, the cat starts at node 2 and goes second, and there is a hole at node 0.
//
// During each player's turn, they must travel along one edge of the graph that meets where they are.  For example, if the Mouse is at node 1, it must travel to any node in graph[1].
//
// Additionally, it is not allowed for the Cat to travel to the Hole (node 0).
//
// Then, the game can end in three ways:
//
//
// 	If ever the Cat occupies the same node as the Mouse, the Cat wins.
// 	If ever the Mouse reaches the Hole, the Mouse wins.
// 	If ever a position is repeated (i.e., the players are in the same position as a previous turn, and it is the same player's turn to move), the game is a draw.
//
//
// Given a graph, and assuming both players play optimally, return
//
//
// 	1 if the mouse wins the game,
// 	2 if the cat wins the game, or
// 	0 if the game is a draw.
//
// Example:
// Input: graph = [[2,5],[3],[0,4,5],[1,4,5],[2,3],[0,2,3]]
// Output: 0
//
// Constraints:
// 3 <= graph.length <= 50
// 	1 <= graph[i].length < graph.length
// 	0 <= graph[i][j] < graph.length
// 	graph[i][j] != i
// 	graph[i] is unique.
// 	The mouse and the cat can always move.
//
// Helpful references (internal KB):
// - Games on arbitrary graphs (graph, array, dfs, game-theory)
//   • When to use: Use this algorithm to determine the outcome (win, lose, or draw) for every possible starting position in a two-player game played on a directed graph, assuming both players play optimally.
//   • Idea: This algorithm classifies each vertex in a directed graph as a winning, losing, or draw state for a two-player game. It iteratively applies rules based on neighbor states, optimized by a Depth-First Search on the reversed graph, achieving an O(M) time complexity.
//   • Invariants: A vertex `u` is a winning state if and only if it has at least one successor `v` that is a losing state.; A vertex `u` is a losing state if and only if all its successors `v` are winning states.
//   • Tips: Construct the reversed graph to efficiently propagate state classifications from successors to predecessors.; Initialize states for terminal vertices (those with no outgoing edges) as losing states.
//   • Pitfalls: Forgetting to account for draw states, which occur when neither winning nor losing conditions are met.; Incorrectly classifying terminal nodes; they are typically losing states in normal play games.
// - Balanced Ternary (number, string, enumeration, simulation)
//   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
//   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
//   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
//   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
//   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
// - Placing Bishops on a Chessboard (array, counting, dp-2d)
//   • When to use: Use when counting non-attacking piece placements on a grid, especially when the problem can be decomposed into independent subproblems based on board properties like diagonals.
//   • Idea: This algorithm employs 2D dynamic programming to count the total number of ways to place non-attacking bishops on a chessboard. It leverages the independence of placements on black and white squares/diagonals, achieving a polynomial time complexity.
//   • Invariants: For any diagonal `i`, `D[i][j]` represents the number of ways to place `j` bishops on diagonal `i`.; Bishops placed on black diagonals do not attack bishops placed on white diagonals.
//   • Tips: Decompose the problem into independent subproblems for black and white squares/diagonals.; Identify the state for DP, typically `dp[diagonal_index][bishops_placed]`.
//   • Pitfalls: Incorrectly calculating the number of squares on each diagonal.; Overlapping bishops if diagonal definitions are not precise.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int catMouseGame(vector<vector<int>>& graph) {
        const int n = graph.size();
        // state: mousePos * n + catPos, turn: 0=mouse,1=cat
        const int totalStates = n * n * 2;
        vector<int> stateType(totalStates, 0); // 0=unknown,1=mouse win,2=cat win
        vector<int> outDegree(totalStates, 0);

        // Initialize outDegrees
        for (int m = 0; m < n; ++m) {
            for (int c = 0; c < n; ++c) {
                for (int t = 0; t < 2; ++t) {
                    int stateIdx = (m * n + c) * 2 + t;
                    if (t == 0) { // mouse turn
                        outDegree[stateIdx] = graph[m].size();
                    } else { // cat turn
                        outDegree[stateIdx] = graph[c].size() - (find(graph[c].begin(), graph[c].end(), 0) != graph[c].end() ? 1 : 0);
                    }
                }
            }
        }

        queue<int> q;

        // Base cases
        for (int c = 1; c < n; ++c) {
            for (int t = 0; t < 2; ++t) {
                int mouseWinState = (0 * n + c) * 2 + t;
                stateType[mouseWinState] = 1; // mouse wins
                q.push(mouseWinState);

                int catWinState = (c * n + c) * 2 + t;
                stateType[catWinState] = 2; // cat wins
                q.push(catWinState);
            }
        }

        // BFS on reversed graph
        while (!q.empty()) {
            int currState = q.front();
            q.pop();
            int currType = stateType[currState];
            int mPos = (currState / 2) / n;
            int cPos = (currState / 2) % n;
            int turn = currState % 2;

            if (turn == 0) { // mouse's turn, came from cat's turn
                for (int prevCat : graph[cPos]) {
                    if (prevCat == 0) continue; // cat cannot go to hole
                    int prevState = (mPos * n + prevCat) * 2 + 1;
                    if (stateType[prevState] != 0) continue;

                    if (currType == 2) { // cat wins in current state
                        stateType[prevState] = 2; // cat wins
                        q.push(prevState);
                    } else {
                        outDegree[prevState]--;
                        if (outDegree[prevState] == 0) {
                            stateType[prevState] = 1; // mouse wins
                            q.push(prevState);
                        }
                    }
                }
            } else { // cat's turn, came from mouse's turn
                for (int prevMouse : graph[mPos]) {
                    int prevState = (prevMouse * n + cPos) * 2 + 0;
                    if (stateType[prevState] != 0) continue;

                    if (currType == 1) { // mouse wins in current state
                        stateType[prevState] = 1; // mouse wins
                        q.push(prevState);
                    } else {
                        outDegree[prevState]--;
                        if (outDegree[prevState] == 0) {
                            stateType[prevState] = 2; // cat wins
                            q.push(prevState);
                        }
                    }
                }
            }
        }
        int startState = (1 * n + 2) * 2 + 0; // mouse at 1, cat at 2, mouse's turn
        return stateType[startState];
    }
};
