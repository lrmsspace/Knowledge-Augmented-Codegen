// Source: https://leetcode.com/problems/last-moment-before-all-ants-fall-out-of-a-plank/   |   Difficulty: Medium
//
// Problem Description:
// We have a wooden plank of the length n units. Some ants are walking on the plank, each ant moves with a speed of 1 unit per second. Some of the ants move to the left, the other move to the right.
//
// When two ants moving in two different directions meet at some point, they change their directions and continue moving again. Assume changing directions does not take any additional time.
//
// When an ant reaches one end of the plank at a time t, it falls out of the plank immediately.
//
// Given an integer n and two integer arrays left and right, the positions of the ants moving to the left and the right, return the moment when the last ant(s) fall out of the plank.
//
// Example:
// Input: n = 4, left = [4,3], right = [0,1]
// Output: 4
// Explanation: In the image above:
// -The ant at index 0 is named A and going to the right.
// -The ant at index 1 is named B and going to the right.
// -The ant at index 3 is named C and going to the left.
// -The ant at index 4 is named D and going to the left.
// The last moment when an ant was on the plank is t = 4 seconds. After that, it falls immediately out of the plank. (i.e., We can say that at t = 4.0000000001, there are no ants on the plank).
//
// Constraints:
// 1 <= n <= 104
// 	0 <= left.length <= n + 1
// 	0 <= left[i] <= n
// 	0 <= right.length <= n + 1
// 	0 <= right[i] <= n
// 	1 <= left.length + right.length <= n + 1
// 	All values of left and right are unique, and each value can appear only in one of the two arrays.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int getLastMoment(int n, int[] left, int[] right) {
        int maxTime = 0;

        // Calculate the time for ants moving to the left to fall off
        for (int position : left) {
            maxTime = Math.max(maxTime, position);
        }

        // Calculate the time for ants moving to the right to fall off
        for (int position : right) {
            maxTime = Math.max(maxTime, n - position);
        }

        return maxTime;         
    }
}
