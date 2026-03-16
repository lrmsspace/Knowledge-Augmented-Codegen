// Source: https://leetcode.com/problems/best-position-for-a-service-centre/   |   Difficulty: Hard
//
// Problem Description:
// A delivery company wants to build a new service center in a new city. The company knows the positions of all the customers in this city on a 2D-Map and wants to build the new center in a position such that the sum of the euclidean distances to all customers is minimum.
//
// Given an array positions where positions[i] = [xi, yi] is the position of the ith customer on the map, return the minimum sum of the euclidean distances to all customers.
//
// In other words, you need to choose the position of the service center [xcentre, ycentre] such that the following formula is minimized:
//
// Answers within 10-5 of the actual value will be accepted.
//
// Example:
// Input: positions = [[0,1],[1,0],[1,2],[2,1]]
// Output: 4.00000
// Explanation: As shown, you can see that choosing [xcentre, ycentre] = [1, 1] will make the distance to each customer = 1, the sum of all distances is 4 which is the minimum possible we can achieve.
//
// Constraints:
// 1 <= positions.length <= 50
// 	positions[i].length == 2
// 	0 <= xi, yi <= 100
//

/**
 * @param {number[][]} positions
 * @return {number}
 */
var getMinDistSum = function(positions) {
    const distance = (x, y) => {
        let sum = 0;
        for (const [px, py] of positions) {
            sum += Math.sqrt((px - x) ** 2 + (py - y) ** 2);
        }
        return sum;
    };

    let x = 50, y = 50;
    let step = 50;
    for (let i = 0; i < 100; i++) {
        let bestX = x, bestY = y, bestDist = distance(x, y);
        for (let dx of [-step, 0, step]) {
            for (let dy of [-step, 0, step]) {
                const nx = x + dx, ny = y + dy;
                const dist = distance(nx, ny);
                if (dist < bestDist) {
                    bestDist = dist;
                    bestX = nx;
                    bestY = ny;
                }
            }
        }
        if (bestX === x && bestY === y) {
            step /= 2;
        }
        x = bestX;
        y = bestY;
    }
    return distance(x, y);
};
