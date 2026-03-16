// Source: https://leetcode.com/problems/put-marbles-in-bags/   |   Difficulty: Hard
//
// Problem Description:
// You have k bags. You are given a 0-indexed integer array weights where weights[i] is the weight of the ith marble. You are also given the integer k.
//
// Divide the marbles into the k bags according to the following rules:
//
//
// 	No bag is empty.
// 	If the ith marble and jth marble are in a bag, then all marbles with an index between the ith and jth indices should also be in that same bag.
// 	If a bag consists of all the marbles with an index from i to j inclusively, then the cost of the bag is weights[i] + weights[j].
//
//
// The score after distributing the marbles is the sum of the costs of all the k bags.
//
// Return the difference between the maximum and minimum scores among marble distributions.
//
// Example:
// Input: weights = [1,3,5,1], k = 2
// Output: 4
// Explanation: 
// The distribution [1],[3,5,1] results in the minimal score of (1+1) + (3+1) = 6. 
// The distribution [1,3],[5,1], results in the maximal score of (1+3) + (5+1) = 10. 
// Thus, we return their difference 10 - 6 = 4.
//
// Constraints:
// 1 <= k <= weights.length <= 105
// 	1 <= weights[i] <= 109
//

long long putMarbles(int* weights, int weightsSize, int k) {
    if (k <= 1 || k >= weightsSize) return 0;

    int n = weightsSize - 1;
    long long *sums = (long long*)malloc(n * sizeof(long long));
    if (!sums) return 0;

    for (int i = 0; i < n; ++i) {
        sums[i] = (long long)(weights[i] + weights[i + 1]);
    }

    qsort(sums, n, sizeof(long long), (__compar_fn_t) (int (*)(const void*, const void*)) [](const long long *a, const long long *b) {
        if (*a < *b) return -1;
        else if (*a > *b) return 1;
        else return 0;
    });

    long long minScore = 0, maxScore = 0;
    for (int i = 0; i < k - 1; ++i) {
        minScore += sums[i];
        maxScore += sums[n - 1 - i];
    }

    free(sums);
    return maxScore - minScore;     
}
