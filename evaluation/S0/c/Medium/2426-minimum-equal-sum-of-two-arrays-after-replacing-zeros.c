// Source: https://leetcode.com/problems/minimum-equal-sum-of-two-arrays-after-replacing-zeros/   |   Difficulty: Medium
//
// Problem Description:
// You are given two arrays nums1 and nums2 consisting of positive integers.
//
// You have to replace all the 0's in both arrays with strictly positive integers such that the sum of elements of both arrays becomes equal.
//
// Return the minimum equal sum you can obtain, or -1 if it is impossible.
//
// Example:
// Input: nums1 = [3,2,0,1,0], nums2 = [6,5,0]
// Output: 12
// Explanation: We can replace 0's in the following way:
// - Replace the two 0's in nums1 with the values 2 and 4. The resulting array is nums1 = [3,2,2,1,4].
// - Replace the 0 in nums2 with the value 1. The resulting array is nums2 = [6,5,1].
// Both arrays have an equal sum of 12. It can be shown that it is the minimum sum we can obtain.
//
// Constraints:
// 1 <= nums1.length, nums2.length <= 105
// 	0 <= nums1[i], nums2[i] <= 106
//

long long minSum(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    long long sum1 = 0, sum2 = 0;
    int zeroCount1 = 0, zeroCount2 = 0;

    for (int i = 0; i < nums1Size; i++) {
        if (nums1[i] == 0) {
            zeroCount1++;
        } else {
            sum1 += nums1[i];
        }
    }

    for (int i = 0; i < nums2Size; i++) {
        if (nums2[i] == 0) {
            zeroCount2++;
        } else {
            sum2 += nums2[i];
        }
    }

    long long diff = sum1 - sum2;
    int totalZeros = zeroCount1 + zeroCount2;

    if (diff < 0) {
        long long requiredIncrease = -diff;
        if (requiredIncrease > (long long)zeroCount1 * 1000000) {
            return -1;
        }
        return sum2 + requiredIncrease + (long long)(totalZeros - zeroCount1);
    } else {
        long long requiredIncrease = diff;
        if (requiredIncrease > (long long)zeroCount2 * 1000000) {
            return -1;
        }
        return sum1 + requiredIncrease + (long long)(totalZeros - zeroCount2);
    }       
}
