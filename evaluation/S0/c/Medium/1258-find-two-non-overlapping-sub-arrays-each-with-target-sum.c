// Source: https://leetcode.com/problems/find-two-non-overlapping-sub-arrays-each-with-target-sum/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of integers arr and an integer target.
//
// You have to find two non-overlapping sub-arrays of arr each with a sum equal target. There can be multiple answers so you have to find an answer where the sum of the lengths of the two sub-arrays is minimum.
//
// Return the minimum sum of the lengths of the two required sub-arrays, or return -1 if you cannot find such two sub-arrays.
//
// Example:
// Input: arr = [3,2,2,4,3], target = 3
// Output: 2
// Explanation: Only two sub-arrays have sum = 3 ([3] and [3]). The sum of their lengths is 2.
//
// Constraints:
// 1 <= arr.length <= 105
// 	1 <= arr[i] <= 1000
// 	1 <= target <= 108
//

int minSumOfLengths(int* arr, int arrSize, int target) {
    int left = 0, right = 0;
    int sum = 0;
    int min_len = arrSize + 1;
    int result = arrSize + 1;
    int *dp = (int *)malloc((arrSize + 1) * sizeof(int));
    
    for (int i = 0; i <= arrSize; i++) {
        dp[i] = arrSize + 1;
    }
    
    while (right < arrSize) {
        sum += arr[right];
        
        while (sum > target) {
            sum -= arr[left];
            left++;
        }
        
        if (sum == target) {
            int current_len = right - left + 1;
            if (left > 0 && dp[left - 1] != arrSize + 1) {
                result = (result < dp[left - 1] + current_len) ? result : dp[left - 1] + current_len;
            }
            min_len = (min_len < current_len) ? min_len : current_len;
        }
        
        dp[right] = (right > 0) ? ((dp[right - 1] < min_len) ? dp[right - 1] : min_len) : min_len;
        right++;
    }
    
    free(dp);
    
    return (result == arrSize + 1) ? -1 : result;       
}
