// Source: https://leetcode.com/problems/maximum-number-of-weeks-for-which-you-can-work/   |   Difficulty: Medium
//
// Problem Description:
// There are n projects numbered from 0 to n - 1. You are given an integer array milestones where each milestones[i] denotes the number of milestones the ith project has.
//
// You can work on the projects following these two rules:
//
//
// 	Every week, you will finish exactly one milestone of one project. You must work every week.
// 	You cannot work on two milestones from the same project for two consecutive weeks.
//
//
// Once all the milestones of all the projects are finished, or if the only milestones that you can work on will cause you to violate the above rules, you will stop working. Note that you may not be able to finish every project's milestones due to these constraints.
//
// Return the maximum number of weeks you would be able to work on the projects without violating the rules mentioned above.
//
// Example:
// Input: milestones = [1,2,3]
// Output: 6
// Explanation: One possible scenario is:
// ​​​​- During the 1st week, you will work on a milestone of project 0.
// - During the 2nd week, you will work on a milestone of project 2.
// - During the 3rd week, you will work on a milestone of project 1.
// - During the 4th week, you will work on a milestone of project 2.
// - During the 5th week, you will work on a milestone of project 1.
// - During the 6th week, you will work on a milestone of project 2.
// The total number of weeks is 6.
//
// Constraints:
// n == milestones.length
// 	1 <= n <= 105
// 	1 <= milestones[i] <= 109
//

class Solution {
    public long numberOfWeeks(int[] milestones) {
        long totalMilestones = 0;
        int maxMilestones = 0;

        for (int milestone : milestones) {
            totalMilestones += milestone;
            maxMilestones = Math.max(maxMilestones, milestone);
        }

        long remainingMilestones = totalMilestones - maxMilestones;

        if (maxMilestones > remainingMilestones + 1) {
            return remainingMilestones * 2 + 1;
        } else {
            return totalMilestones;
        }           
    }
}
