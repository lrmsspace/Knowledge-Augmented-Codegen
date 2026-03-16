// Source: https://leetcode.com/problems/kth-smallest-product-of-two-sorted-arrays/   |   Difficulty: Hard
//
// Problem Description:
// Given two sorted 0-indexed integer arrays nums1 and nums2 as well as an integer k, return the kth (1-based) smallest product of nums1[i] * nums2[j] where 0 <= i < nums1.length and 0 <= j < nums2.length.
//
// Example:
// Input: nums1 = [2,5], nums2 = [3,4], k = 2
// Output: 8
// Explanation: The 2 smallest products are:
// - nums1[0] * nums2[0] = 2 * 3 = 6
// - nums1[0] * nums2[1] = 2 * 4 = 8
// The 2nd smallest product is 8.
//
// Constraints:
// 1 <= nums1.length, nums2.length <= 5 * 104
// 	-105 <= nums1[i], nums2[j] <= 105
// 	1 <= k <= nums1.length * nums2.length
// 	nums1 and nums2 are sorted.
//

class Solution {
public:
    long long kthSmallestProduct(vector<int>& nums1, vector<int>& nums2, long long k) {
        long long left = -1e10, right = 1e10;
        
        auto countLessEqual = [&](long long mid) {
            long long count = 0;
            for (int num1 : nums1) {
                if (num1 == 0) {
                    if (mid >= 0) count += nums2.size();
                } else if (num1 > 0) {
                    int l = 0, r = nums2.size();
                    while (l < r) {
                        int m = l + (r - l) / 2;
                        if ((long long)num1 * nums2[m] <= mid) {
                            l = m + 1;
                        } else {
                            r = m;
                        }
                    }
                    count += l;
                } else { // num1 < 0
                    int l = 0, r = nums2.size();
                    while (l < r) {
                        int m = l + (r - l) / 2;
                        if ((long long)num1 * nums2[m] <= mid) {
                            r = m;
                        } else {
                            l = m + 1;
                        }
                    }
                    count += nums2.size() - l;
                }
            }
            return count;
        };
        
        while (left < right) {
            long long mid = left + (right - left) / 2;
            if (countLessEqual(mid) < k) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        
        return left;            
    }
};
