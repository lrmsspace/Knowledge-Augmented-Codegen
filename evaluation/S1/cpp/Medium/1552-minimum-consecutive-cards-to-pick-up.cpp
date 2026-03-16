// Source: https://leetcode.com/problems/minimum-consecutive-cards-to-pick-up/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array cards where cards[i] represents the value of the ith card. A pair of cards are matching if the cards have the same value.
//
// Return the minimum number of consecutive cards you have to pick up to have a pair of matching cards among the picked cards. If it is impossible to have matching cards, return -1.
//
// Example:
// Input: cards = [3,4,2,3,4,7]
// Output: 4
// Explanation: We can pick up the cards [3,4,2,3] which contain a matching pair of cards with value 3. Note that picking up the cards [4,2,3,4] is also optimal.
//
// Constraints:
// 1 <= cards.length <= 105
// 	0 <= cards[i] <= 106
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
// - Rabin-Karp Algorithm for string matching (string, number, hashing, rolling-hash)
//   • When to use: To efficiently find all occurrences of a given pattern string within a larger text string, especially when multiple patterns might be searched or for average-case linear time performance.
//   • Idea: The Rabin-Karp algorithm finds occurrences of a pattern in a text by comparing their hash values, using a rolling hash function to efficiently update substring hashes. It achieves an average time complexity of O(|s| + |t|) and a worst-case of O(|s| * |t|).
//   • Invariants: The hash of the pattern string remains constant throughout the search.; The current window's hash value accurately represents the substring T[i...i+len(P)-1].
//   • Tips: Choose a large prime modulus to minimize hash collisions.; Select a suitable base (e.g., a prime greater than alphabet size) for polynomial hashing.
//   • Pitfalls: Hash collisions can lead to false positives and degrade worst-case performance to O(MN).; Poor choice of base or modulus can significantly increase collision frequency.
// - Longest increasing subsequence (array, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
//   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
//   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
//   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minimumCardPickup(vector<int>& cards) {
        const int n = cards.size();
        const int MAX_CARD_VALUE = 1'000'000;

        // lastPos[value] = last seen index of card with this value
        std::vector<int> lastPos(MAX_CARD_VALUE + 1, -1);
        int minLength = n + 1;

        for (int i = 0; i < n; ++i) {
            int value = cards[i];
            if (lastPos[value] != -1) {
                // Found a matching pair, calculate length
                int length = i - lastPos[value] + 1;
                if (length < minLength) {
                    minLength = length;
                }
            }
            // Update last seen position
            lastPos[value] = i;
        }

        return (minLength == n + 1) ? -1 : minLength;           
    }
};
