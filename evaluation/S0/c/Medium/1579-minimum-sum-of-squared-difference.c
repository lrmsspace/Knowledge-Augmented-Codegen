// Source: https://leetcode.com/problems/minimum-sum-of-squared-difference/   |   Difficulty: Medium
//
// Problem Description:
// You are given two positive 0-indexed integer arrays nums1 and nums2, both of length n.
//
// The sum of squared difference of arrays nums1 and nums2 is defined as the sum of (nums1[i] - nums2[i])2 for each 0 <= i < n.
//
// You are also given two positive integers k1 and k2. You can modify any of the elements of nums1 by +1 or -1 at most k1 times. Similarly, you can modify any of the elements of nums2 by +1 or -1 at most k2 times.
//
// Return the minimum sum of squared difference after modifying array nums1 at most k1 times and modifying array nums2 at most k2 times.
//
// Note: You are allowed to modify the array elements to become negative integers.
//
// Example:
// Input: nums1 = [1,2,3,4], nums2 = [2,10,20,19], k1 = 0, k2 = 0
// Output: 579
// Explanation: The elements in nums1 and nums2 cannot be modified because k1 = 0 and k2 = 0. 
// The sum of square difference will be: (1 - 2)2 + (2 - 10)2 + (3 - 20)2 + (4 - 19)2 = 579.
//
// Constraints:
// n == nums1.length == nums2.length
// 	1 <= n <= 105
// 	0 <= nums1[i], nums2[i] <= 105
// 	0 <= k1, k2 <= 109
//

long long minSumSquareDiff(int* nums1, int nums1Size, int* nums2, int nums2Size, int k1, int k2) {
    int n = nums1Size;
    long long k = (long long)k1 + (long long)k2;
    int diffs[n];
    for (int i = 0; i < n; i++) {
        diffs[i] = abs(nums1[i] - nums2[i]);
    }

    // Counting sort
    int maxDiff = 0;
    for (int i = 0; i < n; i++) {
        if (diffs[i] > maxDiff) {
            maxDiff = diffs[i];
        }
    }
    int count[maxDiff + 1];
    for (int i = 0; i <= maxDiff; i++) {
        count[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        count[diffs[i]]++;
    }

    // Reduce differences starting from the largest
    for (int d = maxDiff; d > 0 && k > 0; d--) {
        if (count[d] == 0) continue;
        long long totalReduce = (long long)count[d];
        if (totalReduce <= k) {
            count[d - 1] += count[d];
            k -= totalReduce;
            count[d] = 0;
        } else {
            long long fullReductions = k / totalReduce;
            long long remainder = k % totalReduce;
            if (fullReductions > 0) {
                count[d - fullReductions] += count[d];
                count[d] = 0;
            }
            if (remainder > 0) {
                count[d - fullReductions] += remainder;
                count[d - fullReductions - 1] += (totalReduce - remainder);
                count[d] = 0;
            }
            k = 0;
        }
    }

    // Calculate the final sum of squared differences
    long long result = 0;
    for (int d = 0; d <= maxDiff; d++) {
        if (count[d] > 0) {
            result += (long long)count[d] * d * d;
        }
    }

    return result;      
}
