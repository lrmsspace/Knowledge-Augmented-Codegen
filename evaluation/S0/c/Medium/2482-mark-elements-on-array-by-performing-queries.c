// Source: https://leetcode.com/problems/mark-elements-on-array-by-performing-queries/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array nums of size n consisting of positive integers.
//
// You are also given a 2D array queries of size m where queries[i] = [indexi, ki].
//
// Initially all elements of the array are unmarked.
//
// You need to apply m queries on the array in order, where on the ith query you do the following:
//
//
// 	Mark the element at index indexi if it is not already marked.
// 	Then mark ki unmarked elements in the array with the smallest values. If multiple such elements exist, mark the ones with the smallest indices. And if less than ki unmarked elements exist, then mark all of them.
//
//
// Return an array answer of size m where answer[i] is the sum of unmarked elements in the array after the ith query.
//
// Example:
// Input: nums = [1,2,2,1,2,3,1], queries = [[1,2],[3,3],[4,2]]
//
// Output: [8,3,0]
//
// Explanation:
//
// We do the following queries on the array:
//
//
// 	Mark the element at index 1, and 2 of the smallest unmarked elements with the smallest indices if they exist, the marked elements now are nums = [1,2,2,1,2,3,1]. The sum of unmarked elements is 2 + 2 + 3 + 1 = 8.
// 	Mark the element at index 3, since it is already marked we skip it. Then we mark 3 of the smallest unmarked elements with the smallest indices, the marked elements now are nums = [1,2,2,1,2,3,1]. The sum of unmarked elements is 3.
// 	Mark the element at index 4, since it is already marked we skip it. Then we mark 2 of the smallest unmarked elements with the smallest indices if they exist, the marked elements now are nums = [1,2,2,1,2,3,1]. The sum of unmarked elements is 0.
//
// Constraints:
// n == nums.length
// 	m == queries.length
// 	1 <= m <= n <= 105
// 	1 <= nums[i] <= 105
// 	queries[i].length == 2
// 	0 <= indexi, ki <= n - 1
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
long long* unmarkedSumArray(int* nums, int numsSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    // Calculate the total sum of the array
    long long totalSum = 0;
    for (int i = 0; i < numsSize; i++) {
        totalSum += nums[i];
    }

    // Create an array of indices and sort them based on the values in nums
    int* indices = (int*)malloc(numsSize * sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        indices[i] = i;
    }
    qsort(indices, numsSize, sizeof(int), 
          (int (*)(const void*, const void*))[](const int* a, const int* b) {
              return nums[*a] - nums[*b];
          });

    // Create a BIT (Fenwick Tree) to track marked elements
    int* BIT = (int*)calloc(numsSize + 1, sizeof(int));
    auto updateBIT = [&](int index, int value) {
        for (index++; index <= numsSize; index += index & -index) {
            BIT[index] += value;
        }
    };
    auto queryBIT = [&](int index) {
        int sum = 0;
        for (index++; index > 0; index -= index & -index) {
            sum += BIT[index];
        }
        return sum;
    };

    long long* result = (long long*)malloc(queriesSize * sizeof(long long));
    int markedCount = 0;
    int currentIndex = 0;

    for (int i = 0; i < queriesSize; i++) {
        int indexToMark = queries[i][0];
        int k = queries[i][1];

        // Mark the specified index if not already marked
        if (queryBIT(indexToMark) - queryBIT(indexToMark - 1) == 0) {
            updateBIT(indexToMark, 1);
            totalSum -= nums[indexToMark];
            markedCount++;
        }

        // Mark k smallest unmarked elements
        while (k > 0 && currentIndex < numsSize) {
            int idx = indices[currentIndex];
            if (queryBIT(idx) - queryBIT(idx - 1) == 0) {
                updateBIT(idx, 1);
                totalSum -= nums[idx];
                markedCount++;
                k--;
            }
            currentIndex++;
        }

        result[i] = totalSum;
    }  
    *returnSize = queriesSize;
    free(indices);
    
    free(BIT);
    return result;
}
