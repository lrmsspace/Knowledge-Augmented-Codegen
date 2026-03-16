// Source: https://leetcode.com/problems/merge-intervals/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals, and return an array of the non-overlapping intervals that cover all the intervals in the input.
//
// Example:
// Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
// Output: [[1,6],[8,10],[15,18]]
// Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6].
//
// Constraints:
// 1 <= intervals.length <= 104
// 	intervals[i].length == 2
// 	0 <= starti <= endi <= 104
//

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.empty()) return {};

        // Sort intervals based on the start time
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0];
        });

        vector<vector<int>> merged;
        merged.push_back(intervals[0]);

        for (size_t i = 1; i < intervals.size(); ++i) {
            if (intervals[i][0] <= merged.back()[1]) {
                // Overlapping intervals, merge them
                merged.back()[1] = max(merged.back()[1], intervals[i][1]);
            } else {
                // Non-overlapping interval, add to the result
                merged.push_back(intervals[i]);
            }
        }

        return merged;          
    }
};
