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
// Helpful references (internal KB):
// - Breadth-first search (graph, array, stack, bfs, enumeration)
//   • When to use: Use when finding the shortest path in an unweighted graph or traversing a graph level by level. It is suitable for exploring all reachable nodes from a source in increasing order of distance.
//   • Idea: Breadth-First Search (BFS) is a graph traversal algorithm that explores all the neighbor nodes at the current depth level before moving on to nodes at the next depth level. It finds the shortest path in an unweighted graph in O(V + E) time.
//   • Invariants: All nodes currently in the queue are at the same or adjacent depth level.; All 'marked' nodes have been visited, and their 'distTo' values are the shortest path from the source.
//   • Tips: Use a queue to manage nodes to visit, ensuring level-by-level exploration.; Maintain a 'visited' array or set to prevent cycles and redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.; Incorrectly using a stack instead of a queue will result in Depth-First Search behavior.
// - Strongly connected components and the condensation graph (graph, enumeration)
//   • When to use: When you need to identify maximal subgraphs where all vertices are mutually reachable, or to simplify a directed graph into a Directed Acyclic Graph (DAG) of components for further processing.
//   • Idea: This concept defines SCCs as maximal vertex subsets in a directed graph where all pairs are mutually reachable. It also introduces the condensation graph, which represents SCCs as nodes and forms a DAG, typically found in O(V+E) time.
//   • Invariants: Every vertex belongs to exactly one strongly connected component.; Within any SCC, a path exists from any vertex u to any other vertex v, and vice-versa.
//   • Tips: Understand that SCCs partition the graph's vertices.; The condensation graph is always a Directed Acyclic Graph (DAG).
//   • Pitfalls: Confusing SCCs with simple cycles or connected components in undirected graphs.; Incorrectly assuming the condensation graph has cycles.
// - Finding the Eulerian path in O(M) (graph, enumeration, bfs)
//   • When to use: Use when the problem requires visiting every edge in a graph exactly once, either starting and ending at the same vertex (cycle) or at two different vertices (path).
//   • Idea: An Eulerian path is a trail in a graph which visits every edge exactly once. An Eulerian cycle is an Eulerian path that starts and ends on the same vertex.
//   • Invariants: Every edge in the graph is considered exactly once for inclusion in the path.; The current path segment always forms a valid trail in the graph.
//   • Tips: Check vertex degrees to determine path/cycle existence before attempting to find it.; For an Eulerian path, start traversal from one of the two odd-degree vertices.
//   • Pitfalls: Incorrectly handling multi-edges or self-loops can lead to errors in degree calculation or traversal.; Failing to check graph connectivity can result in incomplete paths or infinite loops.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} bombs
 * @return {number}
 */
var maximumDetonation = function(bombs) {
    const n = bombs.length;
    const graph = Array.from({ length: n }, () => []);
    
    // Build the graph where an edge from bomb i to bomb j exists if bomb i can detonate bomb j
    for (let i = 0; i < n; i++) {
        const [x1, y1, r1] = bombs[i];
        for (let j = 0; j < n; j++) {
            if (i !== j) {
                const [x2, y2] = bombs[j];
                const distSq = (x1 - x2) ** 2 + (y1 - y2) ** 2;
                if (distSq <= r1 ** 2) {
                    graph[i].push(j);
                }
            }
        }
    }

    // Function to perform BFS and count detonated bombs starting from bomb `start`
    const bfs = (start) => {
        const visited = Array(n).fill(false);
        const queue = [start];
        visited[start] = true;
        let count = 1;

        while (queue.length > 0) {
            const node = queue.shift();
            for (const neighbor of graph[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    queue.push(neighbor);
                    count++;
                }
            }
        }
        return count;
    };

    let maxDetonated = 0;
    for (let i = 0; i < n; i++) {
        maxDetonated = Math.max(maxDetonated, bfs(i));
    }

    return maxDetonated;
};
