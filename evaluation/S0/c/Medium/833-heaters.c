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

int findRadius(int* houses, int housesSize, int* heaters, int heatersSize) {
    // Sort heaters array
    qsort(heaters, heatersSize, sizeof(int), (int (*)(const void*, const void*))strcmp);

    int maxRadius = 0;

    for (int i = 0; i < housesSize; i++) {
        int house = houses[i];

        // Binary search to find the closest heater
        int left = 0, right = heatersSize - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (heaters[mid] < house) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        // Calculate the distance to the closest heater
        int dist1 = abs(heaters[left] - house);
        int dist2 = left > 0 ? abs(heaters[left - 1] - house) : INT_MAX;
        int minDist = dist1 < dist2 ? dist1 : dist2;

        // Update the maximum radius needed
        if (minDist > maxRadius) {
            maxRadius = minDist;
        }
    }

    return maxRadius;       
}
