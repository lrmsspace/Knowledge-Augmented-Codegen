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

int minNumber(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int min1 = 10, min2 = 10;
    int common = 10;

    for (int i = 0; i < nums1Size; i++) {
        if (nums1[i] < min1) {
            min1 = nums1[i];
        }
        for (int j = 0; j < nums2Size; j++) {
            if (nums1[i] == nums2[j] && nums1[i] < common) {
                common = nums1[i];
            }
        }
    }

    for (int i = 0; i < nums2Size; i++) {
        if (nums2[i] < min2) {
            min2 = nums2[i];
        }
    }

    if (common != 10) {
        return common;
    } else {
        return (min1 < min2) ? (min1 * 10 + min2) : (min2 * 10 + min1);
    }       
}
