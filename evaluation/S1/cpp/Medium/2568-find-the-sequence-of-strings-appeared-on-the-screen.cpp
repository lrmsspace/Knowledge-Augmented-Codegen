// Source: https://leetcode.com/problems/find-the-sequence-of-strings-appeared-on-the-screen/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string target.
//
// Alice is going to type target on her computer using a special keyboard that has only two keys:
//
//
// 	Key 1 appends the character "a" to the string on the screen.
// 	Key 2 changes the last character of the string on the screen to its next character in the English alphabet. For example, "c" changes to "d" and "z" changes to "a".
//
//
// Note that initially there is an empty string "" on the screen, so she can only press key 1.
//
// Return a list of all strings that appear on the screen as Alice types target, in the order they appear, using the minimum key presses.
//
// Example:
// Input: target = "abc"
//
// Output: ["a","aa","ab","aba","abb","abc"]
//
// Explanation:
//
// The sequence of key presses done by Alice are:
//
//
// 	Press key 1, and the string on the screen becomes "a".
// 	Press key 1, and the string on the screen becomes "aa".
// 	Press key 2, and the string on the screen becomes "ab".
// 	Press key 1, and the string on the screen becomes "aba".
// 	Press key 2, and the string on the screen becomes "abb".
// 	Press key 2, and the string on the screen becomes "abc".
//
// Constraints:
// 1 <= target.length <= 400
// 	target consists only of lowercase English letters.
//
// Helpful references (internal KB):
// - Suffix Automaton (graph, string, simulation)
//   • When to use: Use when you need to efficiently represent all distinct substrings of a string, or perform various string operations like counting unique substrings, finding occurrences, or string matching in an online fashion.
//   • Idea: A suffix automaton is a powerful data structure that represents all distinct substrings of a given string in a compact form, typically as a Directed Acyclic Word Graph (DAWG). It can be constructed in linear time O(N) and space O(N) for a string of length N.
//   • Invariants: Each state in the automaton represents a set of substrings that share the same end-positions in the original string.; For any state `v`, `len(v)` is the length of the longest string represented by `v`.
//   • Tips: Understand the properties of `len` (length of the longest string in a state) and `link` (suffix link to the longest proper suffix).; The construction is online, processing characters one by one from left to right.
//   • Pitfalls: Incorrectly handling the `link` updates, especially when cloning states during construction.; Forgetting to update the `last` pointer after each character addition step.
// - Scheduling jobs on two machines (array, greedy)
//   • When to use: Use when optimizing the order of a sequence of tasks on two machines to minimize total idle time or makespan. It is typically applied when a greedy exchange argument can prove optimality.
//   • Idea: This algorithm determines an optimal sequence for jobs on two machines by iteratively applying a greedy choice, often proven optimal via an exchange argument. It typically achieves an optimal solution in polynomial time, commonly O(N log N) or O(N^2).
//   • Invariants: The relative order of jobs already placed in the schedule is optimal.; The total idle time for the current prefix of scheduled jobs is correctly calculated.
//   • Tips: Focus on the local effect of swapping adjacent elements to derive the greedy criterion.; Identify a metric (e.g., total idle time or makespan) that changes predictably with swaps.
//   • Pitfalls: The greedy choice might not be globally optimal for problems with more than two machines.; Incorrectly defining the cost function for idle time or makespan can lead to suboptimal solutions.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<string> stringSequence(string target) {
        vector<string> result;
        string current = "";
        for (char ch : target) {
            // Append 'a' to reach the length of the current character
            while (current.length() < result.size() + 1) {
                current += 'a';
                result.push_back(current);
            }
            // Change the last character to the target character
            while (current.back() < ch) {
                current.back()++;
                result.push_back(current);
            }
        }
        return result;          
    }
};
