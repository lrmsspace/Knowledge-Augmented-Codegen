// Source: https://leetcode.com/problems/longest-well-performing-interval/   |   Difficulty: Medium
//
// Problem Description:
// We are given hours, a list of the number of hours worked per day for a given employee.
//
// A day is considered to be a tiring day if and only if the number of hours worked is (strictly) greater than 8.
//
// A well-performing interval is an interval of days for which the number of tiring days is strictly larger than the number of non-tiring days.
//
// Return the length of the longest well-performing interval.
//
// Example:
// Input: hours = [9,9,6,0,6,6,9]
// Output: 3
// Explanation: The longest well-performing interval is [9,9,6].
//
// Constraints:
// 1 <= hours.length <= 104
// 	0 <= hours[i] <= 16
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int longestWPI(vector<int>& hours) {
        int n = hours.size();
        vector<int> prefixSum(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefixSum[i + 1] = prefixSum[i] + (hours[i] > 8 ? 1 : -1);
        }

        stack<int> s;
        for (int i = 0; i <= n; ++i) {
            if (s.empty() || prefixSum[i] < prefixSum[s.top()]) {
                s.push(i);
            }
        }

        int maxLength = 0;
        for (int i = n; i >= 0; --i) {
            while (!s.empty() && prefixSum[i] > prefixSum[s.top()]) {
                maxLength = max(maxLength, i - s.top());
                s.pop();
            }
        }

        return maxLength;           
    }
};
