// Source: https://leetcode.com/problems/maximize-subarrays-after-removing-one-conflicting-pair/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n which represents an array nums containing the numbers from 1 to n in order. Additionally, you are given a 2D array conflictingPairs, where conflictingPairs[i] = [a, b] indicates that a and b form a conflicting pair.
//
// Remove exactly one element from conflictingPairs. Afterward, count the number of non-empty subarrays of nums which do not contain both a and b for any remaining conflicting pair [a, b].
//
// Return the maximum number of subarrays possible after removing exactly one conflicting pair.
//
// Example:
// Input: n = 4, conflictingPairs = [[2,3],[1,4]]
//
// Output: 9
//
// Explanation:
//
//
// 	Remove [2, 3] from conflictingPairs. Now, conflictingPairs = [[1, 4]].
// 	There are 9 subarrays in nums where [1, 4] do not appear together. They are [1], [2], [3], [4], [1, 2], [2, 3], [3, 4], [1, 2, 3] and [2, 3, 4].
// 	The maximum number of subarrays we can achieve after removing one element from conflictingPairs is 9.
//
// Constraints:
// 2 <= n <= 105
// 	1 <= conflictingPairs.length <= 2 * n
// 	conflictingPairs[i].length == 2
// 	1 <= conflictingPairs[i][j] <= n
// 	conflictingPairs[i][0] != conflictingPairs[i][1]
//
// Helpful references (internal KB):
// - The Inclusion-Exclusion Principle (matrix, array, dp-2d, counting)
//   • When to use: Use when needing to count elements satisfying "at least one" of several properties, especially when direct counting is complicated by overlapping sets. It's also applicable for counting elements satisfying "none" of the properties by subtracting from the total.
//   • Idea: The Inclusion-Exclusion Principle is a combinatorial method to determine the size of the union of multiple finite sets. It works by summing the sizes of individual sets, subtracting the sizes of all pairwise intersections, adding back the sizes of all three-way intersections, and so on, with alternating signs.
//   • Invariants: The count for any element satisfying `k` properties is adjusted to be exactly 1 in the final sum.; Each term in the sum corresponds to the size of an intersection of a distinct subset of properties.
//   • Tips: Clearly define the universe and the properties (sets) you are interested in.; Systematically list all combinations of properties for intersection terms.
//   • Pitfalls: Incorrectly identifying or defining the properties or sets.; Missing certain intersection terms or double-counting them.
// - Finding Bridges Online (graph, ds, union-find, counting)
//   • When to use: Use when edges are added one by one to an initially empty graph and you need to efficiently track the number of bridges or 2-edge-connected components after each addition.
//   • Idea: This algorithm dynamically maintains the number of bridges in an undirected graph as edges are added incrementally. It leverages a Disjoint Set Union (DSU) data structure to achieve an amortized time complexity of O((N+M) log N).
//   • Invariants: Each DSU set represents a 2-edge-connected component or a collection of such components connected by bridges.; The total count of bridges accurately reflects edges whose removal increases connected components.
//   • Tips: Understand the properties of 2-edge-connected components and how they relate to bridges.; Carefully manage DSU operations, including path compression and union by rank/size, for optimal performance.
//   • Pitfalls: Incorrectly updating the bridge count after an edge addition, especially when cycles are formed.; Inefficient DSU operations leading to a higher than expected time complexity.
// - Finding area of simple polygon in O(N) (geometry, array, enumeration, prefix-sum)
//   • When to use: Use when calculating the area of a simple polygon given its vertices in order. It is efficient for both convex and non-convex polygons.
//   • Idea: This algorithm calculates the area of a simple polygon by summing signed trapezoidal areas formed by each edge and the x-axis, or equivalently, using the shoelace formula. It achieves an optimal O(N) time complexity, where N is the number of vertices.
//   • Invariants: Vertices are processed sequentially in their given order, forming edges.; The running sum `current_sum` accumulates the signed contribution from each edge processed so far.
//   • Tips: Ensure vertices are provided in a consistent order (clockwise or counter-clockwise).; Use a data type with sufficient range (e.g., long long or double) for intermediate sums to prevent overflow.
//   • Pitfalls: Incorrect vertex order will result in an incorrect signed area or even zero.; Integer overflow can occur if coordinates are large and sums exceed standard integer limits.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    long long maxSubarrays(int n, vector<vector<int>>& conflictingPairs) {
        vector<vector<int>> graph(n + 1);
        for (const auto& pair : conflictingPairs) {
            int a = pair[0], b = pair[1];
            graph[a].push_back(b);
            graph[b].push_back(a);
        }

        vector<bool> visited(n + 1, false);
        vector<int> componentSizes;

        function<void(int, int&)> dfs = [&](int node, int& size) {
            visited[node] = true;
            size++;
            for (int neighbor : graph[node]) {
                if (!visited[neighbor]) {
                    dfs(neighbor, size);
                }
            }
        };

        for (int i = 1; i <= n; ++i) {
            if (!visited[i]) {
                int size = 0;
                dfs(i, size);
                componentSizes.push_back(size);
            }
        }

        long long totalSubarrays = static_cast<long long>(n) * (n + 1) / 2;
        long long maxSubarraysAfterRemoval = 0;

        for (int size : componentSizes) {
            long long subarraysInComponent = static_cast<long long>(size) * (size + 1) / 2;
            maxSubarraysAfterRemoval += subarraysInComponent;
        }

        return totalSubarrays - maxSubarraysAfterRemoval;           
    }
};
