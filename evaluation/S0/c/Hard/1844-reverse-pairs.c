// Source: https://leetcode.com/problems/reverse-pairs/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums, return the number of reverse pairs in the array.
//
// A reverse pair is a pair (i, j) where:
//
//
// 	0 <= i < j < nums.length and
// 	nums[i] > 2 * nums[j].
//
// Example:
// Input: nums = [1,3,2,3,1]
// Output: 2
// Explanation: The reverse pairs are:
// (1, 4) --> nums[1] = 3, nums[4] = 1, 3 > 2 * 1
// (3, 4) --> nums[3] = 3, nums[4] = 1, 3 > 2 * 1
//
// Constraints:
// 1 <= nums.length <= 5 * 104
// 	-231 <= nums[i] <= 231 - 1
//

int reversePairs(int* nums, int numsSize) {
    if (numsSize <= 1) return 0;

    int *temp = (int*)malloc(numsSize * sizeof(int));
    if (!temp) return 0;

    int merge_sort(int *arr, int left, int right) {
        if (left >= right) return 0;
        int mid = left + (right - left) / 2;
        int count = merge_sort(arr, left, mid) + merge_sort(arr, mid + 1, right);

        // Count reverse pairs
        int j = mid + 1;
        for (int i = left; i <= mid; ++i) {
            while (j <= right && (long)arr[i] > 2 * (long)arr[j]) {
                j++;
            }
            count += (j - (mid + 1));
        }

        // Merge step
        int i = left; j = mid + 1; int k = left;
        while (i <= mid && j <= right) {
            if (arr[i] <= arr[j]) {
                temp[k++] = arr[i++];
            } else {
                temp[k++] = arr[j++];
            }
        }
        while (i <= mid) temp[k++] = arr[i++];
        while (j <= right) temp[k++] = arr[j++];
        for (i = left; i <= right; ++i) {
            arr[i] = temp[i];
        }
        return count;
    }

    int result = merge_sort(nums, 0, numsSize - 1);
    free(temp);
    return result;      
}
