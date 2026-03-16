# Source: https://leetcode.com/problems/minimum-moves-to-reach-target-with-rotations/   |   Difficulty: Hard
#
# Problem Description:
# In an n*n grid, there is a snake that spans 2 cells and starts moving from the top left corner at (0, 0) and (0, 1). The grid has empty cells represented by zeros and blocked cells represented by ones. The snake wants to reach the lower right corner at (n-1, n-2) and (n-1, n-1).
#
# In one move the snake can:
#
#
# 	Move one cell to the right if there are no blocked cells there. This move keeps the horizontal/vertical position of the snake as it is.
# 	Move down one cell if there are no blocked cells there. This move keeps the horizontal/vertical position of the snake as it is.
# 	Rotate clockwise if it's in a horizontal position and the two cells under it are both empty. In that case the snake moves from (r, c) and (r, c+1) to (r, c) and (r+1, c).
# 	
# 	Rotate counterclockwise if it's in a vertical position and the two cells to its right are both empty. In that case the snake moves from (r, c) and (r+1, c) to (r, c) and (r, c+1).
# 	
#
#
# Return the minimum number of moves to reach the target.
#
# If there is no way to reach the target, return -1.
#
# Example:
# Input: grid = [[0,0,0,0,0,1],
#                [1,1,0,0,1,0],
#                [0,0,0,0,1,1],
#                [0,0,1,0,1,0],
#                [0,1,1,0,0,0],
#                [0,1,1,0,0,0]]
# Output: 11
# Explanation:
# One possible solution is [right, right, rotate clockwise, right, down, down, down, down, rotate counterclockwise, right, down].
#
# Constraints:
# 2 <= n <= 100
# 	0 <= grid[i][j] <= 1
# 	It is guaranteed that the snake starts at empty cells.
#
# Helpful references (internal KB):
# - Undirected Graphs (graph, matrix, simulation)
#   • When to use: Use when modeling symmetric relationships between entities, analyzing graph properties like connectivity or degrees, or simulating processes on a network where connections are bidirectional.
#   • Idea: An undirected graph consists of a set of vertices and a set of edges, where each edge connects two vertices symmetrically. Basic operations often have a time complexity of O(V+E) or O(V^2) depending on representation.
#   • Invariants: For every edge (u, v) in the graph, the edge (v, u) also exists.; The sum of degrees of all vertices equals twice the number of edges.
#   • Tips: Choose adjacency list for sparse graphs, adjacency matrix for dense graphs.; Degrees of vertices are easily calculated from adjacency representations.
#   • Pitfalls: Forgetting to add both (u,v) and (v,u) when using an adjacency matrix or list.; Not handling disconnected components during full graph traversals.
# - Placing Bishops on a Chessboard (array, matrix, dp-2d, recursion)
#   • When to use: Use this approach for counting arrangements of non-attacking pieces on a grid, particularly when piece movement is restricted to specific geometric lines like diagonals. It is effective when constraints allow for independent processing of subsets of the grid.
#   • Idea: This method employs 2D dynamic programming to count the number of ways to place bishops on a chessboard such that no two bishops attack each other. It leverages the property that bishops only attack along diagonals of the same color, processing diagonals iteratively to build up solutions in polynomial time.
#   • Invariants: All bishops placed on diagonals with index less than `i` do not attack each other.; The count `D[i][j]` correctly reflects all valid placements of `j` bishops on diagonals up to `i` of the same color.
#   • Tips: Exploit problem-specific constraints, such as bishop movement along diagonals, to simplify state definitions.; Decompose the problem by processing diagonals of the same color independently to avoid complex interactions.
#   • Pitfalls: Incorrectly handling diagonal numbering or miscalculating the number of squares in a diagonal.; Off-by-one errors when determining the number of available squares for placing a bishop on a diagonal.
# - Finding the rank of a matrix (matrix, simulation, enumeration)
#   • When to use: Use when needing to determine the maximum number of linearly independent rows or columns in a matrix. It's also applicable for understanding the dimension of the vector space spanned by the matrix's rows or columns.
#   • Idea: Determines the rank of a matrix by transforming it into row echelon form using Gaussian elimination. The rank is the number of non-zero rows in the echelon form, with a time complexity of O(N^3).
#   • Invariants: The number of non-zero rows processed so far equals the current rank.; All elements below the pivot in the current column are zeroed out.
#   • Tips: Always choose the largest absolute value pivot for numerical stability.; Swap rows to bring a non-zero element to the pivot position.
#   • Pitfalls: Floating point precision issues can lead to incorrect zero checks.; Forgetting to increment rank only when a valid pivot is found.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minimumMoves(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        n = len(grid)
        target = (n-1, n-2, 0)  # (tail_row, tail_col, orientation)
        queue = collections.deque([(0, 0, 0, 0)])  # (tail_row, tail_col, orientation, moves)
        visited = set([(0, 0, 0)])

        while queue:
            tail_row, tail_col, orientation, moves = queue.popleft()
            if (tail_row, tail_col, orientation) == target:
                return moves

            # Generate possible moves
            if orientation == 0:  # horizontal
                # Move right
                if tail_col + 2 < n and grid[tail_row][tail_col + 2] == 0 and (tail_row, tail_col + 1, 0) not in visited:
                    visited.add((tail_row, tail_col + 1, 0))
                    queue.append((tail_row, tail_col + 1, 0, moves + 1))
                # Move down
                if tail_row + 1 < n and grid[tail_row + 1][tail_col] == 0 and grid[tail_row + 1][tail_col + 1] == 0 and (tail_row + 1, tail_col, 0) not in visited:
                    visited.add((tail_row + 1, tail_col, 0))
                    queue.append((tail_row + 1, tail_col, 0, moves + 1))
                # Rotate clockwise
                if tail_row + 1 < n and grid[tail_row + 1][tail_col] == 0 and grid[tail_row + 1][tail_col + 1] == 0 and (tail_row, tail_col, 1) not in visited:
                    visited.add((tail_row, tail_col, 1))
                    queue.append((tail_row, tail_col, 1, moves + 1))

            else:  # vertical
                # Move down
                if tail_row + 2 < n and grid[tail_row + 2][tail_col] == 0 and (tail_row + 1, tail_col, 1) not in visited:
                    visited.add((tail_row + 1, tail_col, 1))
                    queue.append((tail_row + 1, tail_col, 1, moves + 1))
                # Move right
                if tail_col + 1 < n and grid[tail_row][tail_col + 1] == 0 and grid[tail_row + 1][tail_col + 1] == 0 and (tail_row, tail_col + 1, 1) not in visited:
                    visited.add((tail_row, tail_col + 1, 1))
                    queue.append((tail_row, tail_col + 1, 1, moves + 1))
                # Rotate counterclockwise
                if tail_col + 1 < n and grid[tail_row][tail_col + 1] == 0 and grid[tail_row + 1][tail_col + 1] == 0 and (tail_row, tail_col, 0) not in visited:
                    visited.add((tail_row, tail_col, 0))
                    queue.append((tail_row, tail_col, 0, moves + 1))    
        return -1