// Source: https://leetcode.com/problems/sliding-puzzle/   |   Difficulty: Hard
//
// Problem Description:
// On an 2 x 3 board, there are five tiles labeled from 1 to 5, and an empty square represented by 0. A move consists of choosing 0 and a 4-directionally adjacent number and swapping it.
//
// The state of the board is solved if and only if the board is [[1,2,3],[4,5,0]].
//
// Given the puzzle board board, return the least number of moves required so that the state of the board is solved. If it is impossible for the state of the board to be solved, return -1.
//
// Example:
// Input: board = [[1,2,3],[4,0,5]]
// Output: 1
// Explanation: Swap the 0 and the 5 in one move.
//
// Constraints:
// board.length == 2
// 	board[i].length == 3
// 	0 <= board[i][j] <= 5
// 	Each value board[i][j] is unique.
//
// Helpful references (internal KB):
// - Breadth-first search (graph, queue, array, bfs)
//   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes level by level. It is also suitable for problems requiring traversal of all nodes at a specific distance from a source.
//   • Idea: Breadth-first search systematically explores a graph level by level, ensuring that all nodes at distance k are visited before any nodes at distance k+1. It finds the shortest path in terms of number of edges for unweighted graphs in O(V + E) time.
//   • Invariants: All nodes currently in the queue have been discovered and marked, but their adjacent nodes have not yet been fully explored.; For any node v marked as visited, distTo[v] stores the shortest path length from the source s to v.
//   • Tips: Use a queue to manage nodes to visit.; Mark nodes as visited to prevent cycles and redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect paths.; Not handling disconnected graphs correctly.
// - 15 Puzzle Game: Existence Of The Solution (matrix, number, counting)
//   • When to use: Use this to quickly determine if a given 15-puzzle board configuration can be solved, avoiding exhaustive search. It's applicable when the goal is to check solvability rather than finding the solution path.
//   • Idea: This algorithm determines the solvability of a 15-puzzle configuration by analyzing the parity of inversions in the tile permutation and the blank tile's row. It involves counting inversions, which typically takes O(N^2) time for N tiles, or O(N log N) with a more advanced counting method.
//   • Invariants: The permutation used for inversion counting always excludes the blank tile.; Each pair of tiles (i, j) with i < j is considered exactly once for inversion counting.
//   • Tips: Remember to exclude the blank tile (0) when forming the permutation for inversion counting.; For a 4x4 grid, the blank tile's row (from bottom, 1-indexed) is crucial for the parity check.
//   • Pitfalls: Incorrectly including the blank tile (0) in the inversion count.; Miscalculating the blank tile's row index (e.g., 0-indexed from top vs. 1-indexed from bottom).
// - Suffix Automaton (graph, string, simulation)
//   • When to use: When needing to efficiently represent all substrings of a given string and perform various string operations like counting distinct substrings, finding occurrences, or checking for specific patterns. It provides a compact and powerful data structure for complex string problems.
//   • Idea: A Suffix Automaton is a minimal deterministic finite automaton that recognizes all suffixes of a given string. It compactly represents all substrings of the string, with each state corresponding to an endpos-equivalence class, and can be constructed in linear time O(N).
//   • Invariants: Every state corresponds to a unique endpos-equivalence class of substrings.; For any state, all substrings ending at its endpos set are represented by that state or its ancestors via suffix links.
//   • Tips: Focus on the endpos definition for state equivalence.; Understand the incremental construction process.
//   • Pitfalls: The construction algorithm is non-trivial and prone to off-by-one errors.; Misinterpreting the role of suffix links vs. transition links.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int slidingPuzzle(int** board, int boardSize, int* boardColSize) {
    const char target[] = "123450";
    const int directions[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };
    typedef struct State {
        char board[7];
        int zeroPos;
        int moves;
        struct State* next;
    } State;

    unsigned long long hash(const char* board) {
        unsigned long long h = 0;
        for (int i = 0; i < 6; i++) {
            h = h * 31 + (board[i] - '0' + 1);
        }
        return h % 100003;
    }

    int visitedSize = 100003;
    char** visited = (char**)calloc(visitedSize, sizeof(char*));

    State* queueHead = (State*)malloc(sizeof(State));
    State* queueTail = queueHead;
    queueHead->next = NULL;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            queueHead->board[i * 3 + j] = board[i][j] + '0';
            if (board[i][j] == 0) {
                queueHead->zeroPos = i * 3 + j;
            }
        }
    }
    queueHead->moves = 0;

    unsigned long long h = hash(queueHead->board);
    visited[h] = (char*)malloc(7 * sizeof(char));
    strcpy(visited[h], queueHead->board);

    while (queueHead) {
        State* curr = queueHead;
        queueHead = queueHead->next;
        if (strcmp(curr->board, target) == 0) {
            int result = curr->moves;
            free(curr);
            for (int i = 0; i < visitedSize; i++) {
                if (visited[i]) free(visited[i]);
            }
            free(visited);
            while (queueHead) {
                State* temp = queueHead;
                queueHead = queueHead->next;
                free(temp);
            }
            return result;
        }

        int zx = curr->zeroPos / 3;
        int zy = curr->zeroPos % 3;

        for (int d = 0; d < 4; d++) {
            int nx = zx + directions[d][0];
            int ny = zy + directions[d][1];
            if (nx >= 0 && nx < 2 && ny >= 0 && ny < 3) {
                State* nextState = (State*)malloc(sizeof(State));
                strcpy(nextState->board, curr->board);
                int newZeroPos = nx * 3 + ny;
                // Swap zero with the adjacent number
                char temp = nextState->board[curr->zeroPos];
                nextState->board[curr->zeroPos] = nextState->board[newZeroPos];
                nextState->board[newZeroPos] = temp;
                nextState->zeroPos = newZeroPos;
                nextState->moves = curr->moves + 1;
                nextState->next = NULL;

                unsigned long long nh = hash(nextState->board);
                if (!visited[nh] || strcmp(visited[nh], nextState->board) != 0) {
                    visited[nh] = (char*)malloc(7 * sizeof(char));
                    strcpy(visited[nh], nextState->board);
                    queueTail->next = nextState;
                    queueTail = nextState;
                } else {
                    free(nextState);
                }
            }
        }
        free(curr);
    }
    for (int i = 0; i < visitedSize; i++) {
        if (visited[i]) free(visited[i]);
    }
    free(visited);
    return -1;
}
