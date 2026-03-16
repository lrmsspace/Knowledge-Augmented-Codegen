// Source: https://leetcode.com/problems/zero-array-transformation-iv/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums of length n and a 2D array queries, where queries[i] = [li, ri, vali].
//
// Each queries[i] represents the following action on nums:
//
//
// 	Select a subset of indices in the range [li, ri] from nums.
// 	Decrement the value at each selected index by exactly vali.
//
//
// A Zero Array is an array with all its elements equal to 0.
//
// Return the minimum possible non-negative value of k, such that after processing the first k queries in sequence, nums becomes a Zero Array. If no such k exists, return -1.
//
// Example:
// Input: nums = [2,0,2], queries = [[0,2,1],[0,2,1],[1,1,3]]
//
// Output: 2
//
// Explanation:
//
//
// 	For query 0 (l = 0, r = 2, val = 1):
//
// 	
// 		Decrement the values at indices [0, 2] by 1.
// 		The array will become [1, 0, 1].
// 	
// 	
// 	For query 1 (l = 0, r = 2, val = 1):
// 	
// 		Decrement the values at indices [0, 2] by 1.
// 		The array will become [0, 0, 0], which is a Zero Array. Therefore, the minimum value of k is 2.
//
// Constraints:
// 1 <= nums.length <= 10
// 	0 <= nums[i] <= 1000
// 	1 <= queries.length <= 1000
// 	queries[i] = [li, ri, vali]
// 	0 <= li <= ri < nums.length
// 	1 <= vali <= 10
//

int minZeroArray(int* nums, int numsSize, int** queries, int queriesSize, int* queriesColSize) {
    for (int k = 0; k <= queriesSize; k++) {
        int temp[numsSize];
        memcpy(temp, nums, sizeof(int) * numsSize);

        for (int i = 0; i < k; i++) {
            int l = queries[i][0];
            int r = queries[i][1];
            int val = queries[i][2];

            for (int j = l; j <= r; j++) {
                if (temp[j] >= val) {
                    temp[j] -= val;
                }
            }
        }

        int isZeroArray = 1;
        for (int i = 0; i < numsSize; i++) {
            if (temp[i] != 0) {
                isZeroArray = 0;
                break;
            }
        }

        if (isZeroArray) {
            return k;
        }
    }

    return -1;      
}
