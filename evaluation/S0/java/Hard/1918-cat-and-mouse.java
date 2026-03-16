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

class Solution {
    public int catMouseGame(int[][] graph) {
        int n = graph.length;
        int[][][] dp = new int[n][n][2]; // 0: mouse turn, 1: cat turn

        for (int m = 0; m < n; m++) {
            for (int c = 0; c < n; c++) {
                if (m == 0) {
                    dp[m][c][0] = 1;
                    dp[m][c][1] = 1;
                } else if (m == c) {
                    dp[m][c][0] = 2;
                    dp[m][c][1] = 2;
                }
            }
        }

        boolean changed;
        do {
            changed = false;
            for (int m = 0; m < n; m++) {
                for (int c = 0; c < n; c++) {
                    for (int turn = 0; turn < 2; turn++) {
                        if (dp[m][c][turn] != 0) continue;

                        if (turn == 0) { // Mouse's turn
                            boolean mouseCanWin = false;
                            boolean allCatWin = true;

                            for (int nextM : graph[m]) {
                                if (dp[nextM][c][1] == 1) {
                                    mouseCanWin = true;
                                    break;
                                }
                                if (dp[nextM][c][1] != 2) {
                                    allCatWin = false;
                                }
                            }

                            if (mouseCanWin) {
                                dp[m][c][turn] = 1;
                                changed = true;
                            } else if (allCatWin) {
                                dp[m][c][turn] = 2;
                                changed = true;
                            }
                        } else { // Cat's turn
                            boolean catCanWin = false;
                            boolean allMouseWin = true;

                            for (int nextC : graph[c]) {
                                if (nextC == 0) continue; // Cat cannot go to hole
                                if (dp[m][nextC][0] == 2) {
                                    catCanWin = true;
                                    break;
                                }
                                if (dp[m][nextC][0] != 1) {
                                    allMouseWin = false;
                                }
                            }

                            if (catCanWin) {
                                dp[m][c][turn] = 2;
                                changed = true;         
                            } else if (allMouseWin) {
                                dp[m][c][turn] = 1;
                                changed = true;
                            }
                        }
                    }
                }
            }
        } while (changed);

        return dp[1][2][0];
    }
}