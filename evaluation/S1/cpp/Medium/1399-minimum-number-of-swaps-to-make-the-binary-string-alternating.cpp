// Source: https://leetcode.com/problems/minimum-number-of-swaps-to-make-the-binary-string-alternating/   |   Difficulty: Medium
//
// Problem Description:
// Given a binary string s, return the minimum number of character swaps to make it alternating, or -1 if it is impossible.
//
// The string is called alternating if no two adjacent characters are equal. For example, the strings "010" and "1010" are alternating, while the string "0100" is not.
//
// Any two characters may be swapped, even if they are not adjacent.
//
// Example:
// Input: s = "111000"
// Output: 1
// Explanation: Swap positions 1 and 4: "111000" -> "101010"
// The string is now alternating.
//
// Constraints:
// 1 <= s.length <= 1000
// 	s[i] is either '0' or '1'.
//
// Helpful references (internal KB):
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Scheduling jobs on two machines (array, greedy)
//   • When to use: Use when optimizing the order of a sequence of tasks on two machines to minimize total idle time or makespan. It is typically applied when a greedy exchange argument can prove optimality.
//   • Idea: This algorithm determines an optimal sequence for jobs on two machines by iteratively applying a greedy choice, often proven optimal via an exchange argument. It typically achieves an optimal solution in polynomial time, commonly O(N log N) or O(N^2).
//   • Invariants: The relative order of jobs already placed in the schedule is optimal.; The total idle time for the current prefix of scheduled jobs is correctly calculated.
//   • Tips: Focus on the local effect of swapping adjacent elements to derive the greedy criterion.; Identify a metric (e.g., total idle time or makespan) that changes predictably with swaps.
//   • Pitfalls: The greedy choice might not be globally optimal for problems with more than two machines.; Incorrectly defining the cost function for idle time or makespan can lead to suboptimal solutions.
// - Suffix Automaton (graph, string, simulation)
//   • When to use: When needing to efficiently represent all substrings of a given string and perform various string operations like counting distinct substrings, finding occurrences, or checking for specific patterns. It provides a compact and powerful data structure for complex string problems.
//   • Idea: A Suffix Automaton is a minimal deterministic finite automaton that recognizes all suffixes of a given string. It compactly represents all substrings of the string, with each state corresponding to an endpos-equivalence class, and can be constructed in linear time O(N).
//   • Invariants: Every state corresponds to a unique endpos-equivalence class of substrings.; For any state, all substrings ending at its endpos set are represented by that state or its ancestors via suffix links.
//   • Tips: Focus on the endpos definition for state equivalence.; Understand the incremental construction process.
//   • Pitfalls: The construction algorithm is non-trivial and prone to off-by-one errors.; Misinterpreting the role of suffix links vs. transition links.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minSwaps(string s) {
        int n = s.size();
        int count0 = 0;
        int count1 = 0;
        for (char c : s) {
            if (c == '0') count0++;
            else count1++;
        }

        // Check feasibility
        if (abs(count0 - count1) > 1) return -1;

        auto calculate_swaps = [&](char start_char) -> int {
            int swaps = 0;
            for (int i = 0; i < n; ++i) {
                char expected_char = (i % 2 == 0) ? start_char : (start_char == '0' ? '1' : '0');
                if (s[i] != expected_char) swaps++;
            }
            return swaps / 2; // Each swap fixes two positions
        };

        if (count0 > count1) {
            return calculate_swaps('0');
        } else if (count1 > count0) {
            return calculate_swaps('1');
        } else {
            return min(calculate_swaps('0'), calculate_swaps('1'));
        }           
    }
};
