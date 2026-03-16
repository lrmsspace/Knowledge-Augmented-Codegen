// Source: https://leetcode.com/problems/count-pairs-of-points-with-distance-k/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer array coordinates and an integer k, where coordinates[i] = [xi, yi] are the coordinates of the ith point in a 2D plane.
//
// We define the distance between two points (x1, y1) and (x2, y2) as (x1 XOR x2) + (y1 XOR y2) where XOR is the bitwise XOR operation.
//
// Return the number of pairs (i, j) such that i < j and the distance between points i and j is equal to k.
//
// Example:
// Input: coordinates = [[1,2],[4,2],[1,3],[5,2]], k = 5
// Output: 2
// Explanation: We can choose the following pairs:
// - (0,1): Because we have (1 XOR 4) + (2 XOR 2) = 5.
// - (2,3): Because we have (1 XOR 5) + (3 XOR 2) = 5.
//
// Constraints:
// 2 <= coordinates.length <= 50000
// 	0 <= xi, yi <= 106
// 	0 <= k <= 100
//

class Solution {
public:
    int countPairs(vector<vector<int>>& coordinates, int k) {
        int n = coordinates.size();
        int count = 0;

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int dist = (coordinates[i][0] ^ coordinates[j][0]) + (coordinates[i][1] ^ coordinates[j][1]);
                if (dist == k) {
                    ++count;
                }
            }
        }

        return count;           
    }
};
