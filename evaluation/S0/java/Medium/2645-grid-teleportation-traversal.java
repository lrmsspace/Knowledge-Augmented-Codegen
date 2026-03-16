// Source: https://leetcode.com/problems/grid-teleportation-traversal/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D character grid matrix of size m x n, represented as an array of strings, where matrix[i][j] represents the cell at the intersection of the ith row and jth column. Each cell is one of the following:
//
//
// 	'.' representing an empty cell.
// 	'#' representing an obstacle.
// 	An uppercase letter ('A'-'Z') representing a teleportation portal.
//
//
// You start at the top-left cell (0, 0), and your goal is to reach the bottom-right cell (m - 1, n - 1). You can move from the current cell to any adjacent cell (up, down, left, right) as long as the destination cell is within the grid bounds and is not an obstacle.
//
// If you step on a cell containing a portal letter and you haven't used that portal letter before, you may instantly teleport to any other cell in the grid with the same letter. This teleportation does not count as a move, but each portal letter can be used at most once during your journey.
//
// Return the minimum number of moves required to reach the bottom-right cell. If it is not possible to reach the destination, return -1.
//
// Example:
// Input: matrix = ["A..",".A.","..."]
//
// Output: 2
//
// Explanation:
//
//
//
//
// 	Before the first move, teleport from (0, 0) to (1, 1).
// 	In the first move, move from (1, 1) to (1, 2).
// 	In the second move, move from (1, 2) to (2, 2).
//
// Constraints:
// 1 <= m == matrix.length <= 103
// 	1 <= n == matrix[i].length <= 103
// 	matrix[i][j] is either '#', '.', or an uppercase English letter.
// 	matrix[0][0] is not an obstacle.
//

class Solution {
    public int minMoves(String[] matrix) {
        int m = matrix.length, n = matrix[0].length();
        Map<Character, List<int[]>> portals = new HashMap<>();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                char c = matrix[i].charAt(j);
                if (Character.isUpperCase(c)) {
                    portals.computeIfAbsent(c, k -> new ArrayList<>()).add(new int[]{i, j});
                }
            }
        }

        Queue<int[]> queue = new LinkedList<>();
        boolean[][] visited = new boolean[m][n];
        Set<Character> usedPortals = new HashSet<>();
        queue.offer(new int[]{0, 0, 0}); // {row, col, moves}
        visited[0][0] = true;

        int[][] directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        while (!queue.isEmpty()) {
            int[] curr = queue.poll();
            int row = curr[0], col = curr[1], moves = curr[2];

            if (row == m - 1 && col == n - 1) {
                return moves;
            }

            for (int[] dir : directions) {
                int newRow = row + dir[0], newCol = col + dir[1];
                if (newRow >= 0 && newRow < m && newCol >= 0 && newCol < n &&
                    matrix[newRow].charAt(newCol) != '#' && !visited[newRow][newCol]) {
                    visited[newRow][newCol] = true;
                    queue.offer(new int[]{newRow, newCol, moves + 1});
                }
            }

            char cellChar = matrix[row].charAt(col);
            if (Character.isUpperCase(cellChar) && !usedPortals.contains(cellChar)) {
                usedPortals.add(cellChar);
                for (int[] portalPos : portals.get(cellChar)) {
                    int pRow = portalPos[0], pCol = portalPos[1];
                    if (!visited[pRow][pCol]) {
                        visited[pRow][pCol] = true;
                        queue.offer(new int[]{pRow, pCol, moves});
                    }
                }
            }
        }

        return -1;          
    }
}
