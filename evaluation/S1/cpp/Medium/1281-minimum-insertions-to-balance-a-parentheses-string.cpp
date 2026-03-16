// Source: https://leetcode.com/problems/minimum-insertions-to-balance-a-parentheses-string/   |   Difficulty: Medium
//
// Problem Description:
// Given a parentheses string s containing only the characters '(' and ')'. A parentheses string is balanced if:
//
//
// 	Any left parenthesis '(' must have a corresponding two consecutive right parenthesis '))'.
// 	Left parenthesis '(' must go before the corresponding two consecutive right parenthesis '))'.
//
//
// In other words, we treat '(' as an opening parenthesis and '))' as a closing parenthesis.
//
//
// 	For example, "())", "())(())))" and "(())())))" are balanced, ")()", "()))" and "(()))" are not balanced.
//
//
// You can insert the characters '(' and ')' at any position of the string to balance it if needed.
//
// Return the minimum number of insertions needed to make s balanced.
//
// Example:
// Input: s = "(()))"
// Output: 1
// Explanation: The second '(' has two matching '))', but the first '(' has only ')' matching. We need to add one more ')' at the end of the string to be "(())))" which is balanced.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of '(' and ')' only.
//
// Helpful references (internal KB):
// - Balanced bracket sequences (number, counting)
//   • When to use: Use this when verifying if a sequence of delimiters is correctly nested and balanced. It is also applicable for counting or generating all possible valid sequences of a given length.
//   • Idea: This algorithm involves checking if a sequence of opening and closing delimiters is properly matched and nested, or enumerating such sequences. Validation typically uses a stack in O(N) time, while generation often involves backtracking with O(Catalan(N)) complexity.
//   • Invariants: The stack contains only opening delimiters that are yet to be matched.; The balance counter (open - close) is never negative at any point during traversal.
//   • Tips: Use a stack to track unmatched opening delimiters for validation.; Maintain a balance counter (increment for open, decrement for close) for a simpler check.
//   • Pitfalls: Forgetting to check if the stack is empty after processing the entire sequence.; Allowing a closing delimiter when no matching opening delimiter is available (empty stack or mismatch).
// - Manacher's Algorithm - Finding all sub-p (string, array, simulation, enumeration)
//   • When to use: When you need to find all palindromic substrings or the longest palindromic substring within a given string efficiently. It is particularly useful for achieving linear time complexity for this task.
//   • Idea: Manacher's algorithm finds all maximal palindromic substrings centered at each position in a string by leveraging symmetry and previously computed results. It achieves an optimal O(N) time complexity.
//   • Invariants: d_odd[i] stores the radius of the longest odd-length palindrome centered at i.; The (l, r) interval always defines the rightmost palindrome found so far.
//   • Tips: Preprocess the string with delimiters to unify odd and even length palindromes.; Maintain the current rightmost boundary `r` of the largest palindrome found.
//   • Pitfalls: Forgetting to update the `(l, r)` boundaries after processing each center.; Incorrectly calculating mirror positions or handling boundary cases for `i > r`.
// - Optimal schedule of jobs given their deadlines and durations (heap, interval, greedy, simulation)
//   • When to use: When needing to find an optimal schedule for a set of jobs, each with a deadline and duration, typically to maximize completed jobs or minimize total lateness. This approach often involves processing jobs based on deadlines and dynamically selecting tasks.
//   • Idea: This algorithm finds an optimal job schedule by processing jobs sorted by their deadlines, using a priority queue to manage available tasks. It greedily selects jobs with the shortest run-time that can be completed within the current time window, achieving an optimal solution in O(N log N) time complexity.
//   • Invariants: All jobs with deadlines greater than the current job's deadline have been considered.; The priority queue contains jobs that can potentially be scheduled within the current time window.
//   • Tips: Sort jobs by deadline in descending order to process later deadlines first.; Use a min-priority queue to efficiently retrieve the job with the least run-time.
//   • Pitfalls: Incorrectly sorting jobs (e.g., ascending deadline or by duration).; Not handling overlapping time intervals or deadlines properly.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minInsertions(string s) {
        int res = 0;
        int need = 0; // number of ')' needed

        for (char c : s) {
            if (c == '(') {
                // Each '(' requires two ')'
                need += 2;
                // If need is odd, we have an unmatched ')', insert one
                if (need % 2 == 1) {
                    res++;
                    need--; // now need is even
                }
            } else { // c == ')'
                need--; // one ')' satisfies one need
                if (need < 0) {
                    // More ')' than needed, insert a '('
                    res++;
                    need = 1; // now we need one more ')'
                }
            }
        }

        return res + need; // total insertions needed           
    }
};
