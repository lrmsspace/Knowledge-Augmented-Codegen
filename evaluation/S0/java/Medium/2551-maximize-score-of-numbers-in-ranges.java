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
    public int maxPossibleScore(int[] start, int d) {
        Arrays.sort(start);
        int left = 0;
        int right = d + 1;

        while (left < right) {
            int mid = left + (right - left + 1) / 2;
            if (canPlaceNumbers(start, d, mid)) {
                left = mid;
            } else {
                right = mid - 1;
            }
        }

        return left;            
    }
}
