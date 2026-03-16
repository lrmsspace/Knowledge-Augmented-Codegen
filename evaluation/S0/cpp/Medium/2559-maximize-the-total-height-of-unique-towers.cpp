// Source: https://leetcode.com/problems/maximize-the-total-height-of-unique-towers/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array maximumHeight, where maximumHeight[i] denotes the maximum height the ith tower can be assigned.
//
// Your task is to assign a height to each tower so that:
//
//
// 	The height of the ith tower is a positive integer and does not exceed maximumHeight[i].
// 	No two towers have the same height.
//
//
// Return the maximum possible total sum of the tower heights. If it's not possible to assign heights, return -1.
//
// Example:
// Input: maximumHeight = [2,3,4,3]
//
// Output: 10
//
// Explanation:
//
// We can assign heights in the following way: [1, 2, 4, 3].
//
// Constraints:
// 1 <= maximumHeight.length <= 105
// 	1 <= maximumHeight[i] <= 109
//

class Solution {
public:
    long long maximumTotalSum(vector<int>& maximumHeight) {
        sort(maximumHeight.begin(), maximumHeight.end());
        long long totalSum = 0;
        long long currentHeight = LLONG_MAX;

        for (int i = maximumHeight.size() - 1; i >= 0; --i) {
            if (currentHeight > maximumHeight[i]) {
                currentHeight = maximumHeight[i];
            }
            if (currentHeight <= 0) {
                return -1;
            }
            totalSum += currentHeight;
            --currentHeight;
        }

        return totalSum;            
    }
};
