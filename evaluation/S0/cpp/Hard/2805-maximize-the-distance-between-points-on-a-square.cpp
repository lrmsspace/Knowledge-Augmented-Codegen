// Source: https://leetcode.com/problems/maximize-the-distance-between-points-on-a-square/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer side, representing the edge length of a square with corners at (0, 0), (0, side), (side, 0), and (side, side) on a Cartesian plane.
//
// You are also given a positive integer k and a 2D integer array points, where points[i] = [xi, yi] represents the coordinate of a point lying on the boundary of the square.
//
// You need to select k elements among points such that the minimum Manhattan distance between any two points is maximized.
//
// Return the maximum possible minimum Manhattan distance between the selected k points.
//
// The Manhattan Distance between two cells (xi, yi) and (xj, yj) is |xi - xj| + |yi - yj|.
//
// Example:
// Input: side = 2, points = [[0,2],[2,0],[2,2],[0,0]], k = 4
//
// Output: 2
//
// Explanation:
//
//
//
// Select all four points.
//
// Constraints:
// 1 <= side <= 109
// 	4 <= points.length <= min(4 * side, 15 * 103)
// 	points[i] == [xi, yi]
// 	The input is generated such that:
// 	
// 		points[i] lies on the boundary of the square.
// 		All points[i] are unique.
// 	
// 	
// 	4 <= k <= min(25, points.length)
//

class Solution {
public:
    int maxDistance(int side, vector<vector<int>>& points, int k) {
        int n = points.size();
        vector<int> perimeter;
        for (const auto& p : points) {
            int x = p[0], y = p[1];
            int pos = 0;
            if (y == 0) {
                pos = x;
            } else if (x == side) {
                pos = side + y;
            } else if (y == side) {
                pos = 3 * side - x;
            } else { // x == 0
                pos = 4 * side - y;
            }
            perimeter.push_back(pos);
        }
        
        sort(perimeter.begin(), perimeter.end());
        
        int left = 0, right = 2 * side;
        int answer = 0;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int count = 1;
            int lastPos = perimeter[0];
            
            for (int i = 1; i < n; i++) {
                if (perimeter[i] - lastPos >= mid) {
                    count++;
                    lastPos = perimeter[i];
                }
            }
            
            if (count >= k) {
                answer = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return answer;          
    }
};
