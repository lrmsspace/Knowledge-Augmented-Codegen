// Source: https://leetcode.com/problems/furthest-building-you-can-reach/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array heights representing the heights of buildings, some bricks, and some ladders.
//
// You start your journey from building 0 and move to the next building by possibly using bricks or ladders.
//
// While moving from building i to building i+1 (0-indexed),
//
//
// 	If the current building's height is greater than or equal to the next building's height, you do not need a ladder or bricks.
// 	If the current building's height is less than the next building's height, you can either use one ladder or (h[i+1] - h[i]) bricks.
//
//
// Return the furthest building index (0-indexed) you can reach if you use the given ladders and bricks optimally.
//
// Example:
// Input: heights = [4,2,7,6,9,14,12], bricks = 5, ladders = 1
// Output: 4
// Explanation: Starting at building 0, you can follow these steps:
// - Go to building 1 without using ladders nor bricks since 4 >= 2.
// - Go to building 2 using 5 bricks. You must use either bricks or ladders because 2 < 7.
// - Go to building 3 without using ladders nor bricks since 7 >= 6.
// - Go to building 4 using your only ladder. You must use either bricks or ladders because 6 < 9.
// It is impossible to go beyond building 4 because you do not have any more bricks or ladders.
//
// Constraints:
// 1 <= heights.length <= 105
// 	1 <= heights[i] <= 106
// 	0 <= bricks <= 109
// 	0 <= ladders <= heights.length
//
// Helpful references (internal KB):
// - kth-largest-element-in-an-array (heap, array, heap-select)
//   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
//   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
//   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
//   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
//   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
// - Maximum flow - Push-relabel method improved (graph, array, greedy, bfs)
//   • When to use: Use this for maximum flow problems on graphs where an optimized push-relabel approach is required. It improves performance by prioritizing vertices with the greatest height for push and relabel operations.
//   • Idea: This algorithm is an optimized variant of the push-relabel maximum flow method, which improves efficiency by always selecting the vertex with the greatest height that has excess flow. This specific vertex selection strategy leads to a better theoretical time complexity, typically O(V^2 * sqrt(E)) or O(V^3) depending on implementation details.
//   • Invariants: For any edge (u, v) in the residual graph, h(u) <= h(v) + 1.; The total excess flow in the network is always non-negative.
//   • Tips: Always select the active vertex with the highest current height.; Maintain a data structure (e.g., buckets or lists) to quickly find highest-height vertices.
//   • Pitfalls: Incorrectly managing the list of highest-height vertices.; Failing to update residual capacities after a push operation.
// - Breadth-first search (graph, deque, array, 01-bfs)
//   • When to use: When finding the shortest path in a graph where edge weights are restricted to 0 or 1, or when minimizing operations where some operations are 'free' (cost 0) and others have a unit cost (cost 1).
//   • Idea: A graph traversal algorithm that finds the shortest path from a source to all reachable nodes in a graph where edge weights are either 0 or 1. It uses a deque to prioritize 0-cost edges, achieving an optimal O(V + E) time complexity.
//   • Invariants: Nodes are added to the front of the deque if the edge weight is 0, and to the back if 1.; The distance `dist[u]` for any node `u` in the deque is either `k` or `k+1` for some integer `k`.
//   • Tips: Use a deque: push 0-cost edges to the front, 1-cost edges to the back.; Mark nodes visited to avoid cycles and redundant processing.
//   • Pitfalls: Incorrectly handling visited states can lead to infinite loops or incorrect paths.; Forgetting to initialize distances properly before starting the traversal.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int furthestBuilding(int* heights, int heightsSize, int bricks, int ladders) {
    // Min-heap to store the largest 'ladders' number of climbs
    int *minHeap = (int *)malloc(sizeof(int) * (ladders + 1));
    int heapSize = 0;

    for (int i = 0; i < heightsSize - 1; i++) {
        int diff = heights[i + 1] - heights[i];
        if (diff > 0) {
            // Add the climb to the min-heap
            minHeap[heapSize++] = diff;
            // Bubble up
            int idx = heapSize - 1;
            while (idx > 0) {
                int parent = (idx - 1) / 2;
                if (minHeap[parent] <= minHeap[idx]) break;
                int temp = minHeap[parent];
                minHeap[parent] = minHeap[idx];
                minHeap[idx] = temp;
                idx = parent;
            }

            // If we exceed the number of ladders, use bricks for the smallest climb
            if (heapSize > ladders) {
                int smallestClimb = minHeap[0];
                bricks -= smallestClimb;

                // Remove the smallest climb from the heap
                minHeap[0] = minHeap[--heapSize];
                // Bubble down
                idx = 0;
                while (true) {
                    int left = 2 * idx + 1;
                    int right = 2 * idx + 2;
                    int smallest = idx;

                    if (left < heapSize && minHeap[left] < minHeap[smallest]) {
                        smallest = left;
                    }
                    if (right < heapSize && minHeap[right] < minHeap[smallest]) {
                        smallest = right;
                    }
                    if (smallest == idx) break;

                    int temp = minHeap[idx];
                    minHeap[idx] = minHeap[smallest];
                    minHeap[smallest] = temp;
                    idx = smallest;
                }
            }

            // If we run out of bricks, return the current building index
            if (bricks < 0) {
                free(minHeap);
                return i;
            }
        }
    }

    free(minHeap);
    return heightsSize - 1;     
}
