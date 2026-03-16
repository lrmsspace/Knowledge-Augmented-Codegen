// Source: https://leetcode.com/problems/maximum-difference-between-even-and-odd-frequency-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s and an integer k. Your task is to find the maximum difference between the frequency of two characters, freq[a] - freq[b], in a substring subs of s, such that:
//
//
// 	subs has a size of at least k.
// 	Character a has an odd frequency in subs.
// 	Character b has a non-zero even frequency in subs.
//
//
// Return the maximum difference.
//
// Note that subs can contain more than 2 distinct characters.
//
// Example:
// Input: s = "12233", k = 4
//
// Output: -1
//
// Explanation:
//
// For the substring "12233", the frequency of '1' is 1 and the frequency of '3' is 2. The difference is 1 - 2 = -1.
//
// Constraints:
// 3 <= s.length <= 3 * 104
// 	s consists only of digits '0' to '4'.
// 	The input is generated that at least one substring has a character with an even frequency and a character with an odd frequency.
// 	1 <= k <= s.length
//
// Helpful references (internal KB):
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// - Digit DP (array, number, digit-dp)
//   • When to use: When counting numbers within a given range [A, B] that satisfy certain digit-based properties, or calculating a sum of such properties.
//   • Idea: Digit DP is a dynamic programming technique used to count numbers or calculate sums of properties for numbers within a given range, based on their digits. It typically involves a recursive function with memoization, processing digits from most significant to least significant, achieving a time complexity of O(log(N) * S * T) where S is sum/state range and T is tight constraint.
//   • Invariants: The `idx` parameter always represents the current digit position being processed, from most significant to least significant.; The `tight` boolean parameter accurately indicates if the current digit choice is restricted by the original number's corresponding digit.
//   • Tips: Handle leading zeros carefully, often with a dedicated boolean state in the DP function.; Use a 'tight' or 'limit' boolean parameter to manage the upper bound constraint imposed by the original number.
//   • Pitfalls: Incorrectly handling the 'tight' constraint can lead to overcounting or undercounting.; Forgetting to reset the memoization table for each new query or test case, especially in competitive programming.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int maxDifference(string s, int k) {
        int n = s.size();
        vector<int> freq(5, 0);
        int maxDiff = -1;

        for (int i = 0; i < n; ++i) {
            freq[s[i] - '0']++;

            if (i >= k - 1) {
                int oddFreq = -1;
                int evenFreq = -1;

                for (int j = 0; j < 5; ++j) {
                    if (freq[j] % 2 == 1) {
                        oddFreq = max(oddFreq, freq[j]);
                    } else if (freq[j] > 0) {
                        evenFreq = max(evenFreq, freq[j]);
                    }
                }

                if (oddFreq != -1 && evenFreq != -1) {
                    maxDiff = max(maxDiff, oddFreq - evenFreq);
                }

                // Remove the frequency of the character that is sliding out of the window
                freq[s[i - k + 1] - '0']--;
            }
        }

        return maxDiff;         
    }
};
