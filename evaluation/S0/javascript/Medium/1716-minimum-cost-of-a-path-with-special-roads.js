// Source: https://leetcode.com/problems/minimum-cost-of-a-path-with-special-roads/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array start where start = [startX, startY] represents your initial position (startX, startY) in a 2D space. You are also given the array target where target = [targetX, targetY] represents your target position (targetX, targetY).
//
// The cost of going from a position (x1, y1) to any other position in the space (x2, y2) is |x2 - x1| + |y2 - y1|.
//
// There are also some special roads. You are given a 2D array specialRoads where specialRoads[i] = [x1i, y1i, x2i, y2i, costi] indicates that the ith special road goes in one direction from (x1i, y1i) to (x2i, y2i) with a cost equal to costi. You can use each special road any number of times.
//
// Return the minimum cost required to go from (startX, startY) to (targetX, targetY).
//
// Example:
// Input: start = [1,1], target = [4,5], specialRoads = [[1,2,3,3,2],[3,4,4,5,1]]
//
// Output: 5
//
// Explanation:
//
//
// 	(1,1) to (1,2) with a cost of |1 - 1| + |2 - 1| = 1.
// 	(1,2) to (3,3). Use specialRoads[0] with the cost 2.
// 	(3,3) to (3,4) with a cost of |3 - 3| + |4 - 3| = 1.
// 	(3,4) to (4,5). Use specialRoads[1] with the cost 1.
//
//
// So the total cost is 1 + 2 + 1 + 1 = 5.
//
// Constraints:
// start.length == target.length == 2
// 	1 <= startX <= targetX <= 105
// 	1 <= startY <= targetY <= 105
// 	1 <= specialRoads.length <= 200
// 	specialRoads[i].length == 5
// 	startX <= x1i, x2i <= targetX
// 	startY <= y1i, y2i <= targetY
// 	1 <= costi <= 105
//

/**
 * @param {number[]} start
 * @param {number[]} target
 * @param {number[][]} specialRoads
 * @return {number}
 */
var minimumCost = function(start, target, specialRoads) {
    const n = specialRoads.length;
    const dist = new Array(n + 2).fill(Infinity);
    dist[0] = 0; // Distance to start point
    const points = [start, ...specialRoads.map(road => [road[2], road[3]]), target];
    const pq = [[0, 0]]; // [distance, pointIndex]
        
    while (pq.length) {
        pq.sort((a, b) => a[0] - b[0]);
        const [currentDist, u] = pq.shift();
        if (currentDist > dist[u]) continue;
        for (let v = 0; v < points.length; v++) {
            if (u === v) continue;
            let cost;
            if (u === 0) {
                cost = Math.abs(points[u][0] - points[v][0]) + Math.abs(points[u][1] - points[v][1]);
            } else if (v === n + 1) {
                cost = Math.abs(points[u][0] - points[v][0]) + Math.abs(points[u][1] - points[v][1]);
            } else {
                const road = specialRoads[u - 1];
                cost = Math.min(
                    Math.abs(points[u][0] - points[v][0]) + Math.abs(points[u][1] - points[v][1]),
                    road[4] + Math.abs(road[0] - points[v][0]) + Math.abs(road[1] - points[v][1])
                );
            }
            if (dist[u] + cost < dist[v]) {
                dist[v] = dist[u] + cost;
                pq.push([dist[v], v]);
            }
        }
    }
    return dist[n + 1]; 
    
};
