// Source: https://leetcode.com/problems/set-intersection-size-at-least-two/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D integer array intervals where intervals[i] = [starti, endi] represents all the integers from starti to endi inclusively.
//
// A containing set is an array nums where each interval from intervals has at least two integers in nums.
//
//
// 	For example, if intervals = [[1,3], [3,7], [8,9]], then [1,2,4,7,8,9] and [2,3,4,8,9] are containing sets.
//
//
// Return the minimum possible size of a containing set.
//
// Example:
// Input: intervals = [[1,3],[3,7],[8,9]]
// Output: 5
// Explanation: let nums = [2, 3, 4, 8, 9].
// It can be shown that there cannot be any containing array of size 4.
//
// Constraints:
// 1 <= intervals.length <= 3000
// 	intervals[i].length == 2
// 	0 <= starti < endi <= 108
//

/**
 * @param {number[][]} intervals
 * @return {number}
 */
var intersectionSizeTwo = function(intervals) {
    intervals.sort((a, b) => a[1] - b[1]);
    const nums = [];
    for (const [start, end] of intervals) {
        let count = 0;
        for (let i = nums.length - 1; i >= 0; i--) {
            if (nums[i] >= start) {
                count++;
            } else {
                break;
            }

        }
        if (count >= 2) {
            continue;
        }
        for (let i = end - count; i > end - 2; i--) {
            nums.push(i);
        }
    }
    return nums.length; 
    
};
