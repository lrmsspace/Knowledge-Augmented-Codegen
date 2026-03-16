// Source: https://leetcode.com/problems/construct-smallest-number-from-di-string/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed string pattern of length n consisting of the characters 'I' meaning increasing and 'D' meaning decreasing.
//
// A 0-indexed string num of length n + 1 is created using the following conditions:
//
//
// 	num consists of the digits '1' to '9', where each digit is used at most once.
// 	If pattern[i] == 'I', then num[i] < num[i + 1].
// 	If pattern[i] == 'D', then num[i] > num[i + 1].
//
//
// Return the lexicographically smallest possible string num that meets the conditions.
//
// Example:
// Input: pattern = "IIIDIDDD"
// Output: "123549876"
// Explanation:
// At indices 0, 1, 2, and 4 we must have that num[i] < num[i+1].
// At indices 3, 5, 6, and 7 we must have that num[i] > num[i+1].
// Some possible values of num are "245639871", "135749862", and "123849765".
// It can be proven that "123549876" is the smallest possible num that meets the conditions.
// Note that "123414321" is not possible because the digit '1' is used more than once.
//
// Constraints:
// 1 <= pattern.length <= 8
// 	pattern consists of only the letters 'I' and 'D'.
//
// Helpful references (internal KB):
// - Minimum stack / Minimum queue (stack, simulation)
//   • When to use: When you need to perform standard stack operations (push, pop) and also query the minimum element currently in the stack, all in constant time.
//   • Idea: Augments a standard stack by storing each element along with the minimum value encountered up to that point in the stack. This allows O(1) retrieval of the current minimum, while push and pop operations also remain O(1).
//   • Invariants: The top element's second component (minimum_so_far) always represents the minimum value currently in the entire stack.; For any element (value, min_so_far) in the stack, min_so_far is the minimum of 'value' and all elements below it.
//   • Tips: Store elements as pairs: (actual_value, minimum_at_this_level).; When pushing, the new minimum_at_this_level is min(new_value, stack.top().second) if stack is not empty, else new_value.
//   • Pitfalls: Forgetting to handle the empty stack case when calculating the minimum for a new element.; Incorrectly assuming the minimum can be tracked with a single auxiliary variable without considering pops.
// - String Sorts (array, string, recursion)
//   • When to use: Use this algorithm to sort a collection of strings lexicographically, especially when string lengths vary or are large, and the character set is limited.
//   • Idea: This algorithm sorts an array of strings lexicographically by recursively applying a counting sort-like distribution based on characters from most significant to least significant digit. It typically achieves O(N*L + R*L) time complexity, where N is the number of strings, L is the average string length, and R is the radix size.
//   • Invariants: All strings in the current `a[lo...hi]` sub-array share a common prefix of length `d`.; After the distribution pass for character `d`, `aux` contains strings from `a[lo...hi]` stably sorted by their `d`-th character.
//   • Tips: Use an auxiliary array for stable distribution during each pass to maintain relative order.; Implement a cutoff to insertion sort for small sub-arrays to improve performance due to lower overhead.
//   • Pitfalls: Can have high overhead for small N or short strings compared to comparison sorts.; Potentially memory intensive due to the auxiliary array and recursion stack depth proportional to max string length.
// - Linear Diophantine Equation (number, greedy)
//   • When to use: Use when a problem can be solved by making the locally optimal choice at each step, hoping this leads to a globally optimal solution. This strategy is often simpler and faster than dynamic programming.
//   • Idea: The greedy algorithm makes the best choice at each stage with the hope of finding a global optimum, without reconsidering previous choices. Its time complexity is typically O(N log N) or O(N).
//   • Invariants: At each step, the chosen element is the best available according to the greedy criterion.; The partial solution constructed so far remains optimal for the subproblem considered.
//   • Tips: Prove correctness by exchange argument or induction.; Sort input data if it helps identify the greedy choice.
//   • Pitfalls: Failing to prove the greedy choice property.; Making a locally optimal choice that prevents a global optimum.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private boolean backtrack(String pattern, StringBuilder result, boolean[] used, int n) {
        if (result.length() == n + 1) {
            return true;
        }
        int index = result.length();
        char lastChar = result.charAt(result.length() - 1);
        for (int i = 1; i <= 9; i++) {
            if (!used[i]) {
                if ((pattern.charAt(index - 1) == 'I' && lastChar - '0' < i) ||
                    (pattern.charAt(index - 1) == 'D' && lastChar - '0' > i)) {
                    used[i] = true;
                    result.append(i);
                    if (backtrack(pattern, result, used, n)) {
                        return true;
                    }
                    result.deleteCharAt(result.length() - 1);
                    used[i] = false;
                }
            }
        }
        return false;
    }
    public String smallestNumber(String pattern) {
        StringBuilder result = new StringBuilder();
        int n = pattern.length();
        boolean[] used = new boolean[10]; // Digits 1-9

        for (int i = 1; i <= 9; i++) {
            if (!used[i]) {
                used[i] = true;
                result.append(i);
                if (backtrack(pattern, result, used, n)) {
                    return result.toString();
                }
                result.deleteCharAt(result.length() - 1);
                used[i] = false;
            }
        }
        return "";          
    }
}
