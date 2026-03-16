// Source: https://leetcode.com/problems/maximum-number-of-non-overlapping-substrings/   |   Difficulty: Hard
//
// Problem Description:
// Given a string s of lowercase letters, you need to find the maximum number of non-empty substrings of s that meet the following conditions:
//
//
// 	The substrings do not overlap, that is for any two substrings s[i..j] and s[x..y], either j < x or i > y is true.
// 	A substring that contains a certain character c must also contain all occurrences of c.
//
//
// Find the maximum number of substrings that meet the above conditions. If there are multiple solutions with the same number of substrings, return the one with minimum total length. It can be shown that there exists a unique solution of minimum total length.
//
// Notice that you can return the substrings in any order.
//
// Example:
// Input: s = "adefaddaccc"
// Output: ["e","f","ccc"]
// Explanation: The following are all the possible substrings that meet the conditions:
// [
//   "adefaddaccc"
//   "adefadda",
//   "ef",
//   "e",
//   "f",
//   "ccc",
// ]
// If we choose the first string, we cannot choose anything else and we'd get only 1. If we choose "adefadda", we are left with "ccc" which is the only one that doesn't overlap, thus obtaining 2 substrings. Notice also, that it's not optimal to choose "ef" since it can be split into two. Therefore, the optimal way is to choose ["e","f","ccc"] which gives us 3 substrings. No other solution of the same number of substrings exist.
//
// Constraints:
// 1 <= s.length <= 105
// 	s contains only lowercase English letters.
//
// Helpful references (internal KB):
// - Suffix Array (array, string, simulation, two-pointers)
//   • When to use: Use when needing to efficiently compare substrings, find all occurrences of a pattern, or determine lexicographical order among suffixes within a string.
//   • Idea: A Suffix Array stores sorted suffixes of a string, enabling fast substring comparisons and pattern searching. Construction typically takes O(N log N) time, with comparisons often O(1) after preprocessing.
//   • Invariants: The suffix array `p` contains all suffixes of the string `s` sorted lexicographically.; During construction, equivalence classes `c` correctly group suffixes that are identical up to a certain length `2^k`.
//   • Tips: Precompute log values for efficient block length calculation.; Utilize equivalence classes for O(1) comparison of power-of-two length substrings.
//   • Pitfalls: Complexity of suffix array construction can be tricky (e.g., O(N log N) vs O(N)).; Off-by-one errors when calculating block indices or lengths.
// - palindrome-partitioning (string, array, backtracking, recursion)
//   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
//   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
//   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
//   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
//   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public List<String> maxNumOfSubstrings(String s) {
        int n = s.length();
        int[][] pos = new int[26][2];
        for (int i = 0; i < 26; i++) {
            pos[i][0] = n;
            pos[i][1] = -1;
        }
        for (int i = 0; i < n; i++) {
            char c = s.charAt(i);
            pos[c - 'a'][0] = Math.min(pos[c - 'a'][0], i);
            pos[c - 'a'][1] = Math.max(pos[c - 'a'][1], i);
        }

        List<String> ans = new ArrayList<>();
        for (int i = 0; i < 26; i++) {
            if (pos[i][0] == n) {
                continue;
            }
            int left = pos[i][0];
            int right = pos[i][1];
            boolean valid = true;
            for (int j = left; j <= right; j++) {
                char c = s.charAt(j);
                if (pos[c - 'a'][0] < left) {
                    valid = false;
                    break;
                }
                right = Math.max(right, pos[c - 'a'][1]);
            }
            if (valid) {
                ans.add(s.substring(left, right + 1));
            }
        }

        Collections.sort(ans, Comparator.comparingInt(String::length));
        List<String> res = new ArrayList<>();
        int lastEnd = -1;
        for (String str : ans) {
            int start = s.indexOf(str);
            int end = start + str.length() - 1;
            if (start > lastEnd) {
                res.add(str);
                lastEnd = end;
            }
        }
        return res;         
    }
}
