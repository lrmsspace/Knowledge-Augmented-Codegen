// Source: https://leetcode.com/problems/maximum-points-inside-the-square/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D array points and a string s where, points[i] represents the coordinates of point i, and s[i] represents the tag of point i.
//
// A valid square is a square centered at the origin (0, 0), has edges parallel to the axes, and does not contain two points with the same tag.
//
// Return the maximum number of points contained in a valid square.
//
// Note:
//
//
// 	A point is considered to be inside the square if it lies on or within the square's boundaries.
// 	The side length of the square can be zero.
//
// Example:
// Input: points = [[2,2],[-1,-2],[-4,4],[-3,1],[3,-3]], s = "abdca"
//
// Output: 2
//
// Explanation:
//
// The square of side length 4 covers two points points[0] and points[1].
//
// Constraints:
// 1 <= s.length, points.length <= 105
// 	points[i].length == 2
// 	-109 <= points[i][0], points[i][1] <= 109
// 	s.length == points.length
// 	points consists of distinct coordinates.
// 	s consists only of lowercase English letters.
//

class Solution {
public:
    int maxPointsInsideSquare(vector<vector<int>>& points, string s) {
        int n = points.size();
        vector<long long> dists(n);
        for (int i = 0; i < n; ++i) {
            dists[i] = static_cast<long long>(max(abs(points[i][0]), abs(points[i][1])));
        }
        sort(dists.begin(), dists.end());

        int left = 0, right = dists.size() - 1;
        int result = 0;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            long long side = dists[mid];

            unordered_set<char> tags;
            bool valid = true;

            for (int i = 0; i < n; ++i) {
                if (max(abs(points[i][0]), abs(points[i][1])) <= side) {
                    if (tags.count(s[i])) {
                        valid = false;
                        break;
                    }
                    tags.insert(s[i]);
                }
            }

            if (valid) {
                result = tags.size();
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        return result;          
    }
};
