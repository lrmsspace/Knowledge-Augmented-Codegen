// Source: https://leetcode.com/problems/number-of-pairs-satisfying-inequality/   |   Difficulty: Hard
//
// Problem Description:
// You are given two 0-indexed integer arrays nums1 and nums2, each of size n, and an integer diff. Find the number of pairs (i, j) such that:
//
//
// 	0 <= i < j <= n - 1 and
// 	nums1[i] - nums1[j] <= nums2[i] - nums2[j] + diff.
//
//
// Return the number of pairs that satisfy the conditions.
//
// Example:
// Input: nums1 = [3,2,5], nums2 = [2,2,1], diff = 1
// Output: 3
// Explanation:
// There are 3 pairs that satisfy the conditions:
// 1. i = 0, j = 1: 3 - 2 <= 2 - 2 + 1. Since i < j and 1 <= 1, this pair satisfies the conditions.
// 2. i = 0, j = 2: 3 - 5 <= 2 - 1 + 1. Since i < j and -2 <= 2, this pair satisfies the conditions.
// 3. i = 1, j = 2: 2 - 5 <= 2 - 1 + 1. Since i < j and -3 <= 2, this pair satisfies the conditions.
// Therefore, we return 3.
//
// Constraints:
// n == nums1.length == nums2.length
// 	2 <= n <= 105
// 	-104 <= nums1[i], nums2[i] <= 104
// 	-104 <= diff <= 104
//

long long numberOfPairs(int* nums1, int nums1Size, int* nums2, int nums2Size, int diff) {
    if (!nums1 || !nums2 || nums1Size != nums2Size || nums1Size < 2) return 0;

    int n = nums1Size;
    int *arr = (int*)malloc(n * sizeof(int));
    if (!arr) return 0;
    for (int i = 0; i < n; ++i) {
        arr[i] = nums1[i] - nums2[i];
    }

    long long result = 0;

    /* Modified merge sort to count pairs */
    int *temp = (int*)malloc(n * sizeof(int));
    if (!temp) { free(arr); return 0; }

    void merge_sort(int left, int right) {
        if (left >= right) return;
        int mid = left + (right - left) / 2;
        merge_sort(left, mid);
        merge_sort(mid + 1, right);

        /* Count pairs */
        int j = mid + 1;
        for (int i = left; i <= mid; ++i) {
            while (j <= right && arr[i] > arr[j] + diff) {
                j++;
            }
            result += (j - (mid + 1));
        }

        /* Merge step */
        int i = left, k = left;
        j = mid + 1;
        while (i <= mid && j <= right) {
            if (arr[i] <= arr[j]) {
                temp[k++] = arr[i++];
            } else {
                temp[k++] = arr[j++];
            }
        }
        while (i <= mid) {
            temp[k++] = arr[i++];
        }
        while (j <= right) {
            temp[k++] = arr[j++];
        }
        for (i = left; i <= right; ++i) {
            arr[i] = temp[i];
        }
    }

    merge_sort(0, n - 1);

    free(arr);
    free(temp);
    return result;      
}
