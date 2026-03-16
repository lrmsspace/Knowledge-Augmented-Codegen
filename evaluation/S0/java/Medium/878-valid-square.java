// Source: https://leetcode.com/problems/valid-square/   |   Difficulty: Medium
//
// Problem Description:
// Given the coordinates of four points in 2D space p1, p2, p3 and p4, return true if the four points construct a square.
//
// The coordinate of a point pi is represented as [xi, yi]. The input is not given in any order.
//
// A valid square has four equal sides with positive length and four equal angles (90-degree angles).
//
// Example:
// Input: p1 = [0,0], p2 = [1,1], p3 = [1,0], p4 = [0,1]
// Output: true
//
// Constraints:
// p1.length == p2.length == p3.length == p4.length == 2
// 	-104 <= xi, yi <= 104
//

class Solution {
    public boolean validSquare(int[] p1, int[] p2, int[] p3, int[] p4) {
        int[] dists = new int[6];
        dists[0] = distSq(p1, p2);
        dists[1] = distSq(p1, p3);
        dists[2] = distSq(p1, p4);
        dists[3] = distSq(p2, p3);
        dists[4] = distSq(p2, p4);
        dists[5] = distSq(p3, p4);

        Arrays.sort(dists);

        // Check for zero length sides
        if (dists[0] == 0) {
            return false;
        }

        // Check for four equal sides and two equal diagonals
        return dists[0] == dists[1] && dists[1] == dists[2] && dists[2] == dists[3] &&
               dists[4] == dists[5] &&
               2 * dists[0] == dists[4];            
    }
}
