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
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int catMouseGame(int** graph, int graphSize, int* graphColSize) {
    enum { DRAW = 0, MOUSE_WIN = 1, CAT_WIN = 2 };
    int n = graphSize;
    int totalStates = n * n * 2; // mouse_pos, cat_pos, turn
    int *stateResult = (int*)calloc(totalStates, sizeof(int));
    int *outDegree = (int*)calloc(totalStates, sizeof(int));
    if (!stateResult || !outDegree) {
        free(stateResult);
        free(outDegree);
        return DRAW;
    }

    // Initialize outDegrees
    for (int m = 0; m < n; ++m) {
        for (int c = 0; c < n; ++c) {
            for (int t = 0; t < 2; ++t) {
                int idx = (m * n + c) * 2 + t;
                if (t == 0) { // Mouse's turn
                    outDegree[idx] = graphColSize[m];
                } else { // Cat's turn
                    outDegree[idx] = graphColSize[c];
                    for (int k = 0; k < graphColSize[c]; ++k) {
                        if (graph[c][k] == 0) outDegree[idx]--; // Cat cannot go to hole
                    }
                }
            }
        }
    }

    // Queue for BFS
    int *queue = (int*)malloc(totalStates * sizeof(int));
    if (!queue) {
        free(stateResult);
        free(outDegree);
        return DRAW;
    }
    int front = 0, back = 0;

    // Initialize terminal states
    for (int m = 0; m < n; ++m) {
        for (int c = 0; c < n; ++c) {
            for (int t = 0; t < 2; ++t) {
                int idx = (m * n + c) * 2 + t;
                if (m == 0) { // Mouse at hole
                    stateResult[idx] = MOUSE_WIN;
                    queue[back++] = idx;
                } else if (c == m) { // Cat catches mouse
                    stateResult[idx] = CAT_WIN;
                    queue[back++] = idx;
                }
            }
        }
    }

    // BFS to propagate results
    while (front < back) {
        int currIdx = queue[front++];
        int currResult = stateResult[currIdx];
        int m = (currIdx / 2) / n;
        int c = (currIdx / 2) % n;
        int t = currIdx % 2;

        if (t == 0) { // Mouse's turn
            for (int k = 0; k < graphColSize[c]; ++k) {
                int prevC = graph[c][k];
                if (prevC == 0) continue; // Cat cannot go to hole
                int prevIdx = (m * n + prevC) * 2 + 1;
                if (stateResult[prevIdx] != DRAW) continue;

                if (currResult == CAT_WIN) {
                    stateResult[prevIdx] = CAT_WIN;
                    queue[back++] = prevIdx;
                } else {
                    outDegree[prevIdx]--;
                    if (outDegree[prevIdx] == 0) {
                        stateResult[prevIdx] = MOUSE_WIN;
                        queue[back++] = prevIdx;
                    }
                }
            }
        } else { // Cat's turn
            for (int k = 0; k < graphColSize[m]; ++k) {
                int prevM = graph[m][k];
                int prevIdx = (prevM * n + c) * 2 + 0;
                if (stateResult[prevIdx] != DRAW) continue;

                if (currResult == MOUSE_WIN) {
                    stateResult[prevIdx] = MOUSE_WIN;
                    queue[back++] = prevIdx;
                } else {
                    outDegree[prevIdx]--;
                    if (outDegree[prevIdx] == 0) {
                        stateResult[prevIdx] = CAT_WIN;
                        queue[back++] = prevIdx;
                    }
                }
            }
        }
    }
    int result = stateResult[(1 * n + 2) * 2 + 0]; // Mouse at 1, Cat at 2, Mouse's turn
    free(stateResult);
    free(outDegree);
    free(queue);
    return result;
}
