// Source: https://leetcode.com/problems/minimum-number-of-taps-to-open-to-water-a-garden/   |   Difficulty: Hard
//
// Problem Description:
// There is a one-dimensional garden on the x-axis. The garden starts at the point 0 and ends at the point n. (i.e., the length of the garden is n).
//
// There are n + 1 taps located at points [0, 1, ..., n] in the garden.
//
// Given an integer n and an integer array ranges of length n + 1 where ranges[i] (0-indexed) means the i-th tap can water the area [i - ranges[i], i + ranges[i]] if it was open.
//
// Return the minimum number of taps that should be open to water the whole garden, If the garden cannot be watered return -1.
//
// Example:
// Input: n = 5, ranges = [3,4,1,1,0,0]
// Output: 1
// Explanation: The tap at point 0 can cover the interval [-3,3]
// The tap at point 1 can cover the interval [-3,5]
// The tap at point 2 can cover the interval [1,3]
// The tap at point 3 can cover the interval [2,4]
// The tap at point 4 can cover the interval [4,4]
// The tap at point 5 can cover the interval [5,5]
// Opening Only the second tap will water the whole garden [0,5]
//
// Constraints:
// 1 <= n <= 104
// 	ranges.length == n + 1
// 	0 <= ranges[i] <= 100
//

class Solution {
    public int minTaps(int n, int[] ranges) {
        int[] maxReach = new int[n + 1];
        for (int i = 0; i <= n; i++) {
            int left = Math.max(0, i - ranges[i]);
            int right = Math.min(n, i + ranges[i]);
            maxReach[left] = Math.max(maxReach[left], right);
        }

        int tapsOpened = 0;
        int currentEnd = 0;
        int farthest = 0;

        for (int i = 0; i <= n; i++) {
            if (i > farthest) {
                return -1; // Cannot reach this point
            }
            if (i > currentEnd) {
                tapsOpened++;
                currentEnd = farthest;
            }
            farthest = Math.max(farthest, maxReach[i]);
        }

        return tapsOpened;                  
    }
}
