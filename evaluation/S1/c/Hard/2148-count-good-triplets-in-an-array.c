// Source: https://leetcode.com/problems/count-good-triplets-in-an-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given two 0-indexed arrays nums1 and nums2 of length n, both of which are permutations of [0, 1, ..., n - 1].
//
// A good triplet is a set of 3 distinct values which are present in increasing order by position both in nums1 and nums2. In other words, if we consider pos1v as the index of the value v in nums1 and pos2v as the index of the value v in nums2, then a good triplet will be a set (x, y, z) where 0 <= x, y, z <= n - 1, such that pos1x < pos1y < pos1z and pos2x < pos2y < pos2z.
//
// Return the total number of good triplets.
//
// Example:
// Input: nums1 = [2,0,1,3], nums2 = [0,1,2,3]
// Output: 1
// Explanation: 
// There are 4 triplets (x,y,z) such that pos1x < pos1y < pos1z. They are (2,0,1), (2,0,3), (2,1,3), and (0,1,3). 
// Out of those triplets, only the triplet (0,1,3) satisfies pos2x < pos2y < pos2z. Hence, there is only 1 good triplet.
//
// Constraints:
// n == nums1.length == nums2.length
// 	3 <= n <= 105
// 	0 <= nums1[i], nums2[i] <= n - 1
// 	nums1 and nums2 are permutations of [0, 1, ..., n - 1].
//
// Helpful references (internal KB):
// - Fenwick Tree (array, bit-fenwick, difference-array)
//   • When to use: Use when an array requires frequent point updates and efficient retrieval of prefix sums or range sums. It offers logarithmic time complexity for both operations.
//   • Idea: A Fenwick Tree, or Binary Indexed Tree (BIT), is a data structure that efficiently supports point updates and prefix sum queries on an array in O(log N) time.
//   • Invariants: Each `bit[i]` stores the sum of a contiguous range of elements from the original array.; The range length represented by `bit[i]` is determined by `i & -i` (the least significant bit).
//   • Tips: Use 1-based indexing for simpler bitwise operations (`i & -i`).; Initialize with an existing array in O(N) time using a linear construction method.
//   • Pitfalls: Directly finding range minimum/maximum is not efficient or generally supported.; Operations must be associative and preferably invertible for general range queries.
// - The Inclusion-Exclusion Principle (array, number, counting, sieve)
//   • When to use: Use when direct counting of elements satisfying specific conditions is difficult due to overlaps, and you need to find the count of elements satisfying at least one, exactly k, or none of several properties.
//   • Idea: The Inclusion-Exclusion Principle counts the size of a union of sets by alternately adding and subtracting the sizes of intersections of increasing numbers of sets. Its complexity is often exponential in the number of properties.
//   • Invariants: At the start of processing subsets of size k, the running total correctly accounts for all intersections of size less than k.; For every element x, its contribution to the total sum is 1 if it satisfies the target condition, and 0 otherwise.
//   • Tips: Clearly define the properties (P1, P2, ..., Pn) for which elements are counted.; Systematically calculate the sizes of all relevant intersections of properties.
//   • Pitfalls: Incorrectly defining the properties or the universe of elements being counted.; Errors in calculating the sizes of specific intersections of properties.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long goodTriplets(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    /* Fenwick Tree (BIT) implementation */
    typedef struct {
        int size;
        int *bit;
    } FenwickTree;

    FenwickTree* fenwickCreate(int size) {
        FenwickTree* tree = (FenwickTree*)malloc(sizeof(FenwickTree));
        tree->size = size;
        tree->bit = (int*)calloc(size + 1, sizeof(int));
        return tree;
    }

    void fenwickUpdate(FenwickTree* tree, int index, int delta) {
        for (++index; index <= tree->size; index += index & -index) {
            tree->bit[index] += delta;
        }
    }

    int fenwickQuery(FenwickTree* tree, int index) {
        int sum = 0;
        for (++index; index > 0; index -= index & -index) {
            sum += tree->bit[index];
        }
        return sum;
    }

    void fenwickFree(FenwickTree* tree) {
        free(tree->bit);
        free(tree);
    }

    int n = nums1Size;
    int* posInNums2 = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        posInNums2[nums2[i]] = i;
    }

    FenwickTree* fenwickLeft = fenwickCreate(n);
    FenwickTree* fenwickRight = fenwickCreate(n);

    for (int i = 0; i < n; i++) {
        fenwickUpdate(fenwickRight, posInNums2[nums1[i]], 1);
    }

    long long result = 0;
    for (int i = 0; i < n; i++) {
        int pos = posInNums2[nums1[i]];
        fenwickUpdate(fenwickRight, pos, -1);

        long long leftCount = fenwickQuery(fenwickLeft, pos - 1);
        long long rightCount = fenwickQuery(fenwickRight, n - 1) - fenwickQuery(fenwickRight, pos);

        result += leftCount * rightCount;

        fenwickUpdate(fenwickLeft, pos, 1);
    }

    fenwickFree(fenwickLeft);
    fenwickFree(fenwickRight);
    free(posInNums2);

    return result;      
}
