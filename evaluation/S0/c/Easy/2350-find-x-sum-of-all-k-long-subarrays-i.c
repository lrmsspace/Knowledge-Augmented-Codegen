// Source: https://leetcode.com/problems/find-x-sum-of-all-k-long-subarrays-i/   |   Difficulty: Easy
//
// Problem Description:
// You are given an array nums of n integers and two integers k and x.
//
// The x-sum of an array is calculated by the following procedure:
//
//
// 	Count the occurrences of all elements in the array.
// 	Keep only the occurrences of the top x most frequent elements. If two elements have the same number of occurrences, the element with the bigger value is considered more frequent.
// 	Calculate the sum of the resulting array.
//
//
// Note that if an array has less than x distinct elements, its x-sum is the sum of the array.
//
// Return an integer array answer of length n - k + 1 where answer[i] is the x-sum of the subarray nums[i..i + k - 1].
//
// Example:
// Input: nums = [1,1,2,2,3,4,2,3], k = 6, x = 2
//
// Output: [6,10,12]
//
// Explanation:
//
//
// 	For subarray [1, 1, 2, 2, 3, 4], only elements 1 and 2 will be kept in the resulting array. Hence, answer[0] = 1 + 1 + 2 + 2.
// 	For subarray [1, 2, 2, 3, 4, 2], only elements 2 and 4 will be kept in the resulting array. Hence, answer[1] = 2 + 2 + 2 + 4. Note that 4 is kept in the array since it is bigger than 3 and 1 which occur the same number of times.
// 	For subarray [2, 2, 3, 4, 2, 3], only elements 2 and 3 are kept in the resulting array. Hence, answer[2] = 2 + 2 + 2 + 3 + 3.
//
// Constraints:
// 1 <= n == nums.length <= 50
// 	1 <= nums[i] <= 50
// 	1 <= x <= k <= nums.length
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findXSum(int* nums, int numsSize, int k, int x, int* returnSize) {
    int* result = (int*)malloc((numsSize - k + 1) * sizeof(int));
    *returnSize = numsSize - k + 1;

    for (int i = 0; i <= numsSize - k; i++) {
        int freq[51] = {0};

        // Count frequencies in the current subarray
        for (int j = i; j < i + k; j++) {
            freq[nums[j]]++;
        }

        // Create an array of pairs (number, frequency)
        int pairs[51][2];
        int pairCount = 0;
        for (int num = 1; num <= 50; num++) {
            if (freq[num] > 0) {
                pairs[pairCount][0] = num;
                pairs[pairCount][1] = freq[num];
                pairCount++;
            }
        }

        // Sort pairs by frequency (descending), then by number (descending)
        for (int m = 0; m < pairCount - 1; m++) {
            for (int n = m + 1; n < pairCount; n++) {
                if (pairs[m][1] < pairs[n][1] || 
                   (pairs[m][1] == pairs[n][1] && pairs[m][0] < pairs[n][0])) {
                    int tempNum = pairs[m][0];
                    int tempFreq = pairs[m][1];
                    pairs[m][0] = pairs[n][0];
                    pairs[m][1] = pairs[n][1];
                    pairs[n][0] = tempNum;
                    pairs[n][1] = tempFreq;
                }
            }
        }

        // Calculate the x-sum
        int xSum = 0;
        for (int m = 0; m < pairCount && m < x; m++) {
            xSum += pairs[m][0] * pairs[m][1];
        }

        result[i] = xSum;
    }

    return result;      
}
