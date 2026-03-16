// Source: https://leetcode.com/problems/add-minimum-number-of-rungs/   |   Difficulty: Medium
//
// Problem Description:
// You are given a strictly increasing integer array rungs that represents the height of rungs on a ladder. You are currently on the floor at height 0, and you want to reach the last rung.
//
// You are also given an integer dist. You can only climb to the next highest rung if the distance between where you are currently at (the floor or on a rung) and the next rung is at most dist. You are able to insert rungs at any positive integer height if a rung is not already there.
//
// Return the minimum number of rungs that must be added to the ladder in order for you to climb to the last rung.
//
// Example:
// Input: rungs = [1,3,5,10], dist = 2
// Output: 2
// Explanation:
// You currently cannot reach the last rung.
// Add rungs at heights 7 and 8 to climb this ladder. 
// The ladder will now have rungs at [1,3,5,7,8,10].
//
// Constraints:
// 1 <= rungs.length <= 105
// 	1 <= rungs[i] <= 109
// 	1 <= dist <= 109
// 	rungs is strictly increasing.
//

class Solution {
    public int addRungs(int[] rungs, int dist) {
        int addedRungs = 0;
        int currentHeight = 0;

        for (int rung : rungs) {
            int gap = rung - currentHeight;
            if (gap > dist) {
                addedRungs += (gap - 1) / dist;
            }
            currentHeight = rung;
        }

        return addedRungs;          
    }
}
