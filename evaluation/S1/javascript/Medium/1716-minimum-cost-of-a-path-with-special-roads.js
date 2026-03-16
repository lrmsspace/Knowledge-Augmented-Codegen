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
// Helpful references (internal KB):
// - Dijkstra on sparse graphs (heap, queue, dijkstra)
//   • When to use: When you need to find the shortest paths from a single source vertex to all other vertices in a graph with non-negative edge weights, especially efficient for sparse graphs.
//   • Idea: Dijkstra's algorithm finds the shortest paths from a single source to all other vertices in a weighted graph with non-negative edge weights. It uses a priority queue to greedily explore vertices, achieving O(E log V) complexity with a binary heap.
//   • Invariants: At the start of each iteration, dist[u] holds the shortest distance found so far from the source to u.; All vertices already extracted from the priority queue have their final shortest distance determined.
//   • Tips: Use a priority queue (min-heap) to efficiently retrieve the unvisited vertex with the smallest distance.; Initialize all distances to infinity and the source distance to zero.
//   • Pitfalls: Does not work correctly with negative edge weights; Bellman-Ford or SPFA is needed.; Forgetting to mark vertices as visited or handle duplicate entries in the priority queue can lead to incorrectness or TLE.
// - Solving assignment problem using min-cost-flow (graph, dijkstra, bellman-ford)
//   • When to use: Use when finding a one-to-one assignment between two sets of entities, such as workers to tasks, to minimize the total cost. It's suitable for problems modelable as min-cost max-flow in a bipartite graph.
//   • Idea: This technique models the assignment problem as a minimum cost maximum flow problem on a specially constructed bipartite graph. It finds a perfect matching with the lowest total cost, typically with a polynomial time complexity depending on the shortest path algorithm used.
//   • Invariants: Flow conservation holds for all intermediate nodes in the network.; The flow on any edge never exceeds its defined capacity.
//   • Tips: Construct a bipartite graph with a source and sink nodes.; Set capacities to 1 for all assignment-related edges to ensure one-to-one mapping.
//   • Pitfalls: Incorrectly modeling capacities or costs on graph edges can lead to wrong solutions.; Forgetting to ensure a perfect matching (flow value equals N) is found for a complete assignment.
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} start
 * @param {number[]} target
 * @param {number[][]} specialRoads
 * @return {number}
 */
var minimumCost = function(start, target, specialRoads) {
    const [startX, startY] = start;
    const [targetX, targetY] = target;
    const graph = new Map();

    const addEdge = (x1, y1, x2, y2, cost) => {
        const key1 = `${x1},${y1}`;
        const key2 = `${x2},${y2}`;
        if (!graph.has(key1)) graph.set(key1, []);
        graph.get(key1).push([key2, cost]);
    }

    // Add edges for special roads
    for (const [x1, y1, x2, y2, cost] of specialRoads) {
        addEdge(x1, y1, x2, y2, cost);
    }

    // Add edges for direct paths (Manhattan distance)
    const points = new Set([`${startX},${startY}`, `${targetX},${targetY}`]);
    for (const [x1, y1, x2, y2] of specialRoads) {
        points.add(`${x1},${y1}`);
        points.add(`${x2},${y2}`);
    }
    const pointList = Array.from(points);
    for (let i = 0; i < pointList.length; i++) {
        for (let j = i + 1; j < pointList.length; j++) {
            const [x1, y1] = pointList[i].split(',').map(Number);
            const [x2, y2] = pointList[j].split(',').map(Number);
            const cost = Math.abs(x2 - x1) + Math.abs(y2 - y1);
            addEdge(x1, y1, x2, y2, cost);
            addEdge(x2, y2, x1, y1, cost);
        }
    }
    
    // Dijkstra's algorithm to find the minimum cost path
    const distances = new Map();
    const pq = new MinPriorityQueue({ priority: x => x[1] });
    const startKey = `${startX},${startY}`;
    distances.set(startKey, 0);
    pq.enqueue([startKey, 0]);

    while (!pq.isEmpty()) {
        const [current, currentDist] = pq.dequeue().element;
        if (current === `${targetX},${targetY}`) {
            return currentDist;
        }
        if (currentDist > distances.get(current)) continue;

        for (const [neighbor, cost] of (graph.get(current) || [])) {
            const newDist = currentDist + cost;
            if (newDist < (distances.get(neighbor) || Infinity)) {
                distances.set(neighbor, newDist);
                pq.enqueue([neighbor, newDist]);
            }
        }
    }

    return Math.abs(targetX - startX) + Math.abs(targetY - startY);
    
};
