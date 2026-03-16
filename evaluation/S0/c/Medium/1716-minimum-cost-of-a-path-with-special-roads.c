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

int minimumCost(int* start, int startSize, int* target, int targetSize, int** specialRoads, int specialRoadsSize, int* specialRoadsColSize) {
    int minCost = abs(target[0] - start[0]) + abs(target[1] - start[1]);
    for (int i = 0; i < specialRoadsSize; i++) {
        int costToSpecialStart = abs(specialRoads[i][0] - start[0]) + abs(specialRoads[i][1] - start[1]);
        int specialRoadCost = specialRoads[i][4];
        int costFromSpecialEndToTarget = abs(target[0] - specialRoads[i][2]) + abs(target[1] - specialRoads[i][3]);
        int totalCost = costToSpecialStart + specialRoadCost + costFromSpecialEndToTarget;
        if (totalCost < minCost) {
            minCost = totalCost;
        }
    }
    return minCost;     
}
