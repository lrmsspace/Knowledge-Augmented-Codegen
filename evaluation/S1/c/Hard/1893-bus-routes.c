// Source: https://leetcode.com/problems/bus-routes/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array routes representing bus routes where routes[i] is a bus route that the ith bus repeats forever.
//
//
// 	For example, if routes[0] = [1, 5, 7], this means that the 0th bus travels in the sequence 1 -> 5 -> 7 -> 1 -> 5 -> 7 -> 1 -> ... forever.
//
//
// You will start at the bus stop source (You are not on any bus initially), and you want to go to the bus stop target. You can travel between bus stops by buses only.
//
// Return the least number of buses you must take to travel from source to target. Return -1 if it is not possible.
//
// Example:
// Input: routes = [[1,2,7],[3,6,7]], source = 1, target = 6
// Output: 2
// Explanation: The best strategy is take the first bus to the bus stop 7, then take the second bus to the bus stop 6.
//
// Constraints:
// 1 <= routes.length <= 500.
// 	1 <= routes[i].length <= 105
// 	All the values of routes[i] are unique.
// 	sum(routes[i].length) <= 105
// 	0 <= routes[i][j] < 106
// 	0 <= source, target < 106
//
// Helpful references (internal KB):
// - Breadth-first search (graph, queue, array, bfs)
//   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes level by level. It is also suitable for problems requiring traversal of all nodes at a specific distance from a source.
//   • Idea: Breadth-first search systematically explores a graph level by level, ensuring that all nodes at distance k are visited before any nodes at distance k+1. It finds the shortest path in terms of number of edges for unweighted graphs in O(V + E) time.
//   • Invariants: All nodes currently in the queue have been discovered and marked, but their adjacent nodes have not yet been fully explored.; For any node v marked as visited, distTo[v] stores the shortest path length from the source s to v.
//   • Tips: Use a queue to manage nodes to visit.; Mark nodes as visited to prevent cycles and redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect paths.; Not handling disconnected graphs correctly.
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
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

int numBusesToDestination(int** routes, int routesSize, int* routesColSize, int source, int target) {
    if (source == target) return 0;

    /* Map from stop to list of buses */
    #define MAX_STOP 1000000
    int *stopToBuses[MAX_STOP];
    int stopBusCounts[MAX_STOP];
    memset(stopToBuses, 0, sizeof(stopToBuses));
    memset(stopBusCounts, 0, sizeof(stopBusCounts));

    for (int bus = 0; bus < routesSize; ++bus) {
        for (int j = 0; j < routesColSize[bus]; ++j) {
            int stop = routes[bus][j];
            int count = stopBusCounts[stop];
            stopToBuses[stop] = (int*)realloc(stopToBuses[stop], (count + 1) * sizeof(int));
            stopToBuses[stop][count] = bus;
            stopBusCounts[stop]++;
        }
    }

    /* BFS */
    int visitedBuses[routesSize];
    memset(visitedBuses, 0, sizeof(visitedBuses));
    int queue[MAX_STOP];
    int front = 0, back = 0;
    queue[back++] = source;
    int busesTaken = 0;

    while (front < back) {
        int levelSize = back - front;
        busesTaken++;
        for (int i = 0; i < levelSize; ++i) {
            int currStop = queue[front++];
            for (int j = 0; j < stopBusCounts[currStop]; ++j) {
                int bus = stopToBuses[currStop][j];
                if (visitedBuses[bus]) continue;
                visitedBuses[bus] = 1;
                for (int k = 0; k < routesColSize[bus]; ++k) {
                    int nextStop = routes[bus][k];
                    if (nextStop == target) {
                        /* Free allocated memory */
                        for (int s = 0; s < MAX_STOP; ++s) {
                            free(stopToBuses[s]);
                        }
                        return busesTaken;
                    }
                    queue[back++] = nextStop;
                }
            }
        }
    }

    /* Free allocated memory */
    for (int s = 0; s < MAX_STOP; ++s) {
        free(stopToBuses[s]);
    }
    return -1;      
}
