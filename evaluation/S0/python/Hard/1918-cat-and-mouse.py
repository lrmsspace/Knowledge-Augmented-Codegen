# Source: https://leetcode.com/problems/cat-and-mouse/   |   Difficulty: Hard
#
# Problem Description:
# A game on an undirected graph is played by two players, Mouse and Cat, who alternate turns.
#
# The graph is given as follows: graph[a] is a list of all nodes b such that ab is an edge of the graph.
#
# The mouse starts at node 1 and goes first, the cat starts at node 2 and goes second, and there is a hole at node 0.
#
# During each player's turn, they must travel along one edge of the graph that meets where they are.  For example, if the Mouse is at node 1, it must travel to any node in graph[1].
#
# Additionally, it is not allowed for the Cat to travel to the Hole (node 0).
#
# Then, the game can end in three ways:
#
#
# 	If ever the Cat occupies the same node as the Mouse, the Cat wins.
# 	If ever the Mouse reaches the Hole, the Mouse wins.
# 	If ever a position is repeated (i.e., the players are in the same position as a previous turn, and it is the same player's turn to move), the game is a draw.
#
#
# Given a graph, and assuming both players play optimally, return
#
#
# 	1 if the mouse wins the game,
# 	2 if the cat wins the game, or
# 	0 if the game is a draw.
#
# Example:
# Input: graph = [[2,5],[3],[0,4,5],[1,4,5],[2,3],[0,2,3]]
# Output: 0
#
# Constraints:
# 3 <= graph.length <= 50
# 	1 <= graph[i].length < graph.length
# 	0 <= graph[i][j] < graph.length
# 	graph[i][j] != i
# 	graph[i] is unique.
# 	The mouse and the cat can always move.
#

class Solution(object):
    def catMouseGame(self, graph):
        """
        :type graph: List[List[int]]
        :rtype: int
        """
        n = len(graph)
        DRAW, MOUSE, CAT = 0, 1, 2

        color = [[[DRAW] * 2 for _ in range(n)] for _ in range(n)]
        degree = [[[0] * 2 for _ in range(n)] for _ in range(n)]

        for m in range(n):
            for c in range(n):
                degree[m][c][0] = len(graph[m])
                degree[m][c][1] = len(graph[c]) - (0 in graph[c])

        queue = collections.deque()

        for i in range(1, n):
            color[0][i][0] = MOUSE
            queue.append((0, i, 0, MOUSE))
            color[i][i][1] = CAT
            queue.append((i, i, 1, CAT))

        while queue:
            m, c, t, ct = queue.popleft()
            for pm in graph[m] if t == 1 else [m]:
                for pc in graph[c] if t == 0 else [c]:
                    if pc == 0:
                        continue
                    pt = 1 - t
                    if color[pm][pc][pt] == DRAW:
                        if ct == (MOUSE if t == 0 else CAT):
                            color[pm][pc][pt] = ct
                            queue.append((pm, pc, pt, ct))
                        else:
                            degree[pm][pc][pt] -= 1
                            if degree[pm][pc][pt] == 0:
                                otc = CAT if ct == MOUSE else MOUSE
                                color[pm][pc][pt] = otc
                                queue.append((pm, pc, pt, otc))

        return color[1][2][0]