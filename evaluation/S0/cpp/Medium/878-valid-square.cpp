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
public:
    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
        vector<int> dists = {
            distSq(p1, p2), distSq(p1, p3), distSq(p1, p4),
            distSq(p2, p3), distSq(p2, p4), distSq(p3, p4)
        };
        sort(dists.begin(), dists.end());

        // Check for zero length sides
        if (dists[0] == 0) return false;

        // Check that the first four distances (sides) are equal
        for (int i = 1; i < 4; ++i) {
            if (dists[i] != dists[0]) return false;
        }

        // Check that the last two distances (diagonals) are equal
        if (dists[4] != dists[5]) return false;

        // Check that the diagonal is sqrt(2) times the side
        if (dists[4] != 2 * dists[0]) return false;

        return true;            
    }
};
