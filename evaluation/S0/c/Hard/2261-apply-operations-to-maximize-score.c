// Source: https://leetcode.com/problems/apply-operations-to-maximize-score/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums of n positive integers and an integer k.
//
// Initially, you start with a score of 1. You have to maximize your score by applying the following operation at most k times:
//
//
// 	Choose any non-empty subarray nums[l, ..., r] that you haven't chosen previously.
// 	Choose an element x of nums[l, ..., r] with the highest prime score. If multiple such elements exist, choose the one with the smallest index.
// 	Multiply your score by x.
//
//
// Here, nums[l, ..., r] denotes the subarray of nums starting at index l and ending at the index r, both ends being inclusive.
//
// The prime score of an integer x is equal to the number of distinct prime factors of x. For example, the prime score of 300 is 3 since 300 = 2 * 2 * 3 * 5 * 5.
//
// Return the maximum possible score after applying at most k operations.
//
// Since the answer may be large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [8,3,9,3,8], k = 2
// Output: 81
// Explanation: To get a score of 81, we can apply the following operations:
// - Choose subarray nums[2, ..., 2]. nums[2] is the only element in this subarray. Hence, we multiply the score by nums[2]. The score becomes 1 * 9 = 9.
// - Choose subarray nums[2, ..., 3]. Both nums[2] and nums[3] have a prime score of 1, but nums[2] has the smaller index. Hence, we multiply the score by nums[2]. The score becomes 9 * 9 = 81.
// It can be proven that 81 is the highest score one can obtain.
//
// Constraints:
// 1 <= nums.length == n <= 105
// 	1 <= nums[i] <= 105
// 	1 <= k <= min(n * (n + 1) / 2, 109)
//

int maximumScore(int* nums, int numsSize, int k) {
    // Precompute the number of distinct prime factors for each number up to 10^5
    int maxNum = 100000;
    int *primeFactorCount = (int*)calloc(maxNum + 1, sizeof(int));
    for (int i = 2; i <= maxNum; ++i) {
        if (primeFactorCount[i] == 0) { // i is prime
            for (int j = i; j <= maxNum; j += i) {
                primeFactorCount[j]++;
            }
        }
    }

    // Create an array of indices sorted by the prime factor count and then by value
    int *indices = (int*)malloc(numsSize * sizeof(int));
    for (int i = 0; i < numsSize; ++i) {
        indices[i] = i;
    }
    qsort(indices, numsSize, sizeof(int), 
          (int (*)(const void*, const void*))[](const int *a, const int *b) {
              int countA = primeFactorCount[nums[*a]];
              int countB = primeFactorCount[nums[*b]];
              if (countA != countB) return countB - countA; // Descending order by prime factor count
              return nums[*b] - nums[*a]; // Descending order by value
          });

    // Use a union-find structure to manage segments
    int *parent = (int*)malloc(numsSize * sizeof(int));
    int *size = (int*)malloc(numsSize * sizeof(int));
    for (int i = 0; i < numsSize; ++i) {
        parent[i] = i;
        size[i] = 1;
    }

    // Find function for union-find
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    // Union function for union-find
    void unionSets(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) {
            if (size[a] < size[b]) {
                parent[a] = b;
                size[b] += size[a];
            } else {
                parent[b] = a;
                size[a] += size[b];
            }
        }
    }

    long long MOD = 1000000007;
    long long result = 1;
    for (int i = 0; i < numsSize && k > 0; ++i) {
        int idx = indices[i];
        int val = nums[idx];

        // Count how many segments can be formed with this index
        long long leftSize = (idx > 0 && find(idx - 1) != find(idx)) ? size[find(idx - 1)] : 0;
        long long rightSize = (idx < numsSize - 1 && find(idx + 1) != find(idx)) ? size[find(idx + 1)] : 0;
        long long totalSegments = (leftSize + 1) * (rightSize + 1);

        // Determine how many times we can use this value
        long long useCount = (k < totalSegments) ? k : totalSegments;
        result = (result * modPow(val, useCount, MOD)) % MOD;
        k -= useCount;

        // Union with left and right segments
        if (idx > 0 && find(idx - 1) != find(idx)) {
            unionSets(idx, idx - 1);
        }
        if (idx < numsSize - 1 && find(idx + 1) != find(idx)) {
            unionSets(idx, idx + 1);
        }
    }
    free(primeFactorCount);
    free(indices);
    free(parent);
    free(size);
    return (int)result;  
}
