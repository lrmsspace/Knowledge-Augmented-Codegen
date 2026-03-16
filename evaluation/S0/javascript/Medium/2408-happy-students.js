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

/**
 * @param {number[]} nums
 * @return {number}
 */
var countWays = function(nums) {
    nums.sort((a, b) => a - b);
    let ways = 0;
    const n = nums.length;
    for (let i = 0; i <= n; i++) {
        const left = i > 0 ? nums[i - 1] : -1;
        const right = i < n ? nums[i] : n;
        if (left < i && i < right) {
            ways++;
        }
    }
    return ways;
};