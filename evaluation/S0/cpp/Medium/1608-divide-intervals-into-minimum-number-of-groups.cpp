// Source: https://leetcode.com/problems/divide-intervals-into-minimum-number-of-groups/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer array intervals where intervals[i] = [lefti, righti] represents the inclusive interval [lefti, righti].
//
// You have to divide the intervals into one or more groups such that each interval is in exactly one group, and no two intervals that are in the same group intersect each other.
//
// Return the minimum number of groups you need to make.
//
// Two intervals intersect if there is at least one common number between them. For example, the intervals [1, 5] and [5, 8] intersect.
//
// Example:
// Input: intervals = [[5,10],[6,8],[1,5],[2,3],[1,10]]
// Output: 3
// Explanation: We can divide the intervals into the following groups:
// - Group 1: [1, 5], [6, 8].
// - Group 2: [2, 3], [5, 10].
// - Group 3: [1, 10].
// It can be proven that it is not possible to divide the intervals into fewer than 3 groups.
//
// Constraints:
// 1 <= intervals.length <= 105
// 	intervals[i].length == 2
// 	1 <= lefti <= righti <= 106
//

class Solution {
public:
    int minGroups(vector<vector<int>>& intervals) {
        vector<int> timeline(1000002, 0);

        for (const auto& interval : intervals) {
            timeline[interval[0]] += 1;
            timeline[interval[1] + 1] -= 1;
        }

        int maxGroups = 0;
        int currentGroups = 0;

        for (int count : timeline) {
            currentGroups += count;
            maxGroups = max(maxGroups, currentGroups);
        }

        return maxGroups;           
    }
};
