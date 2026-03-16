// Source: https://leetcode.com/problems/find-minimum-time-to-reach-last-room-i/   |   Difficulty: Medium
//
// Problem Description:
// There is a dungeon with n x m rooms arranged as a grid.
//
// You are given a 2D array moveTime of size n x m, where moveTime[i][j] represents the minimum time in seconds after which the room opens and can be moved to. You start from the room (0, 0) at time t = 0 and can move to an adjacent room. Moving between adjacent rooms takes exactly one second.
//
// Return the minimum time to reach the room (n - 1, m - 1).
//
// Two rooms are adjacent if they share a common wall, either horizontally or vertically.
//
// Example:
// Input: moveTime = [[0,4],[4,4]]
//
// Output: 6
//
// Explanation:
//
// The minimum time required is 6 seconds.
//
//
// 	At time t == 4, move from room (0, 0) to room (1, 0) in one second.
// 	At time t == 5, move from room (1, 0) to room (1, 1) in one second.
//
// Constraints:
// 2 <= n == moveTime.length <= 50
// 	2 <= m == moveTime[i].length <= 50
// 	0 <= moveTime[i][j] <= 109
//
// Helpful references (internal KB):
// - Dijkstra Algorithm (graph, array, dijkstra, greedy)
//   • When to use: Use this algorithm to find the shortest paths from a single source to all other vertices in a graph. It is applicable when all edge weights are non-negative.
//   • Idea: Dijkstra's algorithm finds the shortest paths from a single source vertex to all other vertices in a weighted graph with non-negative edge weights. It iteratively selects the unvisited vertex with the smallest known distance, relaxing its outgoing edges, achieving O(V^2 + E) or O(E log V) complexity.
//   • Invariants: For any marked vertex v, d[v] holds the true shortest path distance from s to v.; For any unmarked vertex v, d[v] holds the shortest path distance from s to v using only marked intermediate vertices.
//   • Tips: Use a priority queue for sparse graphs to optimize performance to O(E log V).; Initialize distances to infinity for all vertices except the source, which is zero.
//   • Pitfalls: Dijkstra's algorithm does not work correctly with negative edge weights; use Bellman-Ford or SPFA instead.; Failing to use an efficient data structure (like a priority queue) for vertex selection can lead to O(V^2) performance on sparse graphs.
// - Solving assignment problem using min-cost-flow (graph, dijkstra, bellman-ford)
//   • When to use: Use when finding a one-to-one assignment between two sets of entities, such as workers to tasks, to minimize the total cost. It's suitable for problems modelable as min-cost max-flow in a bipartite graph.
//   • Idea: This technique models the assignment problem as a minimum cost maximum flow problem on a specially constructed bipartite graph. It finds a perfect matching with the lowest total cost, typically with a polynomial time complexity depending on the shortest path algorithm used.
//   • Invariants: Flow conservation holds for all intermediate nodes in the network.; The flow on any edge never exceeds its defined capacity.
//   • Tips: Construct a bipartite graph with a source and sink nodes.; Set capacities to 1 for all assignment-related edges to ensure one-to-one mapping.
//   • Pitfalls: Incorrectly modeling capacities or costs on graph edges can lead to wrong solutions.; Forgetting to ensure a perfect matching (flow value equals N) is found for a complete assignment.
// - Number of paths of fixed length / Shortest paths of fixed length (graph, matrix, matrix-exp, counting)
//   • When to use: Use when needing to count the number of paths of a specific length between all pairs of vertices in a graph, or to find reachability in a fixed number of steps.
//   • Idea: This algorithm leverages matrix exponentiation to find the number of paths of a fixed length `k` between all pairs of vertices in a graph. Each matrix multiplication step extends path lengths by one, resulting in an O(N^3 log K) time complexity for an N-vertex graph.
//   • Invariants: After `m` matrix multiplications, `C_m[i][j]` stores the number of paths of length `m` from `i` to `j`.; The initial adjacency matrix `G` remains constant throughout the exponentiation process.
//   • Tips: Represent the graph as an adjacency matrix where `G[i][j]` is the number of direct edges.; Matrix multiplication `C_k * G` yields `C_{k+1}` for path counts.
//   • Pitfalls: Standard matrix multiplication is O(N^3), leading to O(N^3 log K) overall time complexity.; Memory usage is O(N^2) for storing matrices, which can be prohibitive for very large graphs.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} moveTime
 * @return {number}
 */
var minTimeToReach = function(moveTime) {
    const n = moveTime.length;
    const m = moveTime[0].length;
    const directions = [[0, 1], [1, 0], [0, -1], [-1, 0]];
    
    const minHeap = new MinPriorityQueue({ priority: x => x.time });
    minHeap.enqueue({ x: 0, y: 0, time: 0 });
    
    while (!minHeap.isEmpty()) {
        const { x, y, time } = minHeap.dequeue().element;
        
        if (x === n - 1 && y === m - 1) {
            return time;
        }
        
        for (const [dx, dy] of directions) {
            const newX = x + dx;
            const newY = y + dy;
            
            if (newX >= 0 && newX < n && newY >= 0 && newY < m) {
                const nextTime = Math.max(time + 1, moveTime[newX][newY]);
                minHeap.enqueue({ x: newX, y: newY, time: nextTime });
            }
        }
    }
    
    return -1; // In case there's no valid path
};
