// Source: https://leetcode.com/problems/frequencies-of-shortest-supersequences/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of strings words. Find all shortest common supersequences (SCS) of words that are not permutations of each other.
//
// A shortest common supersequence is a string of minimum length that contains each string in words as a subsequence.
//
// Return a 2D array of integers freqs that represent all the SCSs. Each freqs[i] is an array of size 26, representing the frequency of each letter in the lowercase English alphabet for a single SCS. You may return the frequency arrays in any order.
//
// Example:
// Input: words = ["ab","ba"]
//
// Output: [[1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],[2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]]
//
// Explanation:
//
// The two SCSs are "aba" and "bab". The output is the letter frequencies for each one.
//
// Constraints:
// 1 <= words.length <= 256
// 	words[i].length == 2
// 	All strings in words will altogether be composed of no more than 16 unique lowercase letters.
// 	All strings in words are unique.
//
// Helpful references (internal KB):
// - Suffix array (array, string, suffix-array, divide-and-conquer, recursion)
//   • When to use: Use when you need to efficiently perform various string operations like pattern searching, finding repeated substrings, or comparing suffixes lexicographically on a given text. It is a fundamental data structure for advanced string algorithms.
//   • Idea: A suffix array is a sorted array of all suffixes of a given string. It allows for efficient string operations, with construction typically achievable in O(N log N) or O(N) time for advanced algorithms.
//   • Invariants: The suffix array SA[i] stores the starting index of the i-th lexicographically smallest suffix.; All suffixes of the input string are present exactly once in the suffix array.
//   • Tips: Consider using SA-IS for optimal O(N) construction time and space complexity.; Pair the suffix array with an LCP array for enhanced functionality, such as finding longest common substrings.
//   • Pitfalls: Naive O(N^2 log N) construction is too slow for large input strings.; Implementing linear-time algorithms like SA-IS or DC3 can be complex and error-prone.
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - String Hashing (string, array, hashing)
//   • When to use: Use when you need to efficiently compare strings or substrings, detect duplicates, or perform pattern matching in large text datasets. It's particularly useful for speeding up operations that would otherwise be O(N*M) or O(N^2).
//   • Idea: String hashing maps strings to numerical values, allowing for fast comparisons and operations like substring search. It typically uses a polynomial rolling hash function, achieving O(N) preprocessing and O(1) or O(log N) query time for substrings.
//   • Invariants: The hash of any prefix of the string is correctly computed based on its characters and chosen parameters.; For a rolling hash, the hash of the current window is always maintained correctly as the window slides.
//   • Tips: Choose a large prime modulus (or two) to minimize collision probability.; Select a base (prime number) larger than the alphabet size to ensure unique contributions from characters.
//   • Pitfalls: Hash collisions are possible and can lead to incorrect results if not properly handled or verified.; A poorly chosen base or modulus can significantly increase the frequency of collisions.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public List<List<Integer>> supersequences(String[] words) {
        int m = words.length;
        int[][] overlap = new int[m][m];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                if (i != j) {
                    if (words[i].charAt(1) == words[j].charAt(0)) {
                        overlap[i][j] = 1;
                    }
                }
            }
        }

        int N = 1 << m;
        int[][] dp = new int[N][m];
        for (int mask = 0; mask < N; mask++) {
            Arrays.fill(dp[mask], Integer.MAX_VALUE / 2);
        }
        for (int i = 0; i < m; i++) {
            dp[1 << i][i] = 2;
        }

        for (int mask = 0; mask < N; mask++) {
            for (int u = 0; u < m; u++) {
                if ((mask & (1 << u)) == 0) continue;
                for (int v = 0; v < m; v++) {
                    if ((mask & (1 << v)) != 0) continue;
                    int nextMask = mask | (1 << v);
                    dp[nextMask][v] = Math.min(dp[nextMask][v], dp[mask][u] + 2 - overlap[u][v]);
                }
            }
        }

        int minLen = Integer.MAX_VALUE;
        for (int i = 0; i < m; i++) {
            minLen = Math.min(minLen, dp[N - 1][i]);
        }

        Set<String> scsSet = new HashSet<>();
        for (int i = 0; i < m; i++) {
            if (dp[N - 1][i] == minLen) {
                backtrack(words, overlap, dp, N - 1, i, "", scsSet);
            }
        }

        List<List<Integer>> result = new ArrayList<>();
        for (String scs : scsSet) {
            List<Integer> freq = new ArrayList<>(Collections.nCopies(26, 0));
            for (char c : scs.toCharArray()) {
                freq.set(c - 'a', freq.get(c - 'a') + 1);
            }
            result.add(freq);
        }
        return result;
    }
}
