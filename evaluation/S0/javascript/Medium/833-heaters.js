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

/**
 * @param {number[]} houses
 * @param {number[]} heaters
 * @return {number}
 */
var findRadius = function(houses, heaters) {
    heaters.sort((a, b) => a - b);
    let radius = 0;
    for (const house of houses) {
        let left = 0;
        let right = heaters.length - 1;
        while (left < right) {
            const mid = Math.floor((left + right) / 2);
            if (heaters[mid] < house) {
                left = mid + 1;
            }

            else {
                right = mid;
            }
        }
        const dist1 = Math.abs(heaters[left] - house);
        const dist2 = left > 0 ? Math.abs(heaters[left - 1] - house) : Infinity;
        const minDist = Math.min(dist1, dist2);
        radius = Math.max(radius, minDist);
    }
    return radius;
};
