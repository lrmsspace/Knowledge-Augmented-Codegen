// Source: https://leetcode.com/problems/minimum-time-difference/   |   Difficulty: Medium
//
// Problem Description:
// Given a list of 24-hour clock time points in "HH:MM" format, return the minimum minutes difference between any two time-points in the list.
//
// Example:
// Input: timePoints = ["23:59","00:00"]
// Output: 1
//
// Constraints:
// 2 <= timePoints.length <= 2 * 104
// 	timePoints[i] is in the format "HH:MM".
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
    int findMinDifference(vector<string>& timePoints) {
        // Convert time points to minutes and sort them
        vector<int> minutes;
        for (const string& time : timePoints) {
            int h = stoi(time.substr(0, 2));
            int m = stoi(time.substr(3, 2));
            minutes.push_back(h * 60 + m);
        }
        sort(minutes.begin(), minutes.end());

        // Find the minimum difference between adjacent time points
        int minDiff = INT_MAX;
        for (size_t i = 1; i < minutes.size(); ++i) {
            minDiff = min(minDiff, minutes[i] - minutes[i - 1]);
        }

        // Check the difference between the last and first time points (circular)
        minDiff = min(minDiff, (minutes[0] + 1440) - minutes.back());

        return minDiff;         
    }
};
