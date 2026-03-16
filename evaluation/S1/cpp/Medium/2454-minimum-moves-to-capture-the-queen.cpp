// Source: https://leetcode.com/problems/minimum-moves-to-capture-the-queen/   |   Difficulty: Medium
//
// Problem Description:
// There is a 1-indexed 8 x 8 chessboard containing 3 pieces.
//
// You are given 6 integers a, b, c, d, e, and f where:
//
//
// 	(a, b) denotes the position of the white rook.
// 	(c, d) denotes the position of the white bishop.
// 	(e, f) denotes the position of the black queen.
//
//
// Given that you can only move the white pieces, return the minimum number of moves required to capture the black queen.
//
// Note that:
//
//
// 	Rooks can move any number of squares either vertically or horizontally, but cannot jump over other pieces.
// 	Bishops can move any number of squares diagonally, but cannot jump over other pieces.
// 	A rook or a bishop can capture the queen if it is located in a square that they can move to.
// 	The queen does not move.
//
// Example:
// Input: a = 1, b = 1, c = 8, d = 8, e = 2, f = 3
// Output: 2
// Explanation: We can capture the black queen in two moves by moving the white rook to (1, 3) then to (2, 3).
// It is impossible to capture the black queen in less than two moves since it is not being attacked by any of the pieces at the beginning.
//
// Constraints:
// 1 <= a, b, c, d, e, f <= 8
// 	No two pieces are on the same square.
//
// Helpful references (internal KB):
// - Breadth-first search (graph, queue, array, bfs)
//   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes level by level. It is also suitable for problems requiring traversal of all nodes at a specific distance from a source.
//   • Idea: Breadth-first search systematically explores a graph level by level, ensuring that all nodes at distance k are visited before any nodes at distance k+1. It finds the shortest path in terms of number of edges for unweighted graphs in O(V + E) time.
//   • Invariants: All nodes currently in the queue have been discovered and marked, but their adjacent nodes have not yet been fully explored.; For any node v marked as visited, distTo[v] stores the shortest path length from the source s to v.
//   • Tips: Use a queue to manage nodes to visit.; Mark nodes as visited to prevent cycles and redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect paths.; Not handling disconnected graphs correctly.
// - Placing Bishops on a Chessboard (array, matrix, dp-2d, recursion)
//   • When to use: Use this approach for counting arrangements of non-attacking pieces on a grid, particularly when piece movement is restricted to specific geometric lines like diagonals. It is effective when constraints allow for independent processing of subsets of the grid.
//   • Idea: This method employs 2D dynamic programming to count the number of ways to place bishops on a chessboard such that no two bishops attack each other. It leverages the property that bishops only attack along diagonals of the same color, processing diagonals iteratively to build up solutions in polynomial time.
//   • Invariants: All bishops placed on diagonals with index less than `i` do not attack each other.; The count `D[i][j]` correctly reflects all valid placements of `j` bishops on diagonals up to `i` of the same color.
//   • Tips: Exploit problem-specific constraints, such as bishop movement along diagonals, to simplify state definitions.; Decompose the problem by processing diagonals of the same color independently to avoid complex interactions.
//   • Pitfalls: Incorrectly handling diagonal numbering or miscalculating the number of squares in a diagonal.; Off-by-one errors when determining the number of available squares for placing a bishop on a diagonal.
// - Games on arbitrary graphs (graph, array, dfs, game-theory)
//   • When to use: Use this algorithm to determine the outcome (win, lose, or draw) for every possible starting position in a two-player game played on a directed graph, assuming both players play optimally.
//   • Idea: This algorithm classifies each vertex in a directed graph as a winning, losing, or draw state for a two-player game. It iteratively applies rules based on neighbor states, optimized by a Depth-First Search on the reversed graph, achieving an O(M) time complexity.
//   • Invariants: A vertex `u` is a winning state if and only if it has at least one successor `v` that is a losing state.; A vertex `u` is a losing state if and only if all its successors `v` are winning states.
//   • Tips: Construct the reversed graph to efficiently propagate state classifications from successors to predecessors.; Initialize states for terminal vertices (those with no outgoing edges) as losing states.
//   • Pitfalls: Forgetting to account for draw states, which occur when neither winning nor losing conditions are met.; Incorrectly classifying terminal nodes; they are typically losing states in normal play games.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minMovesToCaptureTheQueen(int a, int b, int c, int d, int e, int f) {
        // Directions for rook and bishop moves
        const int rookDirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        const int bishopDirs[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

        // Check if a position is within the chessboard
        auto isValid = [](int x, int y) {
            return x >= 1 && x <= 8 && y >= 1 && y <= 8;
        };

        // BFS setup
        struct State {
            int x, y, moves;
            bool isRook; // true for rook, false for bishop
        };

        std::queue<State> q;
        bool visited[9][9][2] = {}; // visited[x][y][isRook]

        // Start with both pieces
        q.push({a, b, 0, true});
        visited[a][b][1] = true;
        q.push({c, d, 0, false});
        visited[c][d][0] = true;

        while (!q.empty()) {
            State curr = q.front();
            q.pop();

            // Check if the current piece can capture the queen
            if (curr.x == e && curr.y == f) {
                return curr.moves;
            }

            // Generate next states
            const int (*dirs)[2] = curr.isRook ? rookDirs : bishopDirs;
            int dirCount = curr.isRook ? 4 : 4;

            for (int i = 0; i < dirCount; ++i) {
                int nx = curr.x;
                int ny = curr.y;

                while (true) {
                    nx += dirs[i][0];
                    ny += dirs[i][1];

                    if (!isValid(nx, ny)) break;

                    if (!visited[nx][ny][curr.isRook]) {
                        visited[nx][ny][curr.isRook] = true;
                        q.push({nx, ny, curr.moves + 1, curr.isRook});
                    }
                }
            }
        }

        return -1; // Should not reach here as per problem constraints          
    }
};
