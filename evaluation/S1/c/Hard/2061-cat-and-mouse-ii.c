// Source: https://leetcode.com/problems/cat-and-mouse-ii/   |   Difficulty: Hard
//
// Problem Description:
// A game is played by a cat and a mouse named Cat and Mouse.
//
// The environment is represented by a grid of size rows x cols, where each element is a wall, floor, player (Cat, Mouse), or food.
//
//
// 	Players are represented by the characters 'C'(Cat),'M'(Mouse).
// 	Floors are represented by the character '.' and can be walked on.
// 	Walls are represented by the character '#' and cannot be walked on.
// 	Food is represented by the character 'F' and can be walked on.
// 	There is only one of each character 'C', 'M', and 'F' in grid.
//
//
// Mouse and Cat play according to the following rules:
//
//
// 	Mouse moves first, then they take turns to move.
// 	During each turn, Cat and Mouse can jump in one of the four directions (left, right, up, down). They cannot jump over the wall nor outside of the grid.
// 	catJump, mouseJump are the maximum lengths Cat and Mouse can jump at a time, respectively. Cat and Mouse can jump less than the maximum length.
// 	Staying in the same position is allowed.
// 	Mouse can jump over Cat.
//
//
// The game can end in 4 ways:
//
//
// 	If Cat occupies the same position as Mouse, Cat wins.
// 	If Cat reaches the food first, Cat wins.
// 	If Mouse reaches the food first, Mouse wins.
// 	If Mouse cannot get to the food within 1000 turns, Cat wins.
//
//
// Given a rows x cols matrix grid and two integers catJump and mouseJump, return true if Mouse can win the game if both Cat and Mouse play optimally, otherwise return false.
//
// Example:
// Input: grid = ["####F","#C...","M...."], catJump = 1, mouseJump = 2
// Output: true
// Explanation: Cat cannot catch Mouse on its turn nor can it get the food before Mouse.
//
// Constraints:
// rows == grid.length
// 	cols = grid[i].length
// 	1 <= rows, cols <= 8
// 	grid[i][j] consist only of characters 'C', 'M', 'F', '.', and '#'.
// 	There is only one of each character 'C', 'M', and 'F' in grid.
// 	1 <= catJump, mouseJump <= 8
//
// Helpful references (internal KB):
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
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool canMouseWin(char** grid, int gridSize, int catJump, int mouseJump) {
    int cols = strlen(grid[0]);
    int rows = gridSize;
    
    // Find initial positions and food position
    int catX = 0, catY = 0;
    int mouseX = 0, mouseY = 0;
    int foodX = 0, foodY = 0;
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 'C') {
                catX = i;
                catY = j;
            } else if (grid[i][j] == 'M') {
                mouseX = i;
                mouseY = j;
            } else if (grid[i][j] == 'F') {
                foodX = i;
                foodY = j;
            }
        }
    }
    
    // State: [catX][catY][mouseX][mouseY][turn]
    // 0 = unknown, 1 = mouse wins, 2 = cat wins
    int state[8][8][8][8][2];
    memset(state, 0, sizeof(state));
    
    // Queue for BFS: catX, catY, mouseX, mouseY, turn, result
    int queue[10000][6];
    int queueSize = 0;
    
    // Initialize terminal states
    for (int cx = 0; cx < rows; cx++) {
        for (int cy = 0; cy < cols; cy++) {
            for (int mx = 0; mx < rows; mx++) {
                for (int my = 0; my < cols; my++) {
                    // Cat caught mouse
                    if (cx == mx && cy == my) {
                        state[cx][cy][mx][my][0] = 2;
                        state[cx][cy][mx][my][1] = 2;
                    }
                    // Cat reached food
                    if (cx == foodX && cy == foodY) {
                        state[cx][cy][mx][my][0] = 2;
                        state[cx][cy][mx][my][1] = 2;
                    }
                    // Mouse reached food
                    if (mx == foodX && my == foodY) {
                        state[cx][cy][mx][my][0] = 1;
                        state[cx][cy][mx][my][1] = 1;
                    }
                }
            }
        }
    }
    
    // Add terminal states to queue
    for (int cx = 0; cx < rows; cx++) {
        for (int cy = 0; cy < cols; cy++) {
            for (int mx = 0; mx < rows; mx++) {
                for (int my = 0; my < cols; my++) {
                    if (state[cx][cy][mx][my][0] != 0) {
                        queue[queueSize][0] = cx;
                        queue[queueSize][1] = cy;
                        queue[queueSize][2] = mx;
                        queue[queueSize][3] = my;
                        queue[queueSize][4] = 0;
                        queue[queueSize][5] = state[cx][cy][mx][my][0];
                        queueSize++;
                        if (state[cx][cy][mx][my][0] != state[cx][cy][mx][my][1]) {
                            queue[queueSize][0] = cx;
                            queue[queueSize][1] = cy;
                            queue[queueSize][2] = mx;
                            queue[queueSize][3] = my;
                            queue[queueSize][4] = 1;
                            queue[queueSize][5] = state[cx][cy][mx][my][1];
                            queueSize++;
                        }
                    }
                }
            }
        }
    }
    
    // In-degree tracking
    int inDegree[8][8][8][8][2];
    memset(inDegree, 0, sizeof(inDegree));
    
    for (int cx = 0; cx < rows; cx++) {
        for (int cy = 0; cy < cols; cy++) {
            for (int mx = 0; mx < rows; mx++) {
                for (int my = 0; my < cols; my++) {
                    if (grid[cx][cy] == '#' || grid[mx][my] == '#') continue;
                    
                    // Count predecessors for turn 0 (mouse moves next)
                    int dx[] = {-1, 1, 0, 0};
                    int dy[] = {0, 0, -1, 1};
                    
                    // Previous cat positions (cat moved last)
                    for (int dir = 0; dir < 4; dir++) {
                        for (int jump = 1; jump <= catJump; jump++) {
                            int pcx = cx + dx[dir] * jump;
                            int pcy = cy + dy[dir] * jump;
                            if (pcx < 0 || pcx >= rows || pcy < 0 || pcy >= cols || grid[pcx][pcy] == '#') break;
                            inDegree[cx][cy][mx][my][0]++;
                        }
                    }
                    inDegree[cx][cy][mx][my][0]++; // Cat can stay
                    
                    // Count predecessors for turn 1 (cat moves next)
                    for (int dir = 0; dir < 4; dir++) {
                        for (int jump = 1; jump <= mouseJump; jump++) {
                            int pmx = mx + dx[dir] * jump;
                            int pmy = my + dy[dir] * jump;
                            if (pmx < 0 || pmx >= rows || pmy < 0 || pmy >= cols || grid[pmx][pmy] == '#') break;
                            inDegree[cx][cy][mx][my][1]++;
                        }
                    }
                    inDegree[cx][cy][mx][my][1]++; // Mouse can stay
                }
            }
        }
    }
    
    // BFS to propagate results
    for (int i = 0; i < queueSize; i++) {
        int cx = queue[i][0];
        int cy = queue[i][1];
        int mx = queue[i][2];
        int my = queue[i][3];
        int turn = queue[i][4];
        int result = queue[i][5];
        
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};
        
        if (turn == 0) {
            // Previous turn was cat's turn
            for (int dir = 0; dir < 4; dir++) {
                for (int jump = 1; jump <= catJump; jump++) {
                    int pcx = cx + dx[dir] * jump;
                    int pcy = cy + dy[dir] * jump;
                    if (pcx < 0 || pcx >= rows || pcy < 0 || pcy >= cols || grid[pcx][pcy] == '#') break;
                    
                    if (state[pcx][pcy][mx][my][1] == 0) {
                        if (result == 2) { // Cat wins
                            state[pcx][pcy][mx][my][1] = 2;
                            queue[queueSize][0] = pcx;
                            queue[queueSize][1] = pcy;
                            queue[queueSize][2] = mx;
                            queue[queueSize][3] = my;
                            queue[queueSize][4] = 1;
                            queue[queueSize][5] = 2;
                            queueSize++;
                        } else {
                            inDegree[pcx][pcy][mx][my][1]--;
                            if (inDegree[pcx][pcy][mx][my][1] == 0) {
                                state[pcx][pcy][mx][my][1] = 1;
                                queue[queueSize][0] = pcx;
                                queue[queueSize][1] = pcy;
                                queue[queueSize][2] = mx;
                                queue[queueSize][3] = my;
                                queue[queueSize][4] = 1;
                                queue[queueSize][5] = 1;
                                queueSize++;
                            }
                        }
                    }
                }
            }
            
            // Cat stays
            if (state[cx][cy][mx][my][1] == 0) {
                if (result == 2) {
                    state[cx][cy][mx][my][1] = 2;
                    queue[queueSize][0] = cx;
                    queue[queueSize][1] = cy;
                    queue[queueSize][2] = mx;
                    queue[queueSize][3] = my;
                    queue[queueSize][4] = 1;
                    queue[queueSize][5] = 2;
                    queueSize++;
                } else {
                    inDegree[cx][cy][mx][my][1]--;
                    if (inDegree[cx][cy][mx][my][1] == 0) {
                        state[cx][cy][mx][my][1] = 1;
                        queue[queueSize][0] = cx;
                        queue[queueSize][1] = cy;
                        queue[queueSize][2] = mx;
                        queue[queueSize][3] = my;
                        queue[queueSize][4] = 1;
                        queue[queueSize][5] = 1;
                        queueSize++;
                    }
                }
            }
        } else {
            // Previous turn was mouse's turn
            for (int dir = 0; dir < 4; dir++) {
                for (int jump = 1; jump <= mouseJump; jump++) {
                    int pmx = mx + dx[dir] * jump;
                    int pmy = my + dy[dir] * jump;
                    if (pmx < 0 || pmx >= rows || pmy < 0 || pmy >= cols || grid[pmx][pmy] == '#') break;
                    
                    if (state[cx][cy][pmx][pmy][0] == 0) {
                        if (result == 1) { // Mouse wins
                            state[cx][cy][pmx][pmy][0] = 1;
                            queue[queueSize][0] = cx;
                            queue[queueSize][1] = cy;
                            queue[queueSize][2] = pmx;
                            queue[queueSize][3] = pmy;
                            queue[queueSize][4] = 0;
                            queue[queueSize][5] = 1;
                            queueSize++;
                        } else {
                            inDegree[cx][cy][pmx][pmy][0]--;
                            if (inDegree[cx][cy][pmx][pmy][0] == 0) {
                                state[cx][cy][pmx][pmy][0] = 2;
                                queue[queueSize][0] = cx;
                                queue[queueSize][1] = cy;
                                queue[queueSize][2] = pmx;
                                queue[queueSize][3] = pmy;
                                queue[queueSize][4] = 0;
                                queue[queueSize][5] = 2;
                                queueSize++;
                            }
                        }
                    }
                }
            }
            
            // Mouse stays
            if (state[cx][cy][mx][my][0] == 0) {
                if (result == 1) {
                    state[cx][cy][mx][my][0] = 1;
                    queue[queueSize][0] = cx;
                    queue[queueSize][1] = cy;
                    queue[queueSize][2] = mx;
                    queue[queueSize][3] = my;
                    queue[queueSize][4] = 0;
                    queue[queueSize][5] = 1;
                    queueSize++;
                } else {
                    inDegree[cx][cy][mx][my][0]--;
                    if (inDegree[cx][cy][mx][my][0] == 0) {
                        state[cx][cy][mx][my][0] = 2;
                        queue[queueSize][0] = cx;
                        queue[queueSize][1] = cy;
                        queue[queueSize][2] = mx;
                        queue[queueSize][3] = my;
                        queue[queueSize][4] = 0;
                        queue[queueSize][5] = 2;
                        queueSize++;
                    }
                }
            }
        }
    }
    
    return state[catX][catY][mouseX][mouseY][0] == 1;
}
