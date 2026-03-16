// Source: https://leetcode.com/problems/path-crossing/   |   Difficulty: Easy
//
// Problem Description:
// Given a string path, where path[i] = 'N', 'S', 'E' or 'W', each representing moving one unit north, south, east, or west, respectively. You start at the origin (0, 0) on a 2D plane and walk on the path specified by path.
//
// Return true if the path crosses itself at any point, that is, if at any time you are on a location you have previously visited. Return false otherwise.
//
// Example:
// Input: path = "NES"
// Output: false 
// Explanation: Notice that the path doesn't cross any point more than once.
//
// Constraints:
// 1 <= path.length <= 104
// 	path[i] is either 'N', 'S', 'E', or 'W'.
//
// Helpful references (internal KB):
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Finding the Eulerian path in O(M) (graph, enumeration, bfs)
//   • When to use: Use when the problem requires visiting every edge in a graph exactly once, either starting and ending at the same vertex (cycle) or at two different vertices (path).
//   • Idea: An Eulerian path is a trail in a graph which visits every edge exactly once. An Eulerian cycle is an Eulerian path that starts and ends on the same vertex.
//   • Invariants: Every edge in the graph is considered exactly once for inclusion in the path.; The current path segment always forms a valid trail in the graph.
//   • Tips: Check vertex degrees to determine path/cycle existence before attempting to find it.; For an Eulerian path, start traversal from one of the two odd-degree vertices.
//   • Pitfalls: Incorrectly handling multi-edges or self-loops can lead to errors in degree calculation or traversal.; Failing to check graph connectivity can result in incomplete paths or infinite loops.
// - Check if point belongs to the convex pol (geometry, array, binary-search)
//   • When to use: This algorithm is used to efficiently determine if a given query point lies inside or on the boundary of a convex polygon, especially when many queries are performed on the same polygon.
//   • Idea: The core idea is to decompose the convex polygon into triangles originating from a reference vertex. Binary search is then used to find the specific triangle that could contain the query point, followed by a point-in-triangle check.
//   • Invariants: The reference point p_0 is the lexicographically smallest vertex of the polygon.; All polygon vertices p_1, ..., p_n are ordered counter-clockwise by polar angle around p_0.
//   • Tips: Choose a consistent reference point, typically the lexicographically smallest vertex, to simplify angular sorting.; Ensure polygon vertices are ordered (e.g., counter-clockwise) relative to the reference point for correct binary search behavior.
//   • Pitfalls: Floating point precision errors can lead to incorrect results for collinear points or boundary checks; prefer integer arithmetic with cross products.; Incorrectly handling boundary conditions (points exactly on an edge or vertex) can lead to false negatives or positives.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    bool isPathCrossing(string path) {
        unordered_set<string> visited;
        int x = 0, y = 0;
        visited.insert("0,0");

        for (char c : path) {
            if (c == 'N') y++;
            else if (c == 'S') y--;
            else if (c == 'E') x++;
            else if (c == 'W') x--;

            string pos = to_string(x) + "," + to_string(y);
            if (visited.count(pos)) return true;
            visited.insert(pos);
        }

        return false;           
    }
};
