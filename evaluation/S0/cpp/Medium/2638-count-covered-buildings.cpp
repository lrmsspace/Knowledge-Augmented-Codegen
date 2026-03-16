// Source: https://leetcode.com/problems/count-covered-buildings/   |   Difficulty: Medium
//
// Problem Description:
// You are given a positive integer n, representing an n x n city. You are also given a 2D grid buildings, where buildings[i] = [x, y] denotes a unique building located at coordinates [x, y].
//
// A building is covered if there is at least one building in all four directions: left, right, above, and below.
//
// Return the number of covered buildings.
//
// Example:
// Input: n = 3, buildings = [[1,2],[2,2],[3,2],[2,1],[2,3]]
//
// Output: 1
//
// Explanation:
//
//
// 	Only building [2,2] is covered as it has at least one building:
//
// 	
// 		above ([1,2])
// 		below ([3,2])
// 		left ([2,1])
// 		right ([2,3])
// 	
// 	
// 	Thus, the count of covered buildings is 1.
//
// Constraints:
// 2 <= n <= 105
// 	1 <= buildings.length <= 105 
// 	buildings[i] = [x, y]
// 	1 <= x, y <= n
// 	All coordinates of buildings are unique.
//

class Solution {
public:
    int countCoveredBuildings(int n, vector<vector<int>>& buildings) {
        unordered_set<long long> buildingSet;
        for (const auto& b : buildings) {
            long long code = ((long long)(b[0]) << 32) | b[1];
            buildingSet.insert(code);
        }

        int coveredCount = 0;
        for (const auto& b : buildings) {
            int x = b[0];
            int y = b[1];

            bool hasAbove = buildingSet.count(((long long)(x - 1) << 32) | y) > 0;
            bool hasBelow = buildingSet.count(((long long)(x + 1) << 32) | y) > 0;
            bool hasLeft = buildingSet.count(((long long)(x) << 32) | (y - 1)) > 0;
            bool hasRight = buildingSet.count(((long long)(x) << 32) | (y + 1)) > 0;

            if (hasAbove && hasBelow && hasLeft && hasRight) {
                coveredCount++;
            }
        }

        return coveredCount;            
    }
};
