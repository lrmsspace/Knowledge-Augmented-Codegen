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

int catMouseGame(int** graph, int graphSize, int* graphColSize) {
    #define MOUSE_WIN 1
    #define CAT_WIN 2
    #define DRAW 0
    #define MAX_N 50
    #define MAX_STATES (MAX_N * MAX_N * 2)

    int color[MAX_STATES];
    int degree[MAX_STATES];

    // Initialize degrees
    for (int m = 0; m < graphSize; ++m) {
        for (int c = 0; c < graphSize; ++c) {
            for (int t = 0; t < 2; ++t) {
                int state = (m * graphSize + c) * 2 + t;
                if (t == 0) { // Mouse's turn
                    degree[state] = graphColSize[m];
                } else { // Cat's turn
                    degree[state] = graphColSize[c];
                    for (int i = 0; i < graphColSize[c]; ++i) {
                        if (graph[c][i] == 0) {
                            degree[state]--;
                            break;
                        }
                    }
                }
            }
        }
    }

    // Queue for BFS
    int queue[MAX_STATES];
    int front = 0, rear = 0;

    // Initialize terminal states
    for (int m = 0; m < graphSize; ++m) {
        for (int c = 0; c < graphSize; ++c) {
            for (int t = 0; t < 2; ++t) {
                int state = (m * graphSize + c) * 2 + t;
                if (m == 0) { // Mouse at hole
                    color[state] = MOUSE_WIN;
                    queue[rear++] = state;
                } else if (m == c) { // Cat catches mouse
                    color[state] = CAT_WIN;
                    queue[rear++] = state;
                }
            }
        }
    }

    // BFS to propagate results
    while (front < rear) {
        int state = queue[front++];
        int m = (state / 2) / graphSize;
        int c = (state / 2) % graphSize;
        int t = state % 2;

        for (int pm = 0; pm < graphSize; ++pm) {
            for (int pc = 0; pc < graphSize; ++pc) {
                for (int pt = 0; pt < 2; ++pt) {
                    int prevState = (pm * graphSize + pc) * 2 + pt;
                    if (t == 0 && pt == 1) { // Current is Mouse's turn, previous was Cat's turn
                        for (int i = 0; i < graphColSize[pc]; ++i) {
                            if (graph[pc][i] == m) {
                                if (color[prevState] == 0) {
                                    color[prevState] = CAT_WIN;
                                    queue[rear++] = prevState;
                                }
                            }
                        }
                    } else if (t == 1 && pt == 0) { // Current is Cat's turn, previous was Mouse's turn
                        for (int i = 0; i < graphColSize[pm]; ++i) {
                            if (graph[pm][i] == c) {
                                if (color[prevState] == 0) {
                                    color[prevState] = MOUSE_WIN;
                                    queue[rear++] = prevState;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    int startState = (1 * graphSize + 2) * 2 + 0; // Mouse at 1, Cat at 2, Mouse's turn
    return color[startState];
}
