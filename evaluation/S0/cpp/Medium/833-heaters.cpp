// Source: https://leetcode.com/problems/heaters/   |   Difficulty: Medium
//
// Problem Description:
// Winter is coming! During the contest, your first job is to design a standard heater with a fixed warm radius to warm all the houses.
//
// Every house can be warmed, as long as the house is within the heater's warm radius range. 
//
// Given the positions of houses and heaters on a horizontal line, return the minimum radius standard of heaters so that those heaters could cover all houses.
//
// Notice that all the heaters follow your radius standard, and the warm radius will be the same.
//
// Example:
// Input: houses = [1,2,3], heaters = [2]
// Output: 1
// Explanation: The only heater was placed in the position 2, and if we use the radius 1 standard, then all the houses can be warmed.
//
// Constraints:
// 1 <= houses.length, heaters.length <= 3 * 104
// 	1 <= houses[i], heaters[i] <= 109
//

class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        sort(heaters.begin(), heaters.end());
        int radius = 0;

        for (int house : houses) {
            int left = 0, right = heaters.size() - 1;
            int closestDist = INT_MAX;

            // Binary search to find the closest heater
            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (heaters[mid] == house) {
                    closestDist = 0;
                    break;
                } else if (heaters[mid] < house) {
                    closestDist = min(closestDist, house - heaters[mid]);
                    left = mid + 1;
                } else {
                    closestDist = min(closestDist, heaters[mid] - house);
                    right = mid - 1;
                }
            }

            radius = max(radius, closestDist);
        }

        return radius;          
    }
};
