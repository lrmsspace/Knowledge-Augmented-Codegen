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

bool canMouseWin(char** grid, int gridSize, int catJump, int mouseJump) {
    int rows = gridSize;
    int cols = strlen(grid[0]);
    int maxTurns = 1000;
    int directions[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

    typedef struct {
        int mouseRow, mouseCol, catRow, catCol, turn;
    } State;

    int encodeState(int mr, int mc, int cr, int cc, int t) {
        return (((((mr * cols + mc) * rows + cr) * cols + cc) * (maxTurns + 1)) + t);
    }

    #define MAX_STATES (rows * cols * rows * cols * (maxTurns + 1))
    char dp[MAX_STATES];
    memset(dp, 0, sizeof(dp));

    int mouseRow, mouseCol, catRow, catCol, foodRow, foodCol;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c] == 'M') {
                mouseRow = r; mouseCol = c;
            } else if (grid[r][c] == 'C') {
                catRow = r; catCol = c;
            } else if (grid[r][c] == 'F') {
                foodRow = r; foodCol = c;
            }
        }
    }

    State queue[MAX_STATES];
    int front = 0, back = 0;

    for (int turn = 0; turn <= maxTurns; ++turn) {
        for (int mr = 0; mr < rows; ++mr) {
            for (int mc = 0; mc < cols; ++mc) {
                for (int cr = 0; cr < rows; ++cr) {
                    for (int cc = 0; cc < cols; ++cc) {
                        if (grid[mr][mc] == '#' || grid[cr][cc] == '#') continue;

                        int stateIdx = encodeState(mr, mc, cr, cc, turn);
                        if (mr == cr && mc == cc) {
                            dp[stateIdx] = 2; // Cat wins
                            queue[back++] = (State){mr, mc, cr, cc, turn};
                        } else if (cr == foodRow && cc == foodCol) {
                            dp[stateIdx] = 2; // Cat wins
                            queue[back++] = (State){mr, mc, cr, cc, turn};
                        } else if (mr == foodRow && mc == foodCol) {
                            dp[stateIdx] = 1; // Mouse wins
                            queue[back++] = (State){mr, mc, cr, cc, turn};
                        } else if (turn == maxTurns) {
                            dp[stateIdx] = 2; // Cat wins
                            queue[back++] = (State){mr, mc, cr, cc, turn};
                        }
                    }
                }
            }
        }
    }

    while (front < back) {
        State curr = queue[front++];
        int currIdx = encodeState(curr.mouseRow, curr.mouseCol, curr.catRow, curr.catCol, curr.turn);
        char winner = dp[currIdx];

        if (curr.turn == 0) continue;

        int prevTurn = curr.turn - 1;
        if (curr.turn % 2 == 0) { // Cat's turn
            for (int d = 0; d < 4; ++d) {
                for (int jump = 0; jump <= catJump; ++jump) {
                    int nr = curr.catRow + directions[d][0] * jump;
                    int nc = curr.catCol + directions[d][1] * jump;
                    if (nr < 0 || nr >= rows || nc < 0 || nc >= cols || grid[nr][nc] == '#') break;

                    int prevIdx = encodeState(curr.mouseRow, curr.mouseCol, nr, nc, prevTurn);
                    if (dp[prevIdx] == 0) {
                        if (winner == 2) {
                            dp[prevIdx] = 2;
                            queue[back++] = (State){curr.mouseRow, curr.mouseCol, nr, nc, prevTurn};
                        } else {
                            int allCatWins = 1;
                            for (int dd = 0; dd < 4; ++dd) {
                                for (int mjump = 0; mjump <= mouseJump; ++mjump) {
                                    int mr = curr.mouseRow + directions[dd][0] * mjump;
                                    int mc = curr.mouseCol + directions[dd][1] * mjump;
                                    if (mr < 0 || mr >= rows || mc < 0 || mc >= cols || grid[mr][mc] == '#') break;

                                    int nextIdx = encodeState(mr, mc, nr, nc, curr.turn);
                                    if (dp[nextIdx] != 2) {
                                        allCatWins = 0;
                                        break;
                                    }
                                }
                                if (!allCatWins) break;
                            }
                            if (allCatWins) {
                                dp[prevIdx] = 2;
                                queue[back++] = (State){curr.mouseRow, curr.mouseCol, nr, nc, prevTurn};
                            }
                        }
                    }
                }
            }
        } else
        { // Mouse's turn
            for (int d = 0; d < 4; ++d) {
                for (int jump = 0; jump <= mouseJump; ++jump) {
                    int nr = curr.mouseRow + directions[d][0] * jump;
                    int nc = curr.mouseCol + directions[d][1] * jump;
                    if (nr < 0 || nr >= rows || nc < 0 || nc >= cols || grid[nr][nc] == '#') break;

                    int prevIdx = encodeState(nr, nc, curr.catRow, curr.catCol, prevTurn);
                    if (dp[prevIdx] == 0) {
                        if (winner == 1) {
                            dp[prevIdx] = 1;
                            queue[back++] = (State){nr, nc, curr.catRow, curr.catCol, prevTurn};
                        } else {
                            int allMouseWins = 1;
                            for (int dd = 0; dd < 4; ++dd) {
                                for (int cjump = 0; cjump <= catJump; ++cjump) {
                                    int cr = curr.catRow + directions[dd][0] * cjump;
                                    int cc = curr.catCol + directions[dd][1] * cjump;
                                    if (cr < 0 || cr >= rows || cc < 0 || cc >= cols || grid[cr][cc] == '#') break;

                                    int nextIdx = encodeState(nr, nc, cr, cc, curr.turn);
                                    if (dp[nextIdx] != 1) {
                                        allMouseWins = 0;
                                        break;
                                    }
                                }
                                if (!allMouseWins) break;
                            }
                            if (allMouseWins) {
                                dp[prevIdx] = 1;
                                queue[back++] = (State){nr, nc, curr.catRow, curr.catCol, prevTurn};
                            }
                        }
                    }
                }
            }
        }

        
}
