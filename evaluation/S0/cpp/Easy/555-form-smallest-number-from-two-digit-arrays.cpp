// Source: https://leetcode.com/problems/form-smallest-number-from-two-digit-arrays/   |   Difficulty: Easy
//
// Problem Description:
// Given two arrays of unique digits nums1 and nums2, return the smallest number that contains at least one digit from each array.
//
// Example:
// Input: nums1 = [4,1,3], nums2 = [5,7]
// Output: 15
// Explanation: The number 15 contains the digit 1 from nums1 and the digit 5 from nums2. It can be proven that 15 is the smallest number we can have.
//
// Constraints:
// 1 <= nums1.length, nums2.length <= 9
// 	1 <= nums1[i], nums2[i] <= 9
// 	All digits in each array are unique.
//

class Solution {
public:
    int minNumber(vector<int>& nums1, vector<int>& nums2) {
        int min1 = *min_element(nums1.begin(), nums1.end());
        int min2 = *min_element(nums2.begin(), nums2.end());

        int res = min1 * 10 + min2;
        for (int n1 : nums1) {
            for (int n2 : nums2) {
                if (n1 == n2) {
                    res = min(res, n1);
                } else {
                    res = min(res, min(n1, n2) * 10 + max(n1, n2));
                }
            }
        }

        return res;         
    }
};
