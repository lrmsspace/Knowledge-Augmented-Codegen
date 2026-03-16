// Source: https://leetcode.com/problems/number-of-boomerangs/   |   Difficulty: Medium
//
// Problem Description:
// You are given n points in the plane that are all distinct, where points[i] = [xi, yi]. A boomerang is a tuple of points (i, j, k) such that the distance between i and j equals the distance between i and k (the order of the tuple matters).
//
// Return the number of boomerangs.
//
// Example:
// Input: points = [[0,0],[1,0],[2,0]]
// Output: 2
// Explanation: The two boomerangs are [[1,0],[0,0],[2,0]] and [[1,0],[2,0],[0,0]].
//
// Constraints:
// n == points.length
// 	1 <= n <= 500
// 	points[i].length == 2
// 	-104 <= xi, yi <= 104
// 	All the points are unique.
//

class Solution {
public:
    int numberOfBoomerangs(vector<vector<int>>& points) {
        int result = 0;
        for (const auto& p1 : points) {
            unordered_map<int, int> distanceCount;
            for (const auto& p2 : points) {
                if (p1 == p2) continue;
                int dx = p1[0] - p2[0];
                int dy = p1[1] - p2[1];
                int distSquared = dx * dx + dy * dy;
                distanceCount[distSquared]++;
            }
            for (const auto& [dist, count] : distanceCount) {
                if (count > 1) {
                    result += count * (count - 1);
                }
            }
        }
        return result;          
    }
};
