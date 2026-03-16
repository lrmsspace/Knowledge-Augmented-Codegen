// Source: https://leetcode.com/problems/points-that-intersect-with-cars/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed 2D integer array nums representing the coordinates of the cars parking on a number line. For any index i, nums[i] = [starti, endi] where starti is the starting point of the ith car and endi is the ending point of the ith car.
//
// Return the number of integer points on the line that are covered with any part of a car.
//
// Example:
// Input: nums = [[3,6],[1,5],[4,7]]
// Output: 7
// Explanation: All the points from 1 to 7 intersect at least one car, therefore the answer would be 7.
//
// Constraints:
// 1 <= nums.length <= 100
// 	nums[i].length == 2
// 	1 <= starti <= endi <= 100
//

class Solution {
public:
    int numberOfPoints(vector<vector<int>>& nums) {
        vector<bool> covered(101, false);
        for (const auto& car : nums) {
            for (int point = car[0]; point <= car[1]; ++point) {
                covered[point] = true;
            }
        }
        return count(covered.begin(), covered.end(), true);         
    }
};
