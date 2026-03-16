// Source: https://leetcode.com/problems/detonate-the-maximum-bombs/   |   Difficulty: Medium
//
// Problem Description:
// You are given a list of bombs. The range of a bomb is defined as the area where its effect can be felt. This area is in the shape of a circle with the center as the location of the bomb.
//
// The bombs are represented by a 0-indexed 2D integer array bombs where bombs[i] = [xi, yi, ri]. xi and yi denote the X-coordinate and Y-coordinate of the location of the ith bomb, whereas ri denotes the radius of its range.
//
// You may choose to detonate a single bomb. When a bomb is detonated, it will detonate all bombs that lie in its range. These bombs will further detonate the bombs that lie in their ranges.
//
// Given the list of bombs, return the maximum number of bombs that can be detonated if you are allowed to detonate only one bomb.
//
// Example:
// Input: bombs = [[2,1,3],[6,1,4]]
// Output: 2
// Explanation:
// The above figure shows the positions and ranges of the 2 bombs.
// If we detonate the left bomb, the right bomb will not be affected.
// But if we detonate the right bomb, both bombs will be detonated.
// So the maximum bombs that can be detonated is max(1, 2) = 2.
//
// Constraints:
// 1 <= bombs.length <= 100
// 	bombs[i].length == 3
// 	1 <= xi, yi, ri <= 105
//

/**
 * @param {number[][]} bombs
 * @return {number}
 */
var maximumDetonation = function(bombs) {
    const n = bombs.length;
    const graph = Array.from({ length: n }, () => []);
    for (let i = 0; i < n; i++) {
        const [x1, y1, r1] = bombs[i];
        for (let j = 0; j < n; j++) {
            if (i !== j) {
                const [x2, y2] = bombs[j];
                const distanceSquared = (x1 - x2) ** 2 + (y1 - y2) ** 2;
                if (distanceSquared <= r1 ** 2) {
                    graph[i].push(j);
                }
            }
        }
    }
    const dfs = (start, visited) => {
        visited.add(start);
        for (const neighbor of graph[start]) {
            if (!visited.has(neighbor)) {
                dfs(neighbor, visited);
            }
        }
    };
    let maxDetonated = 0;
    for (let i = 0; i < n; i++) {
        const visited = new Set();
        dfs(i, visited);
        maxDetonated = Math.max(maxDetonated, visited.size);
    }
    return maxDetonated;    
};
