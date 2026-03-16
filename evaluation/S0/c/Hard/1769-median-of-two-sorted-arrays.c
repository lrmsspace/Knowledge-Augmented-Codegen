// Source: https://leetcode.com/problems/median-of-two-sorted-arrays/   |   Difficulty: Hard
//
// Problem Description:
// Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.
//
// The overall run time complexity should be O(log (m+n)).
//
// Example:
// Input: nums1 = [1,3], nums2 = [2]
// Output: 2.00000
// Explanation: merged array = [1,2,3] and median is 2.
//
// Constraints:
// nums1.length == m
// 	nums2.length == n
// 	0 <= m <= 1000
// 	0 <= n <= 1000
// 	1 <= m + n <= 2000
// 	-106 <= nums1[i], nums2[i] <= 106
//

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    if (nums1Size > nums2Size) {
        // Ensure nums1 is the smaller array
        return findMedianSortedArrays(nums2, nums2Size, nums1, nums1Size);
    }

    int x = nums1Size;
    int y = nums2Size;
    int low = 0, high = x;

    while (low <= high) {
        int partitionX = (low + high) / 2;
        int partitionY = (x + y + 1) / 2 - partitionX;

        int maxX = (partitionX == 0) ? INT_MIN : nums1[partitionX - 1];
        int minX = (partitionX == x) ? INT_MAX : nums1[partitionX];

        int maxY = (partitionY == 0) ? INT_MIN : nums2[partitionY - 1];
        int minY = (partitionY == y) ? INT_MAX : nums2[partitionY];

        if (maxX <= minY && maxY <= minX) {
            // Found the correct partitions
            if ((x + y) % 2 == 0) {
                return ((double)(fmax(maxX, maxY) + fmin(minX, minY))) / 2;
            } else {
                return (double)fmax(maxX, maxY);
            }
        } else if (maxX > minY) {
            // Move towards the left in nums1
            high = partitionX - 1;
        } else {
            // Move towards the right in nums1
            low = partitionX + 1;
        }
    }

    // If we reach here, the input arrays were not sorted as expected
    return 0.0;     
}
