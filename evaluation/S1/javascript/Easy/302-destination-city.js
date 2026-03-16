// Source: https://leetcode.com/problems/destination-city/   |   Difficulty: Easy
//
// Problem Description:
// You are given the array paths, where paths[i] = [cityAi, cityBi] means there exists a direct path going from cityAi to cityBi. Return the destination city, that is, the city without any path outgoing to another city.
//
// It is guaranteed that the graph of paths forms a line without any loop, therefore, there will be exactly one destination city.
//
// Example:
// Input: paths = [["London","New York"],["New York","Lima"],["Lima","Sao Paulo"]]
// Output: "Sao Paulo" 
// Explanation: Starting at "London" city you will reach "Sao Paulo" city which is the destination city. Your trip consist of: "London" -> "New York" -> "Lima" -> "Sao Paulo".
//
// Constraints:
// 1 <= paths.length <= 100
// 	paths[i].length == 2
// 	1 <= cityAi.length, cityBi.length <= 10
// 	cityAi != cityBi
// 	All strings consist of lowercase and uppercase English letters and the space character.
//
// Helpful references (internal KB):
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
// - Finding the Eulerian path in O(M) (graph, eulerian-circuit, dfs)
//   • When to use: Use when you need to find a path or cycle that traverses every edge exactly once in a given graph. It's applicable when specific vertex degree conditions are met for path or cycle existence.
//   • Idea: This algorithm constructs an Eulerian path or cycle by first verifying vertex degree conditions and graph connectivity, then performing a recursive DFS-like traversal to build the path. It achieves a time complexity of O(M), where M is the number of edges.
//   • Invariants: Every edge in the constructed path has been traversed exactly once.; All edges incident to the current vertex have been explored or are part of the remaining graph.
//   • Tips: Verify graph connectivity, ignoring isolated vertices.; For an Eulerian path, ensure exactly two vertices have odd degrees.
//   • Pitfalls: Failing to check graph connectivity before starting.; Incorrectly counting odd degree vertices for path vs. cycle.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string[][]} paths
 * @return {string}
 */
var destCity = function(paths) {
    const outgoingCities = new Set();
    for (const [from, to] of paths) {
        outgoingCities.add(from);
    }
    for (const [from, to] of paths) {
        if (!outgoingCities.has(to)) {
            return to;
        }
    }
    return "";
};
