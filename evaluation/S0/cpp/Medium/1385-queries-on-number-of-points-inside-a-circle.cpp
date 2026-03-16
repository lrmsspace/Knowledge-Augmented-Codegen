// Source: https://leetcode.com/problems/queries-on-number-of-points-inside-a-circle/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array points where points[i] = [xi, yi] is the coordinates of the ith point on a 2D plane. Multiple points can have the same coordinates.
//
// You are also given an array queries where queries[j] = [xj, yj, rj] describes a circle centered at (xj, yj) with a radius of rj.
//
// For each query queries[j], compute the number of points inside the jth circle. Points on the border of the circle are considered inside.
//
// Return an array answer, where answer[j] is the answer to the jth query.
//
// Example:
// Input: points = [[1,3],[3,3],[5,3],[2,2]], queries = [[2,3,1],[4,3,1],[1,1,2]]
// Output: [3,2,2]
// Explanation: The points and circles are shown above.
// queries[0] is the green circle, queries[1] is the red circle, and queries[2] is the blue circle.
//
// Constraints:
// 1 <= points.length <= 500
// 	points[i].length == 2
// 	0 <= x​​​​​​i, y​​​​​​i <= 500
// 	1 <= queries.length <= 500
// 	queries[j].length == 3
// 	0 <= xj, yj <= 500
// 	1 <= rj <= 500
// 	All coordinates are integers.
//
//
//  
// Follow up: Could you find the answer for each query in better complexity than O(n)?
//

class Solution {
public:
    vector<int> countPoints(vector<vector<int>>& points, vector<vector<int>>& queries) {
        vector<int> result;
        for (const auto& query : queries) {
            int count = 0;
            int qx = query[0];
            int qy = query[1];
            int r = query[2];
            int rSquared = r * r;
            for (const auto& point : points) {
                int px = point[0];
                int py = point[1];
                int dx = px - qx;
                int dy = py - qy;
                if (dx * dx + dy * dy <= rSquared) {
                    count++;
                }
            }
            result.push_back(count);
        }
        return result;          
    }
};
