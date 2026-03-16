// Source: https://leetcode.com/problems/maximum-elegance-of-a-k-length-subsequence/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed 2D integer array items of length n and an integer k.
//
// items[i] = [profiti, categoryi], where profiti and categoryi denote the profit and category of the ith item respectively.
//
// Let's define the elegance of a subsequence of items as total_profit + distinct_categories2, where total_profit is the sum of all profits in the subsequence, and distinct_categories is the number of distinct categories from all the categories in the selected subsequence.
//
// Your task is to find the maximum elegance from all subsequences of size k in items.
//
// Return an integer denoting the maximum elegance of a subsequence of items with size exactly k.
//
// Note: A subsequence of an array is a new array generated from the original array by deleting some elements (possibly none) without changing the remaining elements' relative order.
//
// Example:
// Input: items = [[3,2],[5,1],[10,1]], k = 2
// Output: 17
// Explanation: In this example, we have to select a subsequence of size 2.
// We can select items[0] = [3,2] and items[2] = [10,1].
// The total profit in this subsequence is 3 + 10 = 13, and the subsequence contains 2 distinct categories [2,1].
// Hence, the elegance is 13 + 22 = 17, and we can show that it is the maximum achievable elegance.
//
// Constraints:
// 1 <= items.length == n <= 105
// 	items[i].length == 2
// 	items[i][0] == profiti
// 	items[i][1] == categoryi
// 	1 <= profiti <= 109
// 	1 <= categoryi <= n 
// 	1 <= k <= n
//

long long findMaximumElegance(int** items, int itemsSize, int* itemsColSize, int k) {
    // Sort items by profit in descending order
    qsort(items, itemsSize, sizeof(int*), [](const void *a, const void *b) {
        int *itemA = *(int**)a;
        int *itemB = *(int**)b;
        return itemB[0] - itemA[0];
    });

    long long totalProfit = 0;
    int distinctCategories = 0;
    int *categoryCount = (int*)calloc(itemsSize + 1, sizeof(int));
    int duplicatesCount = 0;

    // Select the top k items
    for (int i = 0; i < k; ++i) {
        totalProfit += items[i][0];
        if (categoryCount[items[i][1]] == 0) {
            distinctCategories++;
        } else {
            duplicatesCount++;
        }
        categoryCount[items[i][1]]++;
    }

    long long maxElegance = totalProfit + (long long)distinctCategories * distinctCategories;

    // Try to replace duplicates with higher category items
    for (int i = k; i < itemsSize && duplicatesCount > 0; ++i) {
        if (categoryCount[items[i][1]] == 0) {
            totalProfit += items[i][0];
            distinctCategories++;
            duplicatesCount--;

            long long currentElegance = totalProfit + (long long)distinctCategories * distinctCategories;
            if (currentElegance > maxElegance) {
                maxElegance = currentElegance;
            }
        }
    }

    free(categoryCount);
    return maxElegance;     
}
