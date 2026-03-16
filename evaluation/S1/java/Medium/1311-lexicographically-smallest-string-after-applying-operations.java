// Source: https://leetcode.com/problems/lexicographically-smallest-string-after-applying-operations/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s of even length consisting of digits from 0 to 9, and two integers a and b.
//
// You can apply either of the following two operations any number of times and in any order on s:
//
//
// 	Add a to all odd indices of s (0-indexed). Digits post 9 are cycled back to 0. For example, if s = "3456" and a = 5, s becomes "3951".
// 	Rotate s to the right by b positions. For example, if s = "3456" and b = 1, s becomes "6345".
//
//
// Return the lexicographically smallest string you can obtain by applying the above operations any number of times on s.
//
// A string a is lexicographically smaller than a string b (of the same length) if in the first position where a and b differ, string a has a letter that appears earlier in the alphabet than the corresponding letter in b. For example, "0158" is lexicographically smaller than "0190" because the first position they differ is at the third letter, and '5' comes before '9'.
//
// Example:
// Input: s = "5525", a = 9, b = 2
// Output: "2050"
// Explanation: We can apply the following operations:
// Start:  "5525"
// Rotate: "2555"
// Add:    "2454"
// Add:    "2353"
// Rotate: "5323"
// Add:    "5222"
// Add:    "5121"
// Rotate: "2151"
// Add:    "2050"​​​​​
// There is no way to obtain a string that is lexicographically smaller than "2050".
//
// Constraints:
// 2 <= s.length <= 100
// 	s.length is even.
// 	s consists of digits from 0 to 9 only.
// 	1 <= a <= 9
// 	1 <= b <= s.length - 1
//
// Helpful references (internal KB):
// - Breadth-first search (graph, queue, array, bfs)
//   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes level by level. It is also suitable for problems requiring traversal of all nodes at a specific distance from a source.
//   • Idea: Breadth-first search systematically explores a graph level by level, ensuring that all nodes at distance k are visited before any nodes at distance k+1. It finds the shortest path in terms of number of edges for unweighted graphs in O(V + E) time.
//   • Invariants: All nodes currently in the queue have been discovered and marked, but their adjacent nodes have not yet been fully explored.; For any node v marked as visited, distTo[v] stores the shortest path length from the source s to v.
//   • Tips: Use a queue to manage nodes to visit.; Mark nodes as visited to prevent cycles and redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect paths.; Not handling disconnected graphs correctly.
// - Suffix Automaton (string, simulation)
//   • When to use: Use when needing to efficiently process all substrings or suffixes of a given string, especially for counting distinct substrings, finding occurrences, or other complex string pattern problems. It provides linear time solutions for many tasks.
//   • Idea: A suffix automaton is a directed acyclic graph that compactly represents all distinct substrings of a given string. It enables solving a wide range of string-related problems in linear time, typically O(N) or O(N log A) where N is string length and A is alphabet size.
//   • Invariants: Every path from the initial state corresponds to a distinct substring of the original string.; Each state in the automaton represents a set of substrings that share the same end positions.
//   • Tips: Understand the two types of links: suffix links (parent) and transition links (children).; Construction is typically incremental, adding characters one by one.
//   • Pitfalls: Implementation complexity is high; careful handling of state creation and link updates is crucial.; Off-by-one errors in length calculations or suffix link assignments are common.
// - Extended Euclidean Algorithm (number, gcd, simulation)
//   • When to use: Use this algorithm to find integer coefficients x and y that satisfy Bézout's identity (ax + by = gcd(a,b)). It is also essential for computing modular multiplicative inverses and solving linear Diophantine equations.
//   • Idea: The Extended Euclidean Algorithm computes the greatest common divisor (GCD) of two integers 'a' and 'b', and simultaneously finds integer coefficients 'x' and 'y' such that 'ax + by = gcd(a,b)'. It operates in O(log(min(a,b))) time complexity.
//   • Invariants: x * (initial a) + y * (initial b) = current_a_value; x_1 * (initial a) + y_1 * (initial b) = current_b_value
//   • Tips: Can be implemented using either a recursive or an iterative approach.; The algorithm correctly handles negative integer inputs.
//   • Pitfalls: Incorrectly defining base cases in recursive implementations can lead to errors.; Potential for integer overflow if coefficients x or y become extremely large, though uncommon.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    static class State {
        String str;
        int rotate;
        int addOdd;

        State(String str, int rotate, int addOdd) {
            this.str = str;
            this.rotate = rotate;
            this.addOdd = addOdd;
        }
    }
    private int getIndex(State state, int n) {
        return state.rotate * 100 + state.addOdd * 10 + state.str.charAt(0) - '0';
    }
    public String findLexSmallestString(String s, int a, int b) {
        int n = s.length();
        boolean[] visited = new boolean[n * 10 * 10];
        String ans = s;
        Queue<State> queue = new LinkedList<>();
        queue.offer(new State(s, 0, 0));
        visited[0] = true;

        while (!queue.isEmpty()) {
            State curr = queue.poll();
            String str = curr.str;

            if (str.compareTo(ans) < 0) {
                ans = str;
            }

            // Operation 1: Add 'a' to all odd indices
            char[] chars1 = str.toCharArray();
            for (int i = 1; i < n; i += 2) {
                chars1[i] = (char) (((chars1[i] - '0' + a) % 10) + '0');
            }
            String nextStr1 = new String(chars1);
            State nextState1 = new State(nextStr1, (curr.rotate + b) % n, (curr.addOdd + a) % 10);
            int idx1 = getIndex(nextState1, n);
            if (!visited[idx1]) {
                visited[idx1] = true;
                queue.offer(nextState1);
            }

            // Operation 2: Rotate the string by 'b' positions
            String nextStr2 = str.substring(n - b) + str.substring(0, n - b);
            State nextState2 = new State(nextStr2, (curr.rotate + b) % n, curr.addOdd);
            int idx2 = getIndex(nextState2, n);
            if (!visited[idx2]) {
                visited[idx2] = true;
                queue.offer(nextState2);
            }
        }

        return ans;         
    }
}
