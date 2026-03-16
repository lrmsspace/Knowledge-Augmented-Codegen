// Source: https://leetcode.com/problems/minimum-number-of-seconds-to-make-mountain-height-zero/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer mountainHeight denoting the height of a mountain.
//
// You are also given an integer array workerTimes representing the work time of workers in seconds.
//
// The workers work simultaneously to reduce the height of the mountain. For worker i:
//
//
// 	To decrease the mountain's height by x, it takes workerTimes[i] + workerTimes[i] * 2 + ... + workerTimes[i] * x seconds. For example:
//
// 	
// 		To reduce the height of the mountain by 1, it takes workerTimes[i] seconds.
// 		To reduce the height of the mountain by 2, it takes workerTimes[i] + workerTimes[i] * 2 seconds, and so on.
// 	
// 	
//
//
// Return an integer representing the minimum number of seconds required for the workers to make the height of the mountain 0.
//
// Example:
// Input: mountainHeight = 4, workerTimes = [2,1,1]
//
// Output: 3
//
// Explanation:
//
// One way the height of the mountain can be reduced to 0 is:
//
//
// 	Worker 0 reduces the height by 1, taking workerTimes[0] = 2 seconds.
// 	Worker 1 reduces the height by 2, taking workerTimes[1] + workerTimes[1] * 2 = 3 seconds.
// 	Worker 2 reduces the height by 1, taking workerTimes[2] = 1 second.
//
//
// Since they work simultaneously, the minimum time needed is max(2, 3, 1) = 3 seconds.
//
// Constraints:
// 1 <= mountainHeight <= 105
// 	1 <= workerTimes.length <= 104
// 	1 <= workerTimes[i] <= 106
//

class Solution {
    public long minNumberOfSeconds(int mountainHeight, int[] workerTimes) {
        long left = 1, right = (long) 1e15;
        long result = right;

        while (left <= right) {
            long mid = left + (right - left) / 2;
            if (canReduceToZero(mountainHeight, workerTimes, mid)) {
                result = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        return result;          
    }
}
