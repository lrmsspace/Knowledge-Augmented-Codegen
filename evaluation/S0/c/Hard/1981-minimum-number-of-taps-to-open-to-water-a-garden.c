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

int minTaps(int n, int* ranges, int rangesSize) {
    int maxReach[n + 1];
    for (int i = 0; i <= n; ++i) {
        maxReach[i] = 0;
    }

    for (int i = 0; i <= n; ++i) {
        int left = i - ranges[i];
        int right = i + ranges[i];
        if (right < 0 || left > n) continue;
        if (left < 0) left = 0;
        if (right > n) right = n;
        if (maxReach[left] < right) {
            maxReach[left] = right;
        }
    }

    int taps = 0;
    int currEnd = 0;
    int nextEnd = 0;

    for (int i = 0; i <= n; ++i) {
        if (i > nextEnd) {
            return -1; // Cannot reach this point
        }
        if (i > currEnd) {
            taps++;
            currEnd = nextEnd;
        }
        if (maxReach[i] > nextEnd) {
            nextEnd = maxReach[i];
        }
    }

    return taps;        
}
