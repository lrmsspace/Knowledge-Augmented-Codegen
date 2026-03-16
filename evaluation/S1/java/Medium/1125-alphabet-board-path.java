// Source: https://leetcode.com/problems/alphabet-board-path/   |   Difficulty: Medium
//
// Problem Description:
// On an alphabet board, we start at position (0, 0), corresponding to character board[0][0].
//
// Here, board = ["abcde", "fghij", "klmno", "pqrst", "uvwxy", "z"], as shown in the diagram below.
//
//
//
// We may make the following moves:
//
//
// 	'U' moves our position up one row, if the position exists on the board;
// 	'D' moves our position down one row, if the position exists on the board;
// 	'L' moves our position left one column, if the position exists on the board;
// 	'R' moves our position right one column, if the position exists on the board;
// 	'!' adds the character board[r][c] at our current position (r, c) to the answer.
//
//
// (Here, the only positions that exist on the board are positions with letters on them.)
//
// Return a sequence of moves that makes our answer equal to target in the minimum number of moves.  You may return any path that does so.
//
// Example:
// Input: target = "leet"
// Output: "DDR!UURRR!!DDD!"
//
// Constraints:
// 1 <= target.length <= 100
// 	target consists only of English lowercase letters.
//
// Helpful references (internal KB):
// - Finding repetitions (string, array, z-function, enumeration)
//   • When to use: This algorithm efficiently finds all repetitions (periodic substrings) within a given string by combining divide-and-conquer with the Z-function. It is particularly useful for identifying overlapping or crossing periodic patterns.
//   • Idea: The Main-Lorentz algorithm finds all repetitions in a string by recursively splitting it into halves and identifying 'crossing repetitions' using the Z-function. This approach achieves an optimal O(N log N) time complexity.
//   • Invariants: For any fixed `cntr` position, all identified crossing repetitions have a total length of $2 	imes (|u| - cntr)$.; The segment $u[cntr - k_1 	ext{ to } cntr - 1]$ is identical to $u[|u| - k_1 	ext{ to } |u| - 1]$.
//   • Tips: Employ divide-and-conquer to break the problem into subproblems for repetitions within halves and crossing repetitions.; Utilize the Z-function to compute $k_1$ and $k_2$ values in O(1) for each `cntr` position, speeding up crossing repetition detection.
//   • Pitfalls: Correctly identifying and defining 'crossing repetitions' is the most intricate part of the algorithm.; Careful implementation of the Z-function for both the original and reversed string segments is crucial.
// - Suffix Automaton (graph, string, simulation)
//   • When to use: Use to efficiently represent all suffixes of a string in a compressed form, ideal for various string problems like pattern matching or counting distinct substrings.
//   • Idea: A suffix automaton is a minimal Deterministic Finite Automaton (DFA) that accepts all suffixes of a given string, offering O(N) time construction and O(N) memory complexity.
//   • Invariants: Every state in the automaton represents a set of substrings of the original string.; Each state's longest path from the initial state corresponds to its longest string.
//   • Tips: Understand the definition of states and transitions, and their relationship to substrings.; Leverage its linear time and space complexity for efficient string processing on large inputs.
//   • Pitfalls: The construction algorithm can be complex and challenging to implement correctly.; Debugging state transitions, suffix links, and their properties requires careful attention.
// - Convex Hull construction (geometry, array, enumeration)
//   • When to use: Use when you need to find the smallest convex polygon that encloses a given set of points in a plane. It is fundamental for various geometric algorithms and optimization problems.
//   • Idea: Convex hull construction identifies the subset of points that form the vertices of the smallest convex polygon containing all given points. Common algorithms achieve this in O(N log N) time complexity.
//   • Invariants: The sequence of points currently forming the hull maintains a convex property.; All points considered up to the current iteration are either part of the hull or lie within the polygon defined by the hull.
//   • Tips: Sort points by X-coordinate (and Y for ties) as a common preprocessing step.; Consider algorithms like Graham Scan or Monotone Chain for efficiency.
//   • Pitfalls: Floating point precision issues can lead to incorrect orientation calculations.; Incorrectly handling collinear points can result in non-minimal hulls or errors.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public String alphabetBoardPath(String target) {
        StringBuilder path = new StringBuilder();
        int currRow = 0, currCol = 0;

        for (char ch : target.toCharArray()) {
            int targetRow = (ch - 'a') / 5;
            int targetCol = (ch - 'a') % 5;

            // Special case for 'z' to avoid invalid moves
            if (ch == 'z') {
                // Move vertically first
                while (currRow < targetRow) {
                    path.append('D');
                    currRow++;
                }
                while (currCol > targetCol) {
                    path.append('L');
                    currCol--;
                }
                while (currCol < targetCol) {
                    path.append('R');
                    currCol++;
                }
            } else {
                // Move horizontally first
                while (currCol > targetCol) {
                    path.append('L');
                    currCol--;
                }
                while (currCol < targetCol) {
                    path.append('R');
                    currCol++;
                }
                while (currRow > targetRow) {
                    path.append('U');
                    currRow--;
                }
                while (currRow < targetRow) {
                    path.append('D');
                    currRow++;
                }
            }

            path.append('!');
        }

        return path.toString();         
    }
}
