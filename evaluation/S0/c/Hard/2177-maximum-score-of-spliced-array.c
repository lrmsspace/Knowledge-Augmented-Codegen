// Source: https://leetcode.com/problems/maximum-score-of-spliced-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given two 0-indexed integer arrays nums1 and nums2, both of length n.
//
// You can choose two integers left and right where 0 <= left <= right < n and swap the subarray nums1[left...right] with the subarray nums2[left...right].
//
//
// 	For example, if nums1 = [1,2,3,4,5] and nums2 = [11,12,13,14,15] and you choose left = 1 and right = 2, nums1 becomes [1,12,13,4,5] and nums2 becomes [11,2,3,14,15].
//
//
// You may choose to apply the mentioned operation once or not do anything.
//
// The score of the arrays is the maximum of sum(nums1) and sum(nums2), where sum(arr) is the sum of all the elements in the array arr.
//
// Return the maximum possible score.
//
// A subarray is a contiguous sequence of elements within an array. arr[left...right] denotes the subarray that contains the elements of nums between indices left and right (inclusive).
//
// Example:
// Input: nums1 = [60,60,60], nums2 = [10,90,10]
// Output: 210
// Explanation: Choosing left = 1 and right = 1, we have nums1 = [60,90,60] and nums2 = [10,60,10].
// The score is max(sum(nums1), sum(nums2)) = max(210, 80) = 210.
//
// Constraints:
// n == nums1.length == nums2.length
// 	1 <= n <= 105
// 	1 <= nums1[i], nums2[i] <= 104
//

int maximumsSplicedArray(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int total1 = 0, total2 = 0;
    for (int i = 0; i < nums1Size; ++i) {
        total1 += nums1[i];
        total2 += nums2[i];
    }

    int maxGain1 = 0, maxGain2 = 0;
    int currGain1 = 0, currGain2 = 0;
    for (int i = 0; i < nums1Size; ++i) {
        currGain1 += nums2[i] - nums1[i];
        if (currGain1 < 0) currGain1 = 0;
        if (currGain1 > maxGain1) maxGain1 = currGain1;

        currGain2 += nums1[i] - nums2[i];
        if (currGain2 < 0) currGain2 = 0;
        if (currGain2 > maxGain2) maxGain2 = currGain2;
    }

    int result1 = total1 + maxGain1;
    int result2 = total2 + maxGain2;
    return result1 > result2 ? result1 : result2;       
}
