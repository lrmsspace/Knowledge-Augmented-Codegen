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

int numberOfPoints(int** nums, int numsSize, int* numsColSize) {
    int covered[101] = {0};
    for (int i = 0; i < numsSize; i++) {
        for (int j = nums[i][0]; j <= nums[i][1]; j++) {
            covered[j] = 1;
        }
    }
    int count = 0;
    for (int i = 1; i <= 100; i++) {
        if (covered[i]) {
            count++;
        }
    }
    return count;       
}
