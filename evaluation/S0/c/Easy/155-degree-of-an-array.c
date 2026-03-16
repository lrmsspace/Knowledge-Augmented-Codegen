// Source: https://leetcode.com/problems/degree-of-an-array/   |   Difficulty: Easy
//
// Problem Description:
// Given a non-empty array of non-negative integers nums, the degree of this array is defined as the maximum frequency of any one of its elements.
//
// Your task is to find the smallest possible length of a (contiguous) subarray of nums, that has the same degree as nums.
//
// Example:
// Input: nums = [1,2,2,3,1]
// Output: 2
// Explanation: 
// The input array has a degree of 2 because both elements 1 and 2 appear twice.
// Of the subarrays that have the same degree:
// [1, 2, 2, 3, 1], [1, 2, 2, 3], [2, 2, 3, 1], [1, 2, 2], [2, 2, 3], [2, 2]
// The shortest length is 2. So return 2.
//
// Constraints:
// nums.length will be between 1 and 50,000.
// 	nums[i] will be an integer between 0 and 49,999.
//

int findShortestSubArray(int* nums, int numsSize) {
    int count[50000] = {0};
    int firstIndex[50000];
    int lastIndex[50000];
    int degree = 0;
    int minLength = numsSize;

    for (int i = 0; i < numsSize; i++) {
        int num = nums[i];
        count[num]++;
        if (count[num] == 1) {
            firstIndex[num] = i;
        }
        lastIndex[num] = i;

        if (count[num] > degree) {
            degree = count[num];
            minLength = lastIndex[num] - firstIndex[num] + 1;
        } else if (count[num] == degree) {
            int currentLength = lastIndex[num] - firstIndex[num] + 1;
            if (currentLength < minLength) {
                minLength = currentLength;
            }
        }
    }

    return minLength;       
}
