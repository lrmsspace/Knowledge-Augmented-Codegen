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

class Solution {
public:
    long long minSum(vector<int>& nums1, vector<int>& nums2) {
        long long sum1 = 0, sum2 = 0;
        int zeroCount1 = 0, zeroCount2 = 0;

        for (int num : nums1) {
            if (num == 0) {
                zeroCount1++;
            } else {
                sum1 += num;
            }
        }

        for (int num : nums2) {
            if (num == 0) {
                zeroCount2++;
            } else {
                sum2 += num;
            }
        }

        long long diff = abs(sum1 - sum2);
        int totalZeros = zeroCount1 + zeroCount2;

        if (diff > totalZeros * 1000000LL) {
            return -1;
        }

        long long minSum = max(sum1, sum2) + (totalZeros * 1LL);
        return minSum;          
    }
};
