// Source: https://leetcode.com/problems/minimum-moves-to-reach-target-with-rotations/   |   Difficulty: Hard
//
// Problem Description:
// In an n*n grid, there is a snake that spans 2 cells and starts moving from the top left corner at (0, 0) and (0, 1). The grid has empty cells represented by zeros and blocked cells represented by ones. The snake wants to reach the lower right corner at (n-1, n-2) and (n-1, n-1).
//
// In one move the snake can:
//
//
// 	Move one cell to the right if there are no blocked cells there. This move keeps the horizontal/vertical position of the snake as it is.
// 	Move down one cell if there are no blocked cells there. This move keeps the horizontal/vertical position of the snake as it is.
// 	Rotate clockwise if it's in a horizontal position and the two cells under it are both empty. In that case the snake moves from (r, c) and (r, c+1) to (r, c) and (r+1, c).
// 	
// 	Rotate counterclockwise if it's in a vertical position and the two cells to its right are both empty. In that case the snake moves from (r, c) and (r+1, c) to (r, c) and (r, c+1).
// 	
//
//
// Return the minimum number of moves to reach the target.
//
// If there is no way to reach the target, return -1.
//
// Example:
// Input: grid = [[0,0,0,0,0,1],
//                [1,1,0,0,1,0],
//                [0,0,0,0,1,1],
//                [0,0,1,0,1,0],
//                [0,1,1,0,0,0],
//                [0,1,1,0,0,0]]
// Output: 11
// Explanation:
// One possible solution is [right, right, rotate clockwise, right, down, down, down, down, rotate counterclockwise, right, down].
//
// Constraints:
// 2 <= n <= 100
// 	0 <= grid[i][j] <= 1
// 	It is guaranteed that the snake starts at empty cells.
//

class Solution {
    public int minimumMoves(int[][] grid) {
        int n = grid.length;
        boolean[][][] visited = new boolean[n][n][2];
        Queue<int[]> queue = new LinkedList<>();
        queue.offer(new int[]{0, 0, 0}); // row, col, orientation (0: horizontal, 1: vertical)
        visited[0][0][0] = true;
        int moves = 0;

        while (!queue.isEmpty()) {
            int size = queue.size();
            for (int i = 0; i < size; i++) {
                int[] curr = queue.poll();
                int r = curr[0], c = curr[1], orientation = curr[2];

                // Check if we reached the target
                if (r == n - 1 && c == n - 2 && orientation == 0) {
                    return moves;
                }

                // Move right
                if (orientation == 0 && c + 2 < n && grid[r][c + 2] == 0 && !visited[r][c + 1][0]) {
                    visited[r][c + 1][0] = true;
                    queue.offer(new int[]{r, c + 1, 0});
                } else if (orientation == 1 && c + 1 < n && grid[r][c + 1] == 0 && grid[r + 1][c + 1] == 0 && !visited[r][c + 1][1]) {
                    visited[r][c + 1][1] = true;
                    queue.offer(new int[]{r, c + 1, 1});
                }

                // Move down
                if (orientation == 0 && r + 1 < n && grid[r + 1][c] == 0 && grid[r + 1][c + 1] == 0 && !visited[r + 1][c][0]) {
                    visited[r + 1][c][0] = true;
                    queue.offer(new int[]{r + 1, c, 0});
                } else if (orientation == 1 && r + 2 < n && grid[r + 2][c] == 0 && !visited[r + 1][c][1]) {
                    visited[r + 1][c][1] = true;
                    queue.offer(new int[]{r + 1, c, 1});          
                }
                // Rotate clockwise
                if (orientation == 0 && r + 1 < n && grid[r + 1][c] == 0 && grid[r + 1][c + 1] == 0 && !visited[r][c][1]) {
                    visited[r][c][1] = true;
                    queue.offer(new int[]{r, c, 1});
                }
                // Rotate counterclockwise
                if (orientation == 1 && c + 1 < n && grid[r][c + 1] == 0 && grid[r + 1][c + 1] == 0 && !visited[r][c][0]) {
                    visited[r][c][0] = true;
                    queue.offer(new int[]{r, c, 0});
                }
                          
            }
            moves++;
        }
        return -1;
    }
}
