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
    public int findRadius(int[] houses, int[] heaters) {
        Arrays.sort(heaters);
        int radius = 0;

        for (int house : houses) {
            int index = Arrays.binarySearch(heaters, house);
            if (index < 0) {
                index = -index - 1;
            }

            int dist1 = index - 1 >= 0 ? house - heaters[index - 1] : Integer.MAX_VALUE;
            int dist2 = index < heaters.length ? heaters[index] - house : Integer.MAX_VALUE;

            radius = Math.max(radius, Math.min(dist1, dist2));
        }

        return radius;          
    }
}
