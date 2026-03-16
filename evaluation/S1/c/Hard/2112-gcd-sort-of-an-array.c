// Source: https://leetcode.com/problems/gcd-sort-of-an-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums, and you can perform the following operation any number of times on nums:
//
//
// 	Swap the positions of two elements nums[i] and nums[j] if gcd(nums[i], nums[j]) > 1 where gcd(nums[i], nums[j]) is the greatest common divisor of nums[i] and nums[j].
//
//
// Return true if it is possible to sort nums in non-decreasing order using the above swap method, or false otherwise.
//
// Example:
// Input: nums = [7,21,3]
// Output: true
// Explanation: We can sort [7,21,3] by performing the following operations:
// - Swap 7 and 21 because gcd(7,21) = 7. nums = [21,7,3]
// - Swap 21 and 3 because gcd(21,3) = 3. nums = [3,7,21]
//
// Constraints:
// 1 <= nums.length <= 3 * 104
// 	2 <= nums[i] <= 105
//
// Helpful references (internal KB):
// - Linear Sieve (array, sieve)
//   • When to use: Use when you need to find the smallest prime factor or full prime factorization for all numbers up to a given limit N in linear time. It's particularly useful for tasks requiring precomputed factorizations.
//   • Idea: The Linear Sieve computes the smallest prime factor for every number up to N, ensuring each composite number is marked exactly once by its smallest prime factor. It achieves this in O(N) time complexity.
//   • Invariants: Every number `i` from 2 to N has its `lp[i]` correctly set to its smallest prime factor.; The `primes` array contains all prime numbers less than or equal to the current iteration `i`.
//   • Tips: Stores the smallest prime factor (lp) for each number.; Efficiently generates all prime numbers up to N.
//   • Pitfalls: Higher memory usage compared to the classic Sieve of Eratosthenes due to storing lp array.; Can be slower in practice than optimized Sieve of Eratosthenes for merely generating primes.
// - Disjoint Set Union (ds, tree, array, union-find)
//   • When to use: Use when you need to efficiently manage a collection of disjoint sets, supporting operations to merge sets and determine if two elements belong to the same set.
//   • Idea: Disjoint Set Union (DSU) is a data structure that maintains a collection of disjoint sets and supports two primary operations: union (merging two sets) and find (determining the representative of an element's set). With path compression and union by rank/size, operations achieve nearly O(1) amortized time complexity.
//   • Invariants: For any element `v`, `parent[v]` is either `v` itself (if `v` is a root) or an ancestor of `v`.; All elements belonging to the same set share a common root representative.
//   • Tips: Apply path compression during `find_set` to optimize future queries.; Utilize union by rank or size to maintain balanced trees.
//   • Pitfalls: Omitting path compression or union by rank/size results in poor performance.; Failing to correctly identify the root of a set in `find_set`.
// - Primitive Root (number, mod-exp, sieve, enumeration)
//   • When to use: Use when needing to find a generator for the multiplicative group of integers modulo n, or to check if a number is a primitive root. This is often required in number theory problems involving modular arithmetic and cyclic groups.
//   • Idea: This algorithm finds a primitive root modulo n by checking candidate numbers and verifying their order using Euler's totient function and its prime factors. The optimized approach significantly reduces checks from O(phi(n)) to O(k * log(n)) for each candidate, where k is the number of distinct prime factors of phi(n).
//   • Invariants: The current candidate g is coprime to n.; The order of g modulo n is being checked against divisors of phi(n).
//   • Tips: First, determine if a primitive root exists for the given n.; Calculate Euler's totient function phi(n) for the modulus n.
//   • Pitfalls: Forgetting to check the existence condition for primitive roots.; Incorrectly calculating Euler's totient function phi(n).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool gcdSort(int* nums, int numsSize) {
    /* Disjoint Set Union (Union-Find) implementation */
    typedef struct DSU {
        int *parent;
        int *rank;
        int size;
    } DSU;

    DSU* dsuCreate(int size) {
        DSU *dsu = (DSU*)malloc(sizeof(DSU));
        dsu->parent = (int*)malloc(size * sizeof(int));
        dsu->rank = (int*)calloc(size, sizeof(int));
        dsu->size = size;
        for (int i = 0; i < size; ++i) {
            dsu->parent[i] = i;
        }
        return dsu;
    }

    int dsuFind(DSU *dsu, int v) {
        if (dsu->parent[v] != v) {
            dsu->parent[v] = dsuFind(dsu, dsu->parent[v]);
        }
        return dsu->parent[v];
    }

    void dsuUnion(DSU *dsu, int a, int b) {
        a = dsuFind(dsu, a);
        b = dsuFind(dsu, b);
        if (a != b) {
            if (dsu->rank[a] < dsu->rank[b]) {
                dsu->parent[a] = b;
            } else if (dsu->rank[a] > dsu->rank[b]) {
                dsu->parent[b] = a;
            } else {
                dsu->parent[b] = a;
                dsu->rank[a]++;
            }
        }
    }

    void dsuFree(DSU *dsu) {
        free(dsu->parent);
        free(dsu->rank);
        free(dsu);
    }

    /* Linear Sieve to get smallest prime factors up to maxNum */
    int maxNum = 0;
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] > maxNum) maxNum = nums[i];
    }

    int *lp = (int*)calloc(maxNum + 1, sizeof(int));
    int *primes = (int*)malloc((maxNum / 2) * sizeof(int)); // upper bound on number of primes
    int primesCount = 0;

    for (int i = 2; i <= maxNum; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            primes[primesCount++] = i;
        }
        for (int j = 0; j < primesCount && primes[j] <= lp[i] && i * primes[j] <= maxNum; ++j) {
            lp[i * primes[j]] = primes[j];
        }
    }
    free(primes);
    /* Create DSU for numbers up to maxNum */
    DSU *dsu = dsuCreate(maxNum + 1);
    /* Union numbers based on their prime factors */
    for (int i = 0; i < numsSize; ++i) {
        int num = nums[i];
        int firstPrime = lp[num];
        while (num > 1) {
            int primeFactor = lp[num];
            dsuUnion(dsu, firstPrime, primeFactor);
            num /= primeFactor;
        }
    }
    /* Check if sorting is possible */
    int *sortedNums = (int*)malloc(numsSize * sizeof(int));
    memcpy(sortedNums, nums, numsSize * sizeof(int));
    qsort(sortedNums, numsSize, sizeof(int), (int (*)(const void*, const void*))strcmp);
    bool canSort = true;
    for (int i = 0; i < numsSize; ++i) {
        if (dsuFind(dsu, lp[nums[i]]) != dsuFind(dsu, lp[sortedNums[i]])) {
            canSort = false;
            break;
        }
    }
    /* Cleanup */
    dsuFree(dsu);
    free(lp);
    free(sortedNums);
    return canSort;
}
