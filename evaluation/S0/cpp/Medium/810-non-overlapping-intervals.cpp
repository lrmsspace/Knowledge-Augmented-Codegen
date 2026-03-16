// Source: https://leetcode.com/problems/non-overlapping-intervals/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of intervals intervals where intervals[i] = [starti, endi], return the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping.
//
// Note that intervals which only touch at a point are non-overlapping. For example, [1, 2] and [2, 3] are non-overlapping.
//
// Example:
// Input: intervals = [[1,2],[2,3],[3,4],[1,3]]
// Output: 1
// Explanation: [1,3] can be removed and the rest of the intervals are non-overlapping.
//
// Constraints:
// 1 <= intervals.length <= 105
// 	intervals[i].length == 2
// 	-5 * 104 <= starti < endi <= 5 * 104
//

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.empty()) return 0;

        // Sort intervals based on their end times
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });

        int count = 0;
        int end = intervals[0][1];

        for (int i = 1; i < intervals.size(); ++i) {
            if (intervals[i][0] < end) {
                // Overlapping interval found, increment count
                count++;
            } else {
                // No overlap, update the end to the current interval's end
                end = intervals[i][1];
            }
        }

        return count;           
    }
};
