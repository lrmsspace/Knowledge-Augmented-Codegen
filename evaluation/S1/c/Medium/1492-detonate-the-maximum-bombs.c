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
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maximumDetonation(int** bombs, int bombsSize, int* bombsColSize) {
    int maxDetonated = 0;

    for (int i = 0; i < bombsSize; i++) {
        int detonatedCount = 0;
        int visited[100] = {0};
        int queue[100];
        int front = 0, rear = 0;

        queue[rear++] = i;
        visited[i] = 1;

        while (front < rear) {
            int current = queue[front++];
            detonatedCount++;

            for (int j = 0; j < bombsSize; j++) {
                if (!visited[j]) {
                    long long dx = bombs[current][0] - bombs[j][0];
                    long long dy = bombs[current][1] - bombs[j][1];
                    long long r = bombs[current][2];
                    if (dx * dx + dy * dy <= r * r) {
                        queue[rear++] = j;
                        visited[j] = 1;
                    }
                }
            }
        }

        if (detonatedCount > maxDetonated) {
            maxDetonated = detonatedCount;
        }
    }

    return maxDetonated;        
}
