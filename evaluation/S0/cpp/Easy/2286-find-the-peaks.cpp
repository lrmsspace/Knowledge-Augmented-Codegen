// Source: https://leetcode.com/problems/find-the-peaks/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed array mountain. Your task is to find all the peaks in the mountain array.
//
// Return an array that consists of indices of peaks in the given array in any order.
//
// Example:
// Input: mountain = [2,4,4]
// Output: []
// Explanation: mountain[0] and mountain[2] can not be a peak because they are first and last elements of the array.
// mountain[1] also can not be a peak because it is not strictly greater than mountain[2].
// So the answer is [].
//
// Constraints:
// 3 <= mountain.length <= 100
// 	1 <= mountain[i] <= 100
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<int> findPeaks(vector<int>& mountain) {
        vector<int> peaks;
        int n = mountain.size();
        
        for (int i = 1; i < n - 1; ++i) {
            if (mountain[i] > mountain[i - 1] && mountain[i] > mountain[i + 1]) {
                peaks.push_back(i);
            }
        }
        
        return peaks;           
    }
};
