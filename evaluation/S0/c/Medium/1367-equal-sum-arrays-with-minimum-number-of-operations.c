// Source: https://leetcode.com/problems/equal-sum-arrays-with-minimum-number-of-operations/   |   Difficulty: Medium
//
// Problem Description:
// You are given two arrays of integers nums1 and nums2, possibly of different lengths. The values in the arrays are between 1 and 6, inclusive.
//
// In one operation, you can change any integer's value in any of the arrays to any value between 1 and 6, inclusive.
//
// Return the minimum number of operations required to make the sum of values in nums1 equal to the sum of values in nums2. Return -1​​​​​ if it is not possible to make the sum of the two arrays equal.
//
// Example:
// Input: nums1 = [1,2,3,4,5,6], nums2 = [1,1,2,2,2,2]
// Output: 3
// Explanation: You can make the sums of nums1 and nums2 equal with 3 operations. All indices are 0-indexed.
// - Change nums2[0] to 6. nums1 = [1,2,3,4,5,6], nums2 = [6,1,2,2,2,2].
// - Change nums1[5] to 1. nums1 = [1,2,3,4,5,1], nums2 = [6,1,2,2,2,2].
// - Change nums1[2] to 2. nums1 = [1,2,2,4,5,1], nums2 = [6,1,2,2,2,2].
//
// Constraints:
// 1 <= nums1.length, nums2.length <= 105
// 	1 <= nums1[i], nums2[i] <= 6
//

int minOperations(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int sum1 = 0, sum2 = 0;
    for (int i = 0; i < nums1Size; i++) {
        sum1 += nums1[i];
    }
    for (int i = 0; i < nums2Size; i++) {
        sum2 += nums2[i];
    }
    if (sum1 == sum2) {
        return 0;
    }
    if (sum1 > sum2) {
        // Swap to always have sum1 < sum2
        int* tempNums = nums1;
        nums1 = nums2;
        nums2 = tempNums;
        int tempSize = nums1Size;
        nums1Size = nums2Size;
        nums2Size = tempSize;
        int tempSum = sum1;
        sum1 = sum2;
        sum2 = tempSum;
    }

    int diff = sum2 - sum1;
    int count[6] = {0}; // count[i] is the number of elements that can contribute (i+1) to the difference
    for (int i = 0; i < nums1Size; i++) {
        count[6 - nums1[i]]++;
    }
    for (int i = 0; i < nums2Size; i++) {
        count[nums2[i] - 1]++;
    }

    int operations = 0;
    for (int i = 5; i >= 1 && diff > 0; i--) {
        while (count[i] > 0 && diff > 0) {
            diff -= i;
            count[i]--;
            operations++;
        }
    }

    return diff > 0 ? -1 : operations;      
}
