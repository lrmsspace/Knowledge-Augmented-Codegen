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

class Solution {
public:
    int findMinDifference(vector<string>& timePoints) {
        vector<int> minutesList;
        for (const auto& time : timePoints) {
            int hours = stoi(time.substr(0, 2));
            int minutes = stoi(time.substr(3, 2));
            minutesList.push_back(hours * 60 + minutes);
        }

        sort(minutesList.begin(), minutesList.end());

        int minDiff = INT_MAX;
        for (size_t i = 1; i < minutesList.size(); ++i) {
            minDiff = min(minDiff, minutesList[i] - minutesList[i - 1]);
        }

        // Check the difference between the last and first time points across midnight
        minDiff = min(minDiff, (1440 - minutesList.back() + minutesList.front()));

        return minDiff;         
    }
};
