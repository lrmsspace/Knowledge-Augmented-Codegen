// Source: https://leetcode.com/problems/remove-invalid-parentheses/   |   Difficulty: Hard
//
// Problem Description:
// Given a string s that contains parentheses and letters, remove the minimum number of invalid parentheses to make the input string valid.
//
// Return a list of unique strings that are valid with the minimum number of removals. You may return the answer in any order.
//
// Example:
// Input: s = "()())()"
// Output: ["(())()","()()()"]
//
// Constraints:
// 1 <= s.length <= 25
// 	s consists of lowercase English letters and parentheses '(' and ')'.
// 	There will be at most 20 parentheses in s.
//
// Helpful references (internal KB):
// - Breadth-first search (graph, array, bfs, counting)
//   • When to use: Use when finding the shortest path in an unweighted graph or traversing a graph level by level to explore all reachable nodes. It is also suitable for finding connected components or checking reachability.
//   • Idea: Breadth-first search explores a graph layer by layer, finding the shortest path in terms of edges from a source node to all other reachable nodes. It typically runs in O(V + E) time, where V is the number of vertices and E is the number of edges.
//   • Invariants: All nodes currently in the queue are at the same or next level of traversal from the source.; All nodes already dequeued have been fully processed, and their unvisited neighbors have been enqueued.
//   • Tips: Use a queue to manage nodes to visit in a FIFO manner.; Mark nodes as visited immediately upon adding them to the queue to prevent redundant processing and cycles.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs or incorrect path lengths.; Not handling disconnected components if the goal is to traverse the entire graph.
// - Suffix Automaton (graph, string, simulation)
//   • When to use: Use to efficiently represent all suffixes of a string in a compressed form, ideal for various string problems like pattern matching or counting distinct substrings.
//   • Idea: A suffix automaton is a minimal Deterministic Finite Automaton (DFA) that accepts all suffixes of a given string, offering O(N) time construction and O(N) memory complexity.
//   • Invariants: Every state in the automaton represents a set of substrings of the original string.; Each state's longest path from the initial state corresponds to its longest string.
//   • Tips: Understand the definition of states and transitions, and their relationship to substrings.; Leverage its linear time and space complexity for efficient string processing on large inputs.
//   • Pitfalls: The construction algorithm can be complex and challenging to implement correctly.; Debugging state transitions, suffix links, and their properties requires careful attention.
// - Minimum stack / Minimum queue (queue, stack, simulation)
//   • When to use: Use when needing to efficiently query the minimum element of a stack or queue in O(1) average time. Also applicable for finding minimums in all fixed-length subarrays using a sliding window.
//   • Idea: This technique augments a stack or queue to support O(1) average time retrieval of its minimum element, typically by storing minimums alongside data or using auxiliary structures. It achieves amortized constant time for all operations.
//   • Invariants: For a minimum stack, the auxiliary minimum stack's top element is always the minimum of all elements currently in the main stack.; For a minimum queue implemented with two stacks, the output stack is only refilled from the input stack when the output stack becomes empty.
//   • Tips: For a minimum stack, use an auxiliary stack to store minimums encountered so far.; Only push to the auxiliary minimum stack if the new element is less than or equal to its current top.
//   • Pitfalls: Forgetting to pop from the auxiliary minimum stack when the main stack's top is removed.; Incorrectly handling the transfer logic between the two stacks for a minimum queue.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private boolean isValid(String s) {
        int balance = 0;
        for (char c : s.toCharArray()) {
            if (c == '(') balance++;
            else if (c == ')') {
                balance--;
                if (balance < 0) return false;
            }
        }
        return balance == 0;
    }
    public List<String> removeInvalidParentheses(String s) {
        List<String> result = new ArrayList<>();
        if (s == null) return result;

        Set<String> visited = new HashSet<>();
        Queue<String> queue = new LinkedList<>();

        queue.add(s);
        visited.add(s);

        boolean found = false;

        while (!queue.isEmpty()) {
            String current = queue.poll();

            if (isValid(current)) {
                result.add(current);
                found = true;
            }

            if (found) continue;

            for (int i = 0; i < current.length(); i++) {
                if (current.charAt(i) != '(' && current.charAt(i) != ')') continue;

                String next = current.substring(0, i) + current.substring(i + 1);
                if (!visited.contains(next)) {
                    queue.add(next);
                    visited.add(next);
                }
            }
        }

        return result;          
    }
}
