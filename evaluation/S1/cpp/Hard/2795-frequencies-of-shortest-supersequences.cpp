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
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<vector<int>> supersequences(vector<string>& words) {
        int n = words.size();
        int charMask = 0;
        for (const string& w : words) {
            for (char c : w) {
                charMask |= (1 << (c - 'a'));
            }
        }
        vector<int> chars;
        for (int i = 0; i < 26; ++i) {
            if (charMask & (1 << i)) {
                chars.push_back(i);
            }
        }
        int m = chars.size();

        vector<vector<int>> dp(1 << m, vector<int>(1 << m, INT_MAX));
        for (int mask = 0; mask < (1 << m); ++mask) {
            dp[mask][0] = 0;
        }

        for (int mask = 0; mask < (1 << m); ++mask) {
            for (int addMask = 1; addMask < (1 << m); ++addMask) {
                int best = INT_MAX;
                for (int wIdx = 0; wIdx < n; ++wIdx) {
                    const string& w = words[wIdx];
                    int need = 0;
                    for (char c : w) {
                        int cIdx = find(chars.begin(), chars.end(), c - 'a') - chars.begin();
                        if (!((mask | addMask) & (1 << cIdx))) {
                            need = -1;
                            break;
                        }
                        if (!(mask & (1 << cIdx))) {
                            need |= (1 << cIdx);
                        }
                    }
                    if (need == -1) continue;
                    int prevAdd = addMask & (~need);
                    if (dp[mask][prevAdd] != INT_MAX) {
                        best = min(best, dp[mask][prevAdd] + (int)w.length());
                    }
                }
                dp[mask][addMask] = best;
            }
        }

        int fullMask = (1 << m) - 1;
        int minLen = INT_MAX;
        for (int addMask = 0; addMask < (1 << m); ++addMask) {
            if (dp[fullMask][addMask] < minLen) {
                minLen = dp[fullMask][addMask];
            }
        }

        vector<vector<int>> result;
        for (int addMask = 0; addMask < (1 << m); ++addMask) {
            if (dp[fullMask][addMask] == minLen) {
                vector<int> freq(26, 0);
                for (int i = 0; i < m; ++i) {
                    if (fullMask & (1 << i)) {
                        freq[chars[i]]++;
                    }
                    if (addMask & (1 << i)) {
                        freq[chars[i]]++;
                    }
                }
                result.push_back(freq);
            }
        }
        return result;       
    }
};
