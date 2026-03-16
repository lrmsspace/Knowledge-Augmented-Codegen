// Source: https://leetcode.com/problems/trapping-rain-water-ii/   |   Difficulty: Hard
//
// Problem Description:
// Given an m x n integer matrix heightMap representing the height of each unit cell in a 2D elevation map, return the volume of water it can trap after raining.
//
// Example:
// Input: heightMap = [[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]]
// Output: 4
// Explanation: After the rain, water is trapped between the blocks.
// We have two small ponds 1 and 3 units trapped.
// The total volume of water trapped is 4.
//
// Constraints:
// m == heightMap.length
// 	n == heightMap[i].length
// 	1 <= m, n <= 200
// 	0 <= heightMap[i][j] <= 2 * 104
//

/**
 * @param {number[][]} heightMap
 * @return {number}
 */
var trapRainWater = function(heightMap) {
    const m = heightMap.length;
    const n = heightMap[0].length;
    const visited = Array.from({ length: m }, () => new Array(n).fill(false));
    const heap = new MinPriorityQueue({ priority: x => x.height });
    for (let i = 0; i < m; i++) {
        heap.enqueue({ x: i, y: 0, height: heightMap[i][0] });
        heap.enqueue({ x: i, y: n - 1, height: heightMap[i][n - 1] });
        visited[i][0] = true;
        visited[i][n - 1] = true;
    }
    for (let j = 0; j < n; j++) {
        heap.enqueue({ x: 0, y: j, height: heightMap[0][j] });
        heap.enqueue({ x: m - 1, y: j, height: heightMap[m - 1][j] });
        visited[0][j] = true;
        visited[m - 1][j] = true;
    }
    const directions = [[1, 0], [-1, 0], [0, 1], [0, -1]];
    let waterTrapped = 0;
    while (!heap.isEmpty()) {
        const { x, y, height } = heap.dequeue().element;
        for (let [dx, dy] of directions) {
            const newX = x + dx;
            const newY = y + dy;
            if (newX >= 0 && newX < m && newY >= 0 && newY < n && !visited[newX][newY]) {
                visited[newX][newY] = true;
                waterTrapped += Math.max(0, height - heightMap[newX][newY]);
                heap.enqueue({ x: newX, y: newY, height: Math.max(height, heightMap[newX][newY]) });
            }
        }   
        
    }
    return waterTrapped;    
};
