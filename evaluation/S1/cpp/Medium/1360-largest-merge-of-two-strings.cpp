// Source: https://leetcode.com/problems/largest-merge-of-two-strings/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings word1 and word2. You want to construct a string merge in the following way: while either word1 or word2 are non-empty, choose one of the following options:
//
//
// 	If word1 is non-empty, append the first character in word1 to merge and delete it from word1.
//
// 	
// 		For example, if word1 = "abc" and merge = "dv", then after choosing this operation, word1 = "bc" and merge = "dva".
// 	
// 	
// 	If word2 is non-empty, append the first character in word2 to merge and delete it from word2.
// 	
// 		For example, if word2 = "abc" and merge = "", then after choosing this operation, word2 = "bc" and merge = "a".
// 	
// 	
//
//
// Return the lexicographically largest merge you can construct.
//
// A string a is lexicographically larger than a string b (of the same length) if in the first position where a and b differ, a has a character strictly larger than the corresponding character in b. For example, "abcd" is lexicographically larger than "abcc" because the first position they differ is at the fourth character, and d is greater than c.
//
// Example:
// Input: word1 = "cabaa", word2 = "bcaaa"
// Output: "cbcabaaaaa"
// Explanation: One way to get the lexicographically largest merge is:
// - Take from word1: merge = "c", word1 = "abaa", word2 = "bcaaa"
// - Take from word2: merge = "cb", word1 = "abaa", word2 = "caaa"
// - Take from word2: merge = "cbc", word1 = "abaa", word2 = "aaa"
// - Take from word1: merge = "cbca", word1 = "baa", word2 = "aaa"
// - Take from word1: merge = "cbcab", word1 = "aa", word2 = "aaa"
// - Append the remaining 5 a's from word1 and word2 at the end of merge.
//
// Constraints:
// 1 <= word1.length, word2.length <= 3000
// 	word1 and word2 consist only of lowercase English letters.
//
// Helpful references (internal KB):
// - Lyndon factorization (string, greedy, two-pointers)
//   • When to use: Use this algorithm to decompose a string into a unique sequence of Lyndon words, which are lexicographically smallest among their cyclic shifts. It is also applicable for finding the smallest cyclic shift of a string.
//   • Idea: The Duval algorithm greedily factorizes a string into a sequence of Lyndon words by maintaining three pointers to manage processed, pre-simple, and untouched parts. It achieves this in O(N) time complexity.
//   • Invariants: The prefix s[0...i-1] always contains a valid Lyndon factorization.; The substring s[i...j-1] is always a pre-simple string.
//   • Tips: Thoroughly understand the definitions of 'simple string' and 'pre-simple string' to correctly apply the comparison logic.; The three pointers (i, j, k) are crucial; 'i' marks the start of the current pre-simple string, 'j' the start of the untouched part, and 'k' for comparison within the pre-simple string.
//   • Pitfalls: Incorrectly resetting the 'k' pointer when s[j] > s[k], which should point back to the beginning of the simple word within s2.; Misinterpreting the length of the simple string (j - k) when a factorization step occurs.
// - Finding the nearest pair of points (geometry, array, divide-and-conquer, merge-sort, two-pointers)
//   • When to use: Use this when finding the pair of points with the minimum Euclidean distance in a 2D plane. It efficiently handles large datasets by recursively dividing the problem and merging results.
//   • Idea: It finds the closest pair of points in a 2D plane by recursively dividing the set, solving subproblems, and merging results in O(N log N) time. The merge step efficiently handles cross-boundary pairs within a narrow strip.
//   • Invariants: The minimum distance returned by a recursive call is the true minimum for its input subset.; All points in the left subproblem have x-coordinates less than or equal to the median x-coordinate.
//   • Tips: Pre-sort points by x-coordinate to enable efficient splitting.; Maintain a y-sorted list of points for efficient merging of the strip.
//   • Pitfalls: An inefficient merge step can degrade complexity from O(N log N) to O(N^2).; Failing to correctly identify and process cross-boundary pairs.
// - Scheduling jobs on two machines (array, greedy)
//   • When to use: Use when optimizing the order of a sequence of tasks on two machines to minimize total idle time or makespan. It is typically applied when a greedy exchange argument can prove optimality.
//   • Idea: This algorithm determines an optimal sequence for jobs on two machines by iteratively applying a greedy choice, often proven optimal via an exchange argument. It typically achieves an optimal solution in polynomial time, commonly O(N log N) or O(N^2).
//   • Invariants: The relative order of jobs already placed in the schedule is optimal.; The total idle time for the current prefix of scheduled jobs is correctly calculated.
//   • Tips: Focus on the local effect of swapping adjacent elements to derive the greedy criterion.; Identify a metric (e.g., total idle time or makespan) that changes predictably with swaps.
//   • Pitfalls: The greedy choice might not be globally optimal for problems with more than two machines.; Incorrectly defining the cost function for idle time or makespan can lead to suboptimal solutions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    string largestMerge(string word1, string word2) {
        string merge;
        int i = 0, j = 0;
        int n1 = word1.size(), n2 = word2.size();
        while (i < n1 || j < n2) {
            if (i < n1 && j < n2) {
                // Both strings are non-empty, compare suffixes
                if (word1.compare(i, n1 - i, word2, j, n2 - j) > 0) {
                    merge.push_back(word1[i]);
                    i++;
                } else {
                    merge.push_back(word2[j]);
                    j++;
                }
            } else if (i < n1) {
                // Only word1 is non-empty
                merge.push_back(word1[i]);
                i++;
            } else {
                // Only word2 is non-empty
                merge.push_back(word2[j]);
                j++;
            }
        }
        return merge;           
    }
};
