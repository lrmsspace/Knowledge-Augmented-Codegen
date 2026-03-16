// Source: https://leetcode.com/problems/binary-gap/   |   Difficulty: Easy
//
// Problem Description:
// Given a positive integer n, find and return the longest distance between any two adjacent 1's in the binary representation of n. If there are no two adjacent 1's, return 0.
//
// Two 1's are adjacent if there are only 0's separating them (possibly no 0's). The distance between two 1's is the absolute difference between their bit positions. For example, the two 1's in "1001" have a distance of 3.
//
// Example:
// Input: n = 22
// Output: 2
// Explanation: 22 in binary is "10110".
// The first adjacent pair of 1's is "10110" with a distance of 2.
// The second adjacent pair of 1's is "10110" with a distance of 1.
// The answer is the largest of these two distances, which is 2.
// Note that "10110" is not a valid pair since there is a 1 separating the two 1's underlined.
//
// Constraints:
// 1 <= n <= 109
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
    public int binaryGap(int n) {
        int prev = -1; // Previous position of '1'
        int maxGap = 0; // Maximum gap found

        for (int i = 0; i < 32; i++) { // Loop through bits of n
            if ((n & (1 << i)) != 0) { // Check if the i-th bit is '1'
                if (prev != -1) { // If there's a previous '1', calculate the gap
                    maxGap = Math.max(maxGap, i - prev); // Update max gap
                }
                prev = i; // Update previous position to current
            }
        }

        return maxGap; // Return the maximum gap found          
    }
}
