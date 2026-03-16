// Source: https://leetcode.com/problems/rings-and-rods/   |   Difficulty: Easy
//
// Problem Description:
// There are n rings and each ring is either red, green, or blue. The rings are distributed across ten rods labeled from 0 to 9.
//
// You are given a string rings of length 2n that describes the n rings that are placed onto the rods. Every two characters in rings forms a color-position pair that is used to describe each ring where:
//
//
// 	The first character of the ith pair denotes the ith ring's color ('R', 'G', 'B').
// 	The second character of the ith pair denotes the rod that the ith ring is placed on ('0' to '9').
//
//
// For example, "R3G2B1" describes n == 3 rings: a red ring placed onto the rod labeled 3, a green ring placed onto the rod labeled 2, and a blue ring placed onto the rod labeled 1.
//
// Return the number of rods that have all three colors of rings on them.
//
// Example:
// Input: rings = "B0B6G0R6R0R6G9"
// Output: 1
// Explanation: 
// - The rod labeled 0 holds 3 rings with all colors: red, green, and blue.
// - The rod labeled 6 holds 3 rings, but it only has red and blue.
// - The rod labeled 9 holds only a green ring.
// Thus, the number of rods with all three colors is 1.
//
// Constraints:
// rings.length == 2 * n
// 	1 <= n <= 100
// 	rings[i] where i is even is either 'R', 'G', or 'B' (0-indexed).
// 	rings[i] where i is odd is a digit from '0' to '9' (0-indexed).
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Convex Hull construction (geometry, array, enumeration)
//   • When to use: Use when you need to find the smallest convex polygon that encloses a given set of points in a plane. It is fundamental for various geometric algorithms and optimization problems.
//   • Idea: Convex hull construction identifies the subset of points that form the vertices of the smallest convex polygon containing all given points. Common algorithms achieve this in O(N log N) time complexity.
//   • Invariants: The sequence of points currently forming the hull maintains a convex property.; All points considered up to the current iteration are either part of the hull or lie within the polygon defined by the hull.
//   • Tips: Sort points by X-coordinate (and Y for ties) as a common preprocessing step.; Consider algorithms like Graham Scan or Monotone Chain for efficiency.
//   • Pitfalls: Floating point precision issues can lead to incorrect orientation calculations.; Incorrectly handling collinear points can result in non-minimal hulls or errors.
// - Suffix Automaton (graph, string, simulation)
//   • When to use: Use when you need to efficiently represent all distinct substrings of a string, or perform various string operations like counting unique substrings, finding occurrences, or string matching in an online fashion.
//   • Idea: A suffix automaton is a powerful data structure that represents all distinct substrings of a given string in a compact form, typically as a Directed Acyclic Word Graph (DAWG). It can be constructed in linear time O(N) and space O(N) for a string of length N.
//   • Invariants: Each state in the automaton represents a set of substrings that share the same end-positions in the original string.; For any state `v`, `len(v)` is the length of the longest string represented by `v`.
//   • Tips: Understand the properties of `len` (length of the longest string in a state) and `link` (suffix link to the longest proper suffix).; The construction is online, processing characters one by one from left to right.
//   • Pitfalls: Incorrectly handling the `link` updates, especially when cloning states during construction.; Forgetting to update the `last` pointer after each character addition step.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int countPoints(String rings) {
        // Array to track colors on each rod; index 0-9 for rods, bits for colors R=1, G=2, B=4
        int[] rods = new int[10];
        
        // Process each pair in the rings string
        for (int i = 0; i < rings.length(); i += 2) {
            char color = rings.charAt(i);
            int rodIndex = rings.charAt(i + 1) - '0';
            
            // Update the rod's color bitmask
            switch (color) {
                case 'R':
                    rods[rodIndex] |= 1; // Set bit for Red
                    break;
                case 'G':
                    rods[rodIndex] |= 2; // Set bit for Green
                    break;
                case 'B':
                    rods[rodIndex] |= 4; // Set bit for Blue
                    break;
            }
        }
        
        // Count rods that have all three colors (bitmask 7)
        int count = 0;
        for (int rod : rods) {
            if (rod == 7) {
                count++;
            }
        }
        
        return count;           
    }
}
