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
    public long maximumTotalSum(int[] maximumHeight) {
        Arrays.sort(maximumHeight);
        long totalHeight = 0;
        long currentMaxHeight = Long.MAX_VALUE;

        for (int i = maximumHeight.length - 1; i >= 0; i--) {
            if (currentMaxHeight > 1) {
                currentMaxHeight = Math.min(currentMaxHeight - 1, maximumHeight[i]);
                totalHeight += currentMaxHeight;
            } else if (currentMaxHeight == 1) {
                totalHeight += 1;
                currentMaxHeight = 0; // No more heights can be assigned
            } else {
                return -1; // Not possible to assign unique heights
            }
        }

        return totalHeight;         
    }
}
