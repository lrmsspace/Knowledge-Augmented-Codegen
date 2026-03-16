// Source: https://leetcode.com/problems/longest-well-performing-interval/   |   Difficulty: Medium
//
// Problem Description:
// We are given hours, a list of the number of hours worked per day for a given employee.
//
// A day is considered to be a tiring day if and only if the number of hours worked is (strictly) greater than 8.
//
// A well-performing interval is an interval of days for which the number of tiring days is strictly larger than the number of non-tiring days.
//
// Return the length of the longest well-performing interval.
//
// Example:
// Input: hours = [9,9,6,0,6,6,9]
// Output: 3
// Explanation: The longest well-performing interval is [9,9,6].
//
// Constraints:
// 1 <= hours.length <= 104
// 	0 <= hours[i] <= 16
//

class Solution {
    public int longestWPI(int[] hours) {
        int n = hours.length;
        int[] prefixSum = new int[n + 1];
        for (int i = 0; i < n; i++) {
            prefixSum[i + 1] = prefixSum[i] + (hours[i] > 8 ? 1 : -1);
        }

        int maxLength = 0;
        java.util.Deque<Integer> stack = new java.util.ArrayDeque<>();
        for (int i = 0; i <= n; i++) {
            if (stack.isEmpty() || prefixSum[i] < prefixSum[stack.peek()]) {
                stack.push(i);
            }
        }

        for (int i = n; i >= 0; i--) {
            while (!stack.isEmpty() && prefixSum[i] > prefixSum[stack.peek()]) {
                maxLength = Math.max(maxLength, i - stack.pop());
            }
        }

        return maxLength;           
    }
}
