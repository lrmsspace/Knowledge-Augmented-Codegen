// Source: https://leetcode.com/problems/find-the-integer-added-to-array-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integer arrays nums1 and nums2.
//
// From nums1 two elements have been removed, and all other elements have been increased (or decreased in the case of negative) by an integer, represented by the variable x.
//
// As a result, nums1 becomes equal to nums2. Two arrays are considered equal when they contain the same integers with the same frequencies.
//
// Return the minimum possible integer x that achieves this equivalence.
//
// Example:
// Input: nums1 = [4,20,16,12,8], nums2 = [14,18,10]
//
// Output: -2
//
// Explanation:
//
// After removing elements at indices [0,4] and adding -2, nums1 becomes [18,14,10].
//
// Constraints:
// 3 <= nums1.length <= 200
// 	nums2.length == nums1.length - 2
// 	0 <= nums1[i], nums2[i] <= 1000
// 	The test cases are generated in a way that there is an integer x such that nums1 can become equal to nums2 by removing two elements and adding x to each element of nums1.
//

int minimumAddedInteger(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int min_x = 2001; // Since the maximum possible x is 1000 - 0 = 1000, we can safely initialize min_x to a value greater than 1000.
    
    for (int i = 0; i < nums1Size; i++) {
        for (int j = i + 1; j < nums1Size; j++) {
            int x = nums2[0] - nums1[(i == 0) ? 1 : 0];
            if (i == 0) {
                x = nums2[0] - nums1[1];
            } else {
                x = nums2[0] - nums1[0];
            }
            
            int* temp = (int*)malloc((nums1Size - 2) * sizeof(int));
            int index = 0;
            for (int k = 0; k < nums1Size; k++) {
                if (k != i && k != j) {
                    temp[index++] = nums1[k] + x;
                }
            }
            
            // Sort temp and nums2 to compare
            qsort(temp, nums1Size - 2, sizeof(int), (int (*)(const void*, const void*))strcmp);
            qsort(nums2, nums2Size, sizeof(int), (int (*)(const void*, const void*))strcmp);
            
            int equal = 1;
            for (int k = 0; k < nums2Size; k++) {
                if (temp[k] != nums2[k]) {
                    equal = 0;
                    break;
                }
            }
            
            if (equal) {
                if (x < min_x) {
                    min_x = x;
                }
            }
            
            free(temp);
        }
    }
    
    return min_x;       
}
