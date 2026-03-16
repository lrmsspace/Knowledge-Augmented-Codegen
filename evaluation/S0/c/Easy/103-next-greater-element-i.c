// Source: https://leetcode.com/problems/next-greater-element-i/   |   Difficulty: Easy
//
// Problem Description:
// The next greater element of some element x in an array is the first greater element that is to the right of x in the same array.
//
// You are given two distinct 0-indexed integer arrays nums1 and nums2, where nums1 is a subset of nums2.
//
// For each 0 <= i < nums1.length, find the index j such that nums1[i] == nums2[j] and determine the next greater element of nums2[j] in nums2. If there is no next greater element, then the answer for this query is -1.
//
// Return an array ans of length nums1.length such that ans[i] is the next greater element as described above.
//
// Example:
// Input: nums1 = [4,1,2], nums2 = [1,3,4,2]
// Output: [-1,3,-1]
// Explanation: The next greater element for each value of nums1 is as follows:
// - 4 is underlined in nums2 = [1,3,4,2]. There is no next greater element, so the answer is -1.
// - 1 is underlined in nums2 = [1,3,4,2]. The next greater element is 3.
// - 2 is underlined in nums2 = [1,3,4,2]. There is no next greater element, so the answer is -1.
//
// Constraints:
// 1 <= nums1.length <= nums2.length <= 1000
// 	0 <= nums1[i], nums2[i] <= 104
// 	All integers in nums1 and nums2 are unique.
// 	All the integers of nums1 also appear in nums2.
//
//
//  
// Follow up: Could you find an O(nums1.length + nums2.length) solution?
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* nextGreaterElement(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
    int *res = (int *)malloc(nums1Size * sizeof(int));
    *returnSize = nums1Size;
    for (int i = 0; i < nums1Size; i++) {
        res[i] = -1;  // Default to -1
        for (int j = 0; j < nums2Size; j++) {
            if (nums1[i] == nums2[j]) {
                // Found the element in nums2, now look for the next greater element
                for (int k = j + 1; k < nums2Size; k++) {
                    if (nums2[k] > nums1[i]) {
                        res[i] = nums2[k];
                        break;
                    }
                }
                break;  // No need to continue searching in nums2
            }
        }
    }
    return res;     
}
