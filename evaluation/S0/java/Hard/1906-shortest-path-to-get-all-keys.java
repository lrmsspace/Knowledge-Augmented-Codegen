// Source: https://leetcode.com/problems/shortest-path-to-get-all-keys/   |   Difficulty: Hard
//
// Problem Description:
// You are given an m x n grid grid where:
//
//
// 	'.' is an empty cell.
// 	'#' is a wall.
// 	'@' is the starting point.
// 	Lowercase letters represent keys.
// 	Uppercase letters represent locks.
//
//
// You start at the starting point and one move consists of walking one space in one of the four cardinal directions. You cannot walk outside the grid, or walk into a wall.
//
// If you walk over a key, you can pick it up and you cannot walk over a lock unless you have its corresponding key.
//
// For some 1 <= k <= 6, there is exactly one lowercase and one uppercase letter of the first k letters of the English alphabet in the grid. This means that there is exactly one key for each lock, and one lock for each key; and also that the letters used to represent the keys and locks were chosen in the same order as the English alphabet.
//
// Return the lowest number of moves to acquire all keys. If it is impossible, return -1.
//
// Example:
// Input: grid = ["@.a..","###.#","b.A.B"]
// Output: 8
// Explanation: Note that the goal is to obtain all the keys not to open all the locks.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 30
// 	grid[i][j] is either an English letter, '.', '#', or '@'. 
// 	There is exactly one '@' in the grid.
// 	The number of keys in the grid is in the range [1, 6].
// 	Each key in the grid is unique.
// 	Each key in the grid has a matching lock.
//

class Solution {
    public int shortestPathAllKeys(String[] grid) {
        int m = grid.length, n = grid[0].length();
        int allKeys = 0;
        int startX = 0, startY = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                char c = grid[i].charAt(j);
                if (c == '@') {
                    startX = i;
                    startY = j;
                } else if (c >= 'a' && c <= 'f') {
                    allKeys |= (1 << (c - 'a'));
                }
            }
        }

        Queue<int[]> queue = new LinkedList<>();
        boolean[][][] visited = new boolean[m][n][1 << 6];
        queue.offer(new int[]{startX, startY, 0, 0});
        visited[startX][startY][0] = true;

        int[][] directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        while (!queue.isEmpty()) {
            int[] curr = queue.poll();
            int x = curr[0], y = curr[1], keys = curr[2], steps = curr[3];

            if (keys == allKeys) {
                return steps;
            }

            for (int[] dir : directions) {
                int newX = x + dir[0];
                int newY = y + dir[1];
                int newKeys = keys;

                if (newX < 0 || newX >= m || newY < 0 || newY >= n) continue;

                char cell = grid[newX].charAt(newY);
                if (cell == '#') continue;

                if (cell >= 'a' && cell <= 'f') {
                    newKeys |= (1 << (cell - 'a'));
                } else if (cell >= 'A' && cell <= 'F') {
                    if ((keys & (1 << (cell - 'A'))) == 0) continue;
                }

                if (!visited[newX][newY][newKeys]) {
                    visited[newX][newY][newKeys] = true;
                    queue.offer(new int[]{newX, newY, newKeys, steps + 1});
                }
            }
        }

        return -1;          
    }
}
