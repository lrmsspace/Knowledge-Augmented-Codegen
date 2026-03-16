// Source: https://leetcode.com/problems/most-beautiful-item-for-each-query/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer array items where items[i] = [pricei, beautyi] denotes the price and beauty of an item respectively.
//
// You are also given a 0-indexed integer array queries. For each queries[j], you want to determine the maximum beauty of an item whose price is less than or equal to queries[j]. If no such item exists, then the answer to this query is 0.
//
// Return an array answer of the same length as queries where answer[j] is the answer to the jth query.
//
// Example:
// Input: items = [[1,2],[3,2],[2,4],[5,6],[3,5]], queries = [1,2,3,4,5,6]
// Output: [2,4,5,5,6,6]
// Explanation:
// - For queries[0]=1, [1,2] is the only item which has price <= 1. Hence, the answer for this query is 2.
// - For queries[1]=2, the items which can be considered are [1,2] and [2,4]. 
//   The maximum beauty among them is 4.
// - For queries[2]=3 and queries[3]=4, the items which can be considered are [1,2], [3,2], [2,4], and [3,5].
//   The maximum beauty among them is 5.
// - For queries[4]=5 and queries[5]=6, all items can be considered.
//   Hence, the answer for them is the maximum beauty of all items, i.e., 6.
//
// Constraints:
// 1 <= items.length, queries.length <= 105
// 	items[i].length == 2
// 	1 <= pricei, beautyi, queries[j] <= 109
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maximumBeauty(int** items, int itemsSize, int* itemsColSize, int* queries, int queriesSize, int* returnSize) {
    // Sort items by price
    int cmp(const void* a, const void* b) {
        return ((int*)a)[0] - ((int*)b)[0];
    }
    qsort(items, itemsSize, sizeof(int*), cmp);

    // Preprocess to get max beauty up to each price
    int* maxBeauty = (int*)malloc(itemsSize * sizeof(int));
    maxBeauty[0] = items[0][1];
    for (int i = 1; i < itemsSize; i++) {
        maxBeauty[i] = (items[i][1] > maxBeauty[i - 1]) ? items[i][1] : maxBeauty[i - 1];
    }

    // Prepare result array
    int* result = (int*)malloc(queriesSize * sizeof(int));
    *returnSize = queriesSize;

    // For each query, perform binary search on items
    for (int i = 0; i < queriesSize; i++) {
        int left = 0, right = itemsSize - 1;
        int ans = 0;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (items[mid][0] <= queries[i]) {
                ans = maxBeauty[mid];
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        result[i] = ans;
    }

    free(maxBeauty);
    return result;      
}
