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

/**
 * @param {number[][]} graph
 * @return {number}
 */
var catMouseGame = function(graph) {
    const n = graph.length;
    const MOUSE_WIN = 1;
    const CAT_WIN = 2;
    const DRAW = 0;
    const dp = Array.from({ length: n }, () => new Array(n).fill(DRAW));

    for (let mouse = 0; mouse < n; mouse++) {
        for (let cat = 0; cat < n; cat++) {
            if (mouse === 0) {
                dp[mouse][cat] = MOUSE_WIN;
            } else if (mouse === cat) {
                dp[mouse][cat] = CAT_WIN;
            }
        }
    }
    let changed = true;
    while (changed) {
        changed = false;
        for (let mouse = 0; mouse < n; mouse++) {
            for (let cat = 0; cat < n; cat++) {
                if (dp[mouse][cat] !== DRAW) continue;
                for (const nextMouse of graph[mouse]) {
                    if (dp[nextMouse][cat] === MOUSE_WIN) {
                        dp[mouse][cat] = MOUSE_WIN;
                        changed = true;
                        break;
                    }
                }
                if (dp[mouse][cat] !== DRAW) continue;
                let catCanWin = false;
                for (const nextCat of graph[cat]) {
                    if (nextCat === 0) continue;
                    if (dp[mouse][nextCat] === CAT_WIN) {
                        catCanWin = true;
                        break;
                    }
                }
                if (catCanWin) {
                    dp[mouse][cat] = CAT_WIN;
                    changed = true;
                }
            }
        }
    }
    return dp[1][2];    
};
