// Source: https://leetcode.com/problems/determine-if-a-cell-is-reachable-at-a-given-time/   |   Difficulty: Medium
//
// Problem Description:
// You are given four integers sx, sy, fx, fy, and a non-negative integer t.
//
// In an infinite 2D grid, you start at the cell (sx, sy). Each second, you must move to any of its adjacent cells.
//
// Return true if you can reach cell (fx, fy) after exactly t seconds, or false otherwise.
//
// A cell's adjacent cells are the 8 cells around it that share at least one corner with it. You can visit the same cell several times.
//
// Example:
// Input: sx = 2, sy = 4, fx = 7, fy = 7, t = 6
// Output: true
// Explanation: Starting at cell (2, 4), we can reach cell (7, 7) in exactly 6 seconds by going through the cells depicted in the picture above.
//
// Constraints:
// 1 <= sx, sy, fx, fy <= 109
// 	0 <= t <= 109
//

bool isReachableAtTime(int sx, int sy, int fx, int fy, int t){
    int dx = fx - sx;
    int dy = fy - sy;
    int dist = (dx > 0 ? dx : -dx) > (dy > 0 ? dy : -dy) ? (dx > 0 ? dx : -dx) : (dy > 0 ? dy : -dy);
    return dist <= t && (t - dist) % 2 == 0;
}
