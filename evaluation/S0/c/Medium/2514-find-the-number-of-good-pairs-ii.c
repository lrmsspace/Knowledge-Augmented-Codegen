// Source: https://leetcode.com/problems/find-the-number-of-good-pairs-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given 2 integer arrays nums1 and nums2 of lengths n and m respectively. You are also given a positive integer k.
//
// A pair (i, j) is called good if nums1[i] is divisible by nums2[j] * k (0 <= i <= n - 1, 0 <= j <= m - 1).
//
// Return the total number of good pairs.
//
// Example:
// Input: nums1 = [1,3,4], nums2 = [1,3,4], k = 1
//
// Output: 5
//
// Explanation:
// The 5 good pairs are (0, 0), (1, 0), (1, 1), (2, 0), and (2, 2).
//
// Constraints:
// 1 <= n, m <= 105
// 	1 <= nums1[i], nums2[j] <= 106
// 	1 <= k <= 103
//

long long numberOfPairs(int* nums1, int nums1Size, int* nums2, int nums2Size, int k) {
    long long result = 0;
    int maxNum = 1000000;
    int freq[maxNum + 1];
    for (int i = 0; i <= maxNum; i++) {
        freq[i] = 0;
    }

    for (int i = 0; i < nums2Size; i++) {
        freq[nums2[i]]++;
    }

    for (int i = 0; i < nums1Size; i++) {
        int num1 = nums1[i];
        for (int j = k; j <= maxNum; j += k) {
            if (num1 < j) {
                break;
            }
            if (num1 % j == 0) {
                int div = num1 / j;
                if (div <= maxNum) {
                    result += freq[div];
                }
            }
        }
    }

    return result;      
}
