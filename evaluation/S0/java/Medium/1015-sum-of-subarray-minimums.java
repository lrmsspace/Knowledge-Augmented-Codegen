// Source: https://leetcode.com/problems/sum-of-subarray-minimums/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers arr, find the sum of min(b), where b ranges over every (contiguous) subarray of arr. Since the answer may be large, return the answer modulo 109 + 7.
//
// Example:
// Input: arr = [3,1,2,4]
// Output: 17
// Explanation: 
// Subarrays are [3], [1], [2], [4], [3,1], [1,2], [2,4], [3,1,2], [1,2,4], [3,1,2,4]. 
// Minimums are 3, 1, 2, 4, 1, 1, 2, 1, 1, 1.
// Sum is 17.
//
// Constraints:
// 1 <= arr.length <= 3 * 104
// 	1 <= arr[i] <= 3 * 104
//

class Solution {
    public int sumSubarrayMins(int[] arr) {
        int n = arr.length;
        int MOD = 1_000_000_007;

        // Arrays to store the distance to the previous and next less elements
        int[] prevLess = new int[n];
        int[] nextLess = new int[n];

        // Monotonic stack for previous less elements
        Deque<Integer> stack = new ArrayDeque<>();
        for (int i = 0; i < n; i++) {
            while (!stack.isEmpty() && arr[stack.peek()] > arr[i]) {
                stack.pop();
            }
            prevLess[i] = stack.isEmpty() ? i + 1 : i - stack.peek();
            stack.push(i);
        }

        // Clear the stack for next less elements
        stack.clear();
        for (int i = n - 1; i >= 0; i--) {
            while (!stack.isEmpty() && arr[stack.peek()] >= arr[i]) {
                stack.pop();
            }
            nextLess[i] = stack.isEmpty() ? n - i : stack.peek() - i;
            stack.push(i);
        }

        // Calculate the result using the distances
        long result = 0;
        for (int i = 0; i < n; i++) {
            result = (result + (long) arr[i] * prevLess[i] * nextLess[i]) % MOD;
        }

        return (int) result;            
    }
}
