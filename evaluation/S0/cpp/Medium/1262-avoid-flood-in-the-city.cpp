// Source: https://leetcode.com/problems/avoid-flood-in-the-city/   |   Difficulty: Medium
//
// Problem Description:
// Your country has an infinite number of lakes. Initially, all the lakes are empty, but when it rains over the nth lake, the nth lake becomes full of water. If it rains over a lake that is full of water, there will be a flood. Your goal is to avoid floods in any lake.
//
// Given an integer array rains where:
//
//
// 	rains[i] > 0 means there will be rains over the rains[i] lake.
// 	rains[i] == 0 means there are no rains this day and you can choose one lake this day and dry it.
//
//
// Return an array ans where:
//
//
// 	ans.length == rains.length
// 	ans[i] == -1 if rains[i] > 0.
// 	ans[i] is the lake you choose to dry in the ith day if rains[i] == 0.
//
//
// If there are multiple valid answers return any of them. If it is impossible to avoid flood return an empty array.
//
// Notice that if you chose to dry a full lake, it becomes empty, but if you chose to dry an empty lake, nothing changes.
//
// Example:
// Input: rains = [1,2,3,4]
// Output: [-1,-1,-1,-1]
// Explanation: After the first day full lakes are [1]
// After the second day full lakes are [1,2]
// After the third day full lakes are [1,2,3]
// After the fourth day full lakes are [1,2,3,4]
// There's no day to dry any lake and there is no flood in any lake.
//
// Constraints:
// 1 <= rains.length <= 105
// 	0 <= rains[i] <= 109
//

class Solution {
public:
    vector<int> avoidFlood(vector<int>& rains) {
        int n = rains.size();
        vector<int> result(n, 1);
        unordered_map<int, int> fullLakes; // lake -> day it got full
        set<int> dryDays; // days available to dry lakes

        for (int day = 0; day < n; ++day) {
            int lake = rains[day];
            if (lake > 0) {
                // It rains on lake
                if (fullLakes.count(lake)) {
                    // Lake is already full, need to find a dry day
                    int lastFullDay = fullLakes[lake];
                    auto it = dryDays.lower_bound(lastFullDay);
                    if (it == dryDays.end()) {
                        // No available dry day, flood occurs
                        return {};
                    }
                    // Dry the lake on the found dry day
                    int dryDay = *it;
                    result[dryDay] = lake;
                    dryDays.erase(it);
                }
                // Mark the lake as full on this day
                fullLakes[lake] = day;
                result[day] = -1; // It rained today
            } else {
                // It's a dry day, add to available dry days
                dryDays.insert(day);
            }
        }

        return result;          
    }
};
