// Source: https://leetcode.com/problems/falling-squares/   |   Difficulty: Hard
//
// Problem Description:
// There are several squares being dropped onto the X-axis of a 2D plane.
//
// You are given a 2D integer array positions where positions[i] = [lefti, sideLengthi] represents the ith square with a side length of sideLengthi that is dropped with its left edge aligned with X-coordinate lefti.
//
// Each square is dropped one at a time from a height above any landed squares. It then falls downward (negative Y direction) until it either lands on the top side of another square or on the X-axis. A square brushing the left/right side of another square does not count as landing on it. Once it lands, it freezes in place and cannot be moved.
//
// After each square is dropped, you must record the height of the current tallest stack of squares.
//
// Return an integer array ans where ans[i] represents the height described above after dropping the ith square.
//
// Example:
// Input: positions = [[1,2],[2,3],[6,1]]
// Output: [2,5,5]
// Explanation:
// After the first drop, the tallest stack is square 1 with a height of 2.
// After the second drop, the tallest stack is squares 1 and 2 with a height of 5.
// After the third drop, the tallest stack is still squares 1 and 2 with a height of 5.
// Thus, we return an answer of [2, 5, 5].
//
// Constraints:
// 1 <= positions.length <= 1000
// 	1 <= lefti <= 108
// 	1 <= sideLengthi <= 106
//

class Solution {
public:
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        map<int, int> heightMap; // key: right edge, value: height at that edge
        heightMap[0] = 0; // ground level

        vector<int> result;
        int currentMaxHeight = 0;

        for (const auto& pos : positions) {
            int left = pos[0];
            int sideLength = pos[1];
            int right = left + sideLength;

            // Find the maximum height in the range [left, right)
            auto it = heightMap.upper_bound(left);
            int baseHeight = 0;
            while (it != heightMap.end() && it->first < right) {
                baseHeight = max(baseHeight, it->second);
                ++it;
            }

            int newHeight = baseHeight + sideLength;
            currentMaxHeight = max(currentMaxHeight, newHeight);
            result.push_back(currentMaxHeight);

            // Update the height map
            heightMap[right] = max(heightMap[right], newHeight);
            // Clean up any heights that are now obsolete
            it = heightMap.upper_bound(left);
            while (it != heightMap.end() && it->first < right) {
                if (it->second <= newHeight) {
                    it = heightMap.erase(it);
                } else {
                    ++it;
                }
            }
        }

        return result;          
    }
};
