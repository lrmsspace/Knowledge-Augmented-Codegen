// Source: https://leetcode.com/problems/intersection-of-two-arrays-ii/   |   Difficulty: Easy
//
// Problem Description:
// Given two integer arrays nums1 and nums2, return an array of their intersection. Each element in the result must appear as many times as it shows in both arrays and you may return the result in any order.
//
// Example:
// Input: nums1 = [1,2,2,1], nums2 = [2,2]
// Output: [2,2]
//
// Constraints:
// 1 <= nums1.length, nums2.length <= 1000
// 	0 <= nums1[i], nums2[i] <= 1000
//
//
//  
// Follow up:
//
//
// 	What if the given array is already sorted? How would you optimize your algorithm?
// 	What if nums1's size is small compared to nums2's size? Which algorithm is better?
// 	What if elements of nums2 are stored on disk, and the memory is limited such that you cannot load all elements into the memory at once?
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* intersect(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
    int count[1001] = {0};
    for (int i = 0; i < nums1Size; i++) {
        count[nums1[i]]++;
    }

    int* result = (int*)malloc(sizeof(int) * (nums1Size < nums2Size ? nums1Size : nums2Size));
    int index = 0;

    for (int i = 0; i < nums2Size; i++) {
        if (count[nums2[i]] > 0) {
            result[index++] = nums2[i];
            count[nums2[i]]--;
        }
    }

    *returnSize = index;
    return result;      
}
