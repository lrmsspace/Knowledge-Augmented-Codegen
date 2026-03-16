// Source: https://leetcode.com/problems/minimum-moves-to-move-a-box-to-their-target-location/   |   Difficulty: Hard
//
// Problem Description:
// A storekeeper is a game in which the player pushes boxes around in a warehouse trying to get them to target locations.
//
// The game is represented by an m x n grid of characters grid where each element is a wall, floor, or box.
//
// Your task is to move the box 'B' to the target position 'T' under the following rules:
//
//
// 	The character 'S' represents the player. The player can move up, down, left, right in grid if it is a floor (empty cell).
// 	The character '.' represents the floor which means a free cell to walk.
// 	The character '#' represents the wall which means an obstacle (impossible to walk there).
// 	There is only one box 'B' and one target cell 'T' in the grid.
// 	The box can be moved to an adjacent free cell by standing next to the box and then moving in the direction of the box. This is a push.
// 	The player cannot walk through the box.
//
//
// Return the minimum number of pushes to move the box to the target. If there is no way to reach the target, return -1.
//
// Example:
// Input: grid = [["#","#","#","#","#","#"],
//                ["#","T","#","#","#","#"],
//                ["#",".",".","B",".","#"],
//                ["#",".","#","#",".","#"],
//                ["#",".",".",".","S","#"],
//                ["#","#","#","#","#","#"]]
// Output: 3
// Explanation: We return only the number of times the box is pushed.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 20
// 	grid contains only characters '.', '#', 'S', 'T', or 'B'.
// 	There is only one character 'S', 'B', and 'T' in the grid.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int minPushBox(char[][] grid) {
        int m = grid.length, n = grid[0].length;
        int[] box = new int[2], target = new int[2], player = new int[2];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 'B') {
                    box[0] = i;
                    box[1] = j;
                } else if (grid[i][j] == 'T') {
                    target[0] = i;
                    target[1] = j;
                } else if (grid[i][j] == 'S') {
                    player[0] = i;
                    player[1] = j;
                }
            }
        }

        // BFS to find the minimum pushes
        Queue<int[]> queue = new LinkedList<>();
        Set<String> visited = new HashSet<>();
        queue.offer(new int[]{box[0], box[1], player[0], player[1], 0}); // box_x, box_y, player_x, player_y, pushes
        visited.add(box[0] + "," + box[1] + "," + player[0] + "," + player[1]);

        int[][] directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        while (!queue.isEmpty()) {
            int[] current = queue.poll();
            int boxX = current[0], boxY = current[1], playerX = current[2], playerY = current[3], pushes = current[4];

            if (boxX == target[0] && boxY == target[1]) {
                return pushes;
            }

            for (int[] dir : directions) {
                int newBoxX = boxX + dir[0];
                int newBoxY = boxY + dir[1];
                int newPlayerX = boxX - dir[0];
                int newPlayerY = boxY - dir[1];

                if (isValid(grid, newBoxX, newBoxY) && isValid(grid, newPlayerX, newPlayerY) &&
                        canReach(grid, playerX, playerY, newPlayerX, newPlayerY, boxX, boxY)) {
                    String state = newBoxX + "," + newBoxY + "," + boxX + "," + boxY;
                    if (!visited.contains(state)) {
                        visited.add(state);
                        queue.offer(new int[]{newBoxX, newBoxY, boxX, boxY, pushes + 1});
                    }
                }
            }
        }
        return -1;
    }
}
