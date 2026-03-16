// Source: https://leetcode.com/problems/reaching-points/   |   Difficulty: Hard
//
// Problem Description:
// Given four integers sx, sy, tx, and ty, return true if it is possible to convert the point (sx, sy) to the point (tx, ty) through some operations, or false otherwise.
//
// The allowed operation on some point (x, y) is to convert it to either (x, x + y) or (x + y, y).
//
// Example:
// Input: sx = 1, sy = 1, tx = 3, ty = 5
// Output: true
// Explanation:
// One series of moves that transforms the starting point to the target is:
// (1, 1) -> (1, 2)
// (1, 2) -> (3, 2)
// (3, 2) -> (3, 5)
//
// Constraints:
// 1 <= sx, sy, tx, ty <= 109
//

class Solution {
public:
    bool reachingPoints(int sx, int sy, int tx, int ty) {
        while (tx >= sx && ty >= sy) {
            if (tx == sx && ty == sy) return true;
            if (tx > ty) {
                if (ty > sy) {
                    tx %= ty;
                } else {
                    // ty == sy
                    return (tx - sx) % ty == 0;
                }
            } else {
                if (tx > sx) {
                    ty %= tx;
                } else {
                    // tx == sx
                    return (ty - sy) % tx == 0;
                }
            }
        }
        return false;           
    }
};
