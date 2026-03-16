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

int shortestPathAllKeys(char** grid, int gridSize) {
    int n = strlen(grid[0]);
    int totalKeys = 0;
    int startX, startY;

    // Find the starting point and count total keys
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == '@') {
                startX = i;
                startY = j;
            } else if (grid[i][j] >= 'a' && grid[i][j] <= 'f') {
                totalKeys |= (1 << (grid[i][j] - 'a'));
            }
        }
    }

    // BFS initialization
    typedef struct {
        int x, y, keys;
    } State;

    State queue[90000];
    int front = 0, back = 0;
    int visited[30][30][64] = {{{0}}};
    queue[back++] = (State){startX, startY, 0};
    visited[startX][startY][0] = 1;
    int steps = 0;

    int directions[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

    // BFS loop
    while (front < back) {
        int levelSize = back - front;
        for (int i = 0; i < levelSize; ++i) {
            State curr = queue[front++];
            if (curr.keys == totalKeys) return steps;

            for (int d = 0; d < 4; ++d) {
                int newX = curr.x + directions[d][0];
                int newY = curr.y + directions[d][1];
                int newKeys = curr.keys;

                if (newX < 0 || newX >= gridSize || newY < 0 || newY >= n) continue;
                char cell = grid[newX][newY];
                if (cell == '#') continue;

                if (cell >= 'a' && cell <= 'f') {
                    newKeys |= (1 << (cell - 'a'));
                } else if (cell >= 'A' && cell <= 'F') {
                    if (!(newKeys & (1 << (cell - 'A')))) continue;
                }

                if (!visited[newX][newY][newKeys]) {
                    visited[newX][newY][newKeys] = 1;
                    queue[back++] = (State){newX, newY, newKeys};
                }
            }
        }
        steps++;
        }
    return -1;
}
