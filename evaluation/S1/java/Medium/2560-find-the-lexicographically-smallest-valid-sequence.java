// Source: https://leetcode.com/problems/find-the-lexicographically-smallest-valid-sequence/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings word1 and word2.
//
// A string x is called almost equal to y if you can change at most one character in x to make it identical to y.
//
// A sequence of indices seq is called valid if:
//
//
// 	The indices are sorted in ascending order.
// 	Concatenating the characters at these indices in word1 in the same order results in a string that is almost equal to word2.
//
//
// Return an array of size word2.length representing the lexicographically smallest valid sequence of indices. If no such sequence of indices exists, return an empty array.
//
// Note that the answer must represent the lexicographically smallest array, not the corresponding string formed by those indices.
//
// Example:
// Input: word1 = "vbcca", word2 = "abc"
//
// Output: [0,1,2]
//
// Explanation:
//
// The lexicographically smallest valid sequence of indices is [0, 1, 2]:
//
//
// 	Change word1[0] to 'a'.
// 	word1[1] is already 'b'.
// 	word1[2] is already 'c'.
//
// Constraints:
// 1 <= word2.length < word1.length <= 3 * 105
// 	word1 and word2 consist only of lowercase English letters.
//
// Helpful references (internal KB):
// - String Sorts (array, string, recursion)
//   • When to use: Use this algorithm to sort a collection of strings lexicographically, especially when string lengths vary or are large, and the character set is limited.
//   • Idea: This algorithm sorts an array of strings lexicographically by recursively applying a counting sort-like distribution based on characters from most significant to least significant digit. It typically achieves O(N*L + R*L) time complexity, where N is the number of strings, L is the average string length, and R is the radix size.
//   • Invariants: All strings in the current `a[lo...hi]` sub-array share a common prefix of length `d`.; After the distribution pass for character `d`, `aux` contains strings from `a[lo...hi]` stably sorted by their `d`-th character.
//   • Tips: Use an auxiliary array for stable distribution during each pass to maintain relative order.; Implement a cutoff to insertion sort for small sub-arrays to improve performance due to lower overhead.
//   • Pitfalls: Can have high overhead for small N or short strings compared to comparison sorts.; Potentially memory intensive due to the auxiliary array and recursion stack depth proportional to max string length.
// - Solve RMQ (Range Minimum Query) by finding LCA (Lowest Common Ancestor) (array, tree, stack, simulation, monotonic-stack)
//   • When to use: This technique is used to answer Range Minimum Queries efficiently on a static array by transforming them into Lowest Common Ancestor queries on a Cartesian Tree.
//   • Idea: This approach solves Range Minimum Query problems by constructing a Cartesian Tree from the input array, where the root of any subtree is its minimum element. RMQ for a given range then reduces to finding the Lowest Common Ancestor of the range's endpoints in this tree, allowing O(N) construction and O(1) query time after O(N) preprocessing.
//   • Invariants: For any node `u` in the Cartesian Tree, `value(u)` is the minimum among all values in the subtree rooted at `u`.; For any node `u`, all nodes in its left subtree have indices smaller than `index(u)`, and all nodes in its right subtree have indices larger than `index(u)`.
//   • Tips: A Cartesian Tree is a binary tree where each node's value is less than its children's values, and an in-order traversal yields the original array.; Utilize a monotonic stack to construct the Cartesian Tree in linear O(N) time.
//   • Pitfalls: Correctly implementing the monotonic stack for Cartesian Tree construction can be challenging.; Edge cases, such as an empty stack or handling the last elements during tree building, must be managed carefully.
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int[] validSequence(String word1, String word2) {
        int n = word2.length();
        int m = word1.length();
        int[][] pos = new int[26][];
        for (int i = 0; i < 26; i++) {
            pos[i] = new int[m + 1];
            pos[i][m] = m;
        }
        for (int i = m - 1; i >= 0; i--) {
            for (int j = 0; j < 26; j++) {
                pos[j][i] = pos[j][i + 1];
            }
            pos[word1.charAt(i) - 'a'][i] = i;
        }

        int[] dp = new int[n + 1];
        int[] change = new int[n + 1];
        for (int i = n - 1; i >= 0; i--) {
            dp[i] = Integer.MAX_VALUE;
            change[i] = -1;
            for (int c = 0; c < 26; c++) {
                int nextPos = pos[c][dp[i + 1] == Integer.MAX_VALUE ? 0 : dp[i + 1]];
                if (nextPos == m) {
                    continue;
                }
                int cost = dp[i + 1] + (c == word2.charAt(i) - 'a' ? 0 : 1);
                if (cost < dp[i]) {
                    dp[i] = cost;
                    change[i] = c;
                }
            }
        }

        if (dp[0] > 1) {
            return new int[0];
        }

        int[] result = new int[n];
        int currPos = 0;
        for (int i = 0; i < n; i++) {
            int c = change[i];
            currPos = pos[c][currPos];
            result[i] = currPos;
            currPos++;
        }
        return result;          
    }
}
