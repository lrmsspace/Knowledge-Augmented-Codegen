// Source: https://leetcode.com/problems/handling-sum-queries-after-update/   |   Difficulty: Hard
//
// Problem Description:
// You are given two 0-indexed arrays nums1 and nums2 and a 2D array queries of queries. There are three types of queries:
//
//
// 	For a query of type 1, queries[i] = [1, l, r]. Flip the values from 0 to 1 and from 1 to 0 in nums1 from index l to index r. Both l and r are 0-indexed.
// 	For a query of type 2, queries[i] = [2, p, 0]. For every index 0 <= i < n, set nums2[i] = nums2[i] + nums1[i] * p.
// 	For a query of type 3, queries[i] = [3, 0, 0]. Find the sum of the elements in nums2.
//
//
// Return an array containing all the answers to the third type queries.
//
// Example:
// Input: nums1 = [1,0,1], nums2 = [0,0,0], queries = [[1,1,1],[2,1,0],[3,0,0]]
// Output: [3]
// Explanation: After the first query nums1 becomes [1,1,1]. After the second query, nums2 becomes [1,1,1], so the answer to the third query is 3. Thus, [3] is returned.
//
// Constraints:
// 1 <= nums1.length,nums2.length <= 105
// 	nums1.length = nums2.length
// 	1 <= queries.length <= 105
// 	queries[i].length = 3
// 	0 <= l <= r <= nums1.length - 1
// 	0 <= p <= 106
// 	0 <= nums1[i] <= 1
// 	0 <= nums2[i] <= 109
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
long long* handleQuery(int* nums1, int nums1Size, int* nums2, int nums2Size, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    if (!returnSize) return NULL;

    /* Precompute sum of nums2 and count of 1s in nums1 */
    long long sum_nums2 = 0;
    int count_ones = 0;
    for (int i = 0; i < nums2Size; ++i) {
        sum_nums2 += nums2[i];
    }
    for (int i = 0; i < nums1Size; ++i) {
        if (nums1[i] == 1) {
            count_ones++;
        }
    }

    /* Prepare result array for type 3 queries */
    long long *results = (long long*)malloc(queriesSize * sizeof(long long));
    if (!results) return NULL;
    int res_index = 0;

    /* Process each query */
    for (int i = 0; i < queriesSize; ++i) {
        int type = queries[i][0];
        if (type == 1) {
            int l = queries[i][1];
            int r = queries[i][2];
            for (int j = l; j <= r; ++j) {
                if (nums1[j] == 1) {
                    nums1[j] = 0;
                    count_ones--;
                } else {
                    nums1[j] = 1;
                    count_ones++;
                }
            }
        } else if (type == 2) {
            int p = queries[i][1];
            sum_nums2 += (long long)count_ones * p;
        } else if (type == 3) {
            results[res_index++] = sum_nums2;
        }
    }

    *returnSize = res_index;
    return results;     
}
