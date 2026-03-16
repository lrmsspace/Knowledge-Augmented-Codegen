// Source: https://leetcode.com/problems/happy-students/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums of length n where n is the total number of students in the class. The class teacher tries to select a group of students so that all the students remain happy.
//
// The ith student will become happy if one of these two conditions is met:
//
//
// 	The student is selected and the total number of selected students is strictly greater than nums[i].
// 	The student is not selected and the total number of selected students is strictly less than nums[i].
//
//
// Return the number of ways to select a group of students so that everyone remains happy.
//
// Example:
// Input: nums = [1,1]
// Output: 2
// Explanation: 
// The two possible ways are:
// The class teacher selects no student.
// The class teacher selects both students to form the group. 
// If the class teacher selects just one student to form a group then the both students will not be happy. Therefore, there are only two possible ways.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] < nums.length
//

class Solution {
public:
    int countWays(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        int n = nums.size();
        sort(nums.begin(), nums.end());

        int ways = 0;
        for (int selected = 0; selected <= n; ++selected) {
            // Check if 'selected' students can make everyone happy
            // Students with nums[i] < selected should be selected
            // Students with nums[i] >= selected should not be selected
            int lessCount = lower_bound(nums.begin(), nums.end(), selected) - nums.begin();
            int greaterCount = n - upper_bound(nums.begin(), nums.end(), selected - 1);

            if (lessCount <= selected && greaterCount <= n - selected) {
                ways = (ways + 1) % MOD;
            }
        }

        return ways;            
    }
};
