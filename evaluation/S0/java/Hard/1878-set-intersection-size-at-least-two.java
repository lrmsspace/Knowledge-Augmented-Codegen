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

class Solution {
    public int intersectionSizeTwo(int[][] intervals) {
        Arrays.sort(intervals, (a, b) -> {
            if (a[1] != b[1]) {
                return Integer.compare(a[1], b[1]);
            } else {
                return Integer.compare(b[0], a[0]);
            }
        });

        int n = intervals.length;
        int count = 0;
        int first = -1;
        int second = -1;

        for (int i = 0; i < n; i++) {
            int start = intervals[i][0];
            int end = intervals[i][1];

            if (start <= first) {
                continue;
            } else if (start <= second) {
                first = second;
                second = end;
                count += 1;
            } else {
                first = end - 1;
                second = end;
                count += 2;
            }
        }

        return count;           
    }
}
