// Source: https://leetcode.com/problems/find-right-interval/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of intervals, where intervals[i] = [starti, endi] and each starti is unique.
//
// The right interval for an interval i is an interval j such that startj >= endi and startj is minimized. Note that i may equal j.
//
// Return an array of right interval indices for each interval i. If no right interval exists for interval i, then put -1 at index i.
//
// Example:
// Input: intervals = [[1,2]]
// Output: [-1]
// Explanation: There is only one interval in the collection, so it outputs -1.
//
// Constraints:
// 1 <= intervals.length <= 2 * 104
// 	intervals[i].length == 2
// 	-106 <= starti <= endi <= 106
// 	The start point of each interval is unique.
//

class Solution {
public:
    vector<int> findRightInterval(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<int> result(n, -1);
        vector<pair<int, int>> starts; // pair of (start, index)

        for (int i = 0; i < n; ++i) {
            starts.emplace_back(intervals[i][0], i);
        }

        sort(starts.begin(), starts.end());

        for (int i = 0; i < n; ++i) {
            int end = intervals[i][1];
            int left = 0, right = n - 1;
            int idx = -1;

            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (starts[mid].first >= end) {
                    idx = starts[mid].second;
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }

            result[i] = idx;
        }

        return result;          
    }
};
