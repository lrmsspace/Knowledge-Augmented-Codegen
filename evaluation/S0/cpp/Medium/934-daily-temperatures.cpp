// Source: https://leetcode.com/problems/daily-temperatures/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers temperatures represents the daily temperatures, return an array answer such that answer[i] is the number of days you have to wait after the ith day to get a warmer temperature. If there is no future day for which this is possible, keep answer[i] == 0 instead.
//
// Example:
// Input: temperatures = [73,74,75,71,69,72,76,73]
// Output: [1,1,4,2,1,1,0,0]
//
// Constraints:
// 1 <= temperatures.length <= 105
// 	30 <= temperatures[i] <= 100
//

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> answer(n, 0);
        stack<int> s; // stores indices of temperatures

        for (int i = 0; i < n; ++i) {
            while (!s.empty() && temperatures[i] > temperatures[s.top()]) {
                int idx = s.top();
                s.pop();
                answer[idx] = i - idx;
            }
            s.push(i);
        }

        return answer;          
    }
};
