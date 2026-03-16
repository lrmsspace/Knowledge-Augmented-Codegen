// Source: https://leetcode.com/problems/shortest-distance-to-a-character/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s and a character c that occurs in s, return an array of integers answer where answer.length == s.length and answer[i] is the distance from index i to the closest occurrence of character c in s.
//
// The distance between two indices i and j is abs(i - j), where abs is the absolute value function.
//
// Example:
// Input: s = "loveleetcode", c = "e"
// Output: [3,2,1,0,1,0,0,1,2,2,1,0]
// Explanation: The character 'e' appears at indices 3, 5, 6, and 11 (0-indexed).
// The closest occurrence of 'e' for index 0 is at index 3, so the distance is abs(0 - 3) = 3.
// The closest occurrence of 'e' for index 1 is at index 3, so the distance is abs(1 - 3) = 2.
// For index 4, there is a tie between the 'e' at index 3 and the 'e' at index 5, but the distance is still the same: abs(4 - 3) == abs(4 - 5) = 1.
// The closest occurrence of 'e' for index 8 is at index 6, so the distance is abs(8 - 6) = 2.
//
// Constraints:
// 1 <= s.length <= 104
// 	s[i] and c are lowercase English letters.
// 	It is guaranteed that c occurs at least once in s.
//
// Helpful references (internal KB):
// - Suffix Array (array, string, simulation, two-pointers)
//   • When to use: Use when needing to efficiently compare substrings, find all occurrences of a pattern, or determine lexicographical order among suffixes within a string.
//   • Idea: A Suffix Array stores sorted suffixes of a string, enabling fast substring comparisons and pattern searching. Construction typically takes O(N log N) time, with comparisons often O(1) after preprocessing.
//   • Invariants: The suffix array `p` contains all suffixes of the string `s` sorted lexicographically.; During construction, equivalence classes `c` correctly group suffixes that are identical up to a certain length `2^k`.
//   • Tips: Precompute log values for efficient block length calculation.; Utilize equivalence classes for O(1) comparison of power-of-two length substrings.
//   • Pitfalls: Complexity of suffix array construction can be tricky (e.g., O(N log N) vs O(N)).; Off-by-one errors when calculating block indices or lengths.
// - Circle-Line Intersection (geometry, number, enumeration, simulation)
//   • When to use: Use this algorithm to find the intersection points between a circle and a line, especially when numerical stability is a concern. It efficiently determines zero, one, or two intersection points.
//   • Idea: This algorithm finds the intersection points of a circle and a line by using geometric properties like distances and vectors, avoiding direct algebraic system solving. It determines zero, one, or two intersection points in constant time, O(1).
//   • Invariants: The distance from the origin to the line, d0, is always correctly calculated as |C| / sqrt(A^2 + B^2).; The point (x0, y0) is always the closest point on the line Ax+By+C=0 to the origin (0,0).
//   • Tips: Translate the circle to the origin for simplified calculations, adjusting the line equation accordingly.; Use the distance from the origin to the line to quickly determine the number of intersection points.
//   • Pitfalls: Floating point precision errors can accumulate, especially with very small or large coordinates.; Incorrectly handling edge cases where the line is tangent to the circle or passes through the origin.
// - Finding the nearest pair of points (geometry, array, divide-and-conquer, merge-sort, two-pointers)
//   • When to use: Use this when finding the pair of points with the minimum Euclidean distance in a 2D plane. It efficiently handles large datasets by recursively dividing the problem and merging results.
//   • Idea: It finds the closest pair of points in a 2D plane by recursively dividing the set, solving subproblems, and merging results in O(N log N) time. The merge step efficiently handles cross-boundary pairs within a narrow strip.
//   • Invariants: The minimum distance returned by a recursive call is the true minimum for its input subset.; All points in the left subproblem have x-coordinates less than or equal to the median x-coordinate.
//   • Tips: Pre-sort points by x-coordinate to enable efficient splitting.; Maintain a y-sorted list of points for efficient merging of the strip.
//   • Pitfalls: An inefficient merge step can degrade complexity from O(N log N) to O(N^2).; Failing to correctly identify and process cross-boundary pairs.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* shortestToChar(char* s, char c, int* returnSize) {
    int n = 0;
    while (s[n] != '\0') {
        n++;
    }

    int* answer = (int*)malloc(n * sizeof(int));
    *returnSize = n;

    int prev = -n;  // Initialize to a large negative value
    for (int i = 0; i < n; i++) {
        if (s[i] == c) {
            prev = i;
        }
        answer[i] = i - prev;
    }

    prev = 2 * n;  // Initialize to a large positive value
    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == c) {
            prev = i;
        }
        if (prev - i < answer[i]) {
            answer[i] = prev - i;
        }
    }

    return answer;      
}
