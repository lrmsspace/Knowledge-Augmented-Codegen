// Source: https://leetcode.com/problems/self-crossing/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of integers distance.
//
// You start at the point (0, 0) on an X-Y plane, and you move distance[0] meters to the north, then distance[1] meters to the west, distance[2] meters to the south, distance[3] meters to the east, and so on. In other words, after each move, your direction changes counter-clockwise.
//
// Return true if your path crosses itself or false if it does not.
//
// Example:
// Input: distance = [2,1,1,2]
// Output: true
// Explanation: The path crosses itself at the point (0, 1).
//
// Constraints:
// 1 <= distance.length <= 105
// 	1 <= distance[i] <= 105
//

class Solution {
public:
    bool isSelfCrossing(vector<int>& distance) {
        int n = distance.size();
        for (int i = 3; i < n; i++) {
            // Case 1: Current line crosses the line 3 steps ahead
            if (distance[i] >= distance[i - 2] && distance[i - 1] <= distance[i - 3]) {
                return true;
            }
            // Case 2: Current line overlaps the line 4 steps ahead
            if (i >= 4 && distance[i - 1] == distance[i - 3] && distance[i] + distance[i - 4] >= distance[i - 2]) {
                return true;
            }
            // Case 3: Current line crosses the line 5 steps ahead
            if (i >= 5 && distance[i - 2] >= distance[i - 4] && distance[i] + distance[i - 4] >= distance[i - 2] &&
                distance[i - 1] <= distance[i - 3] && distance[i - 1] + distance[i - 5] >= distance[i - 3]) {
                return true;
            }
        }
        return false;           
    }
};
