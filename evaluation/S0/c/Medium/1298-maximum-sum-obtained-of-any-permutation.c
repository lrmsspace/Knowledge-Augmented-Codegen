// Source: https://leetcode.com/problems/maximum-sum-obtained-of-any-permutation/   |   Difficulty: Medium
//
// Problem Description:
// We have an array of integers, nums, and an array of requests where requests[i] = [starti, endi]. The ith request asks for the sum of nums[starti] + nums[starti + 1] + ... + nums[endi - 1] + nums[endi]. Both starti and endi are 0-indexed.
//
// Return the maximum total sum of all requests among all permutations of nums.
//
// Since the answer may be too large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [1,2,3,4,5], requests = [[1,3],[0,1]]
// Output: 19
// Explanation: One permutation of nums is [2,1,3,4,5] with the following result: 
// requests[0] -> nums[1] + nums[2] + nums[3] = 1 + 3 + 4 = 8
// requests[1] -> nums[0] + nums[1] = 2 + 1 = 3
// Total sum: 8 + 3 = 11.
// A permutation with a higher total sum is [3,5,4,2,1] with the following result:
// requests[0] -> nums[1] + nums[2] + nums[3] = 5 + 4 + 2 = 11
// requests[1] -> nums[0] + nums[1] = 3 + 5  = 8
// Total sum: 11 + 8 = 19, which is the best that you can do.
//
// Constraints:
// n == nums.length
// 	1 <= n <= 105
// 	0 <= nums[i] <= 105
// 	1 <= requests.length <= 105
// 	requests[i].length == 2
// 	0 <= starti <= endi < n
//

int maxSumRangeQuery(int* nums, int numsSize, int** requests, int requestsSize, int* requestsColSize) {
    int MOD = 1e9 + 7;
    int* freq = (int*)calloc(numsSize, sizeof(int));
    
    // Calculate frequency of each index in nums based on requests
    for (int i = 0; i < requestsSize; i++) {
        int start = requests[i][0];
        int end = requests[i][1];
        freq[start]++;
        if (end + 1 < numsSize) {
            freq[end + 1]--;
        }
    }
    
    // Prefix sum to get the actual frequency counts
    for (int i = 1; i < numsSize; i++) {
        freq[i] += freq[i - 1];
    }
    
    // Sort nums and freq arrays
    qsort(nums, numsSize, sizeof(int), (int (*)(const void*, const void*))strcmp);
    qsort(freq, numsSize, sizeof(int), (int (*)(const void*, const void*))strcmp);
    
    // Calculate the maximum sum
    long long result = 0;
    for (int i = 0; i < numsSize; i++) {
        result = (result + (long long)nums[i] * freq[i]) % MOD;
    }
    
    free(freq);
    return (int)result;     
}
