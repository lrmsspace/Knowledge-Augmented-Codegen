// Source: https://leetcode.com/problems/maximize-score-of-numbers-in-ranges/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of integers start and an integer d, representing n intervals [start[i], start[i] + d].
//
// You are asked to choose n integers where the ith integer must belong to the ith interval. The score of the chosen integers is defined as the minimum absolute difference between any two integers that have been chosen.
//
// Return the maximum possible score of the chosen integers.
//
// Example:
// Input: start = [6,0,3], d = 2
//
// Output: 4
//
// Explanation:
//
// The maximum possible score can be obtained by choosing integers: 8, 0, and 4. The score of these chosen integers is min(|8 - 0|, |8 - 4|, |0 - 4|) which equals 4.
//
// Constraints:
// 2 <= start.length <= 105
// 	0 <= start[i] <= 109
// 	0 <= d <= 109
//

class Solution {
public:
    int maxPossibleScore(vector<int>& start, int d) {
        sort(start.begin(), start.end());
        int n = start.size();
        int left = 0, right = d;

        auto canAchieve = [&](int score) {
            long long lastChosen = (long long)start[0] + d; // Choose the largest possible in the first interval
            for (int i = 1; i < n; ++i) {
                long long minChoice = (long long)start[i];
                long long maxChoice = (long long)start[i] + d;
                if (lastChosen + score <= maxChoice) {
                    lastChosen = max(lastChosen + score, minChoice);
                } else {
                    return false;
                }
            }
            return true;
        };

        int result = 0;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (canAchieve(mid)) {
                result = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return result;          
    }
};
