// Source: https://leetcode.com/problems/make-array-empty/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums containing distinct numbers, and you can perform the following operations until the array is empty:
//
//
// 	If the first element has the smallest value, remove it
// 	Otherwise, put the first element at the end of the array.
//
//
// Return an integer denoting the number of operations it takes to make nums empty.
//
// Example:
// Input: nums = [3,4,-1]
// Output: 5
//
//
//
// 	
// 		
// 			Operation
// 			Array
// 		
// 	
// 	
// 		
// 			1
// 			[4, -1, 3]
// 		
// 		
// 			2
// 			[-1, 3, 4]
// 		
// 		
// 			3
// 			[3, 4]
// 		
// 		
// 			4
// 			[4]
// 		
// 		
// 			5
// 			[]
//
// Constraints:
// 1 <= nums.length <= 105
// 	-109 <= nums[i] <= 109
// 	All values in nums are distinct.
//
// Helpful references (internal KB):
// - Fenwick Tree (array, bit-fenwick, difference-array)
//   • When to use: Use when an array requires frequent point updates and efficient retrieval of prefix sums or range sums. It offers logarithmic time complexity for both operations.
//   • Idea: A Fenwick Tree, or Binary Indexed Tree (BIT), is a data structure that efficiently supports point updates and prefix sum queries on an array in O(log N) time.
//   • Invariants: Each `bit[i]` stores the sum of a contiguous range of elements from the original array.; The range length represented by `bit[i]` is determined by `i & -i` (the least significant bit).
//   • Tips: Use 1-based indexing for simpler bitwise operations (`i & -i`).; Initialize with an existing array in O(N) time using a linear construction method.
//   • Pitfalls: Directly finding range minimum/maximum is not efficient or generally supported.; Operations must be associative and preferably invertible for general range queries.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: When tasks need to be processed sequentially on a single resource to optimize a cumulative metric like total completion time or weighted sum of completion times.
//   • Idea: This algorithm finds an optimal sequence for processing jobs on a single machine by applying a greedy strategy, often involving sorting based on specific criteria. It typically achieves an optimal schedule in O(N log N) time complexity.
//   • Invariants: The list of jobs is sorted according to the chosen greedy criterion.; For any prefix of the sorted jobs, the current schedule minimizes the objective function for those jobs.
//   • Tips: Identify the correct sorting key (e.g., processing time, weight/time ratio) for the objective function.; Prove optimality using an exchange argument to justify the greedy choice.
//   • Pitfalls: Applying an incorrect sorting criterion for the specific optimization objective.; Assuming a greedy approach is always optimal without a formal proof.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long countOperationsToEmptyArray(int* nums, int numsSize) {
    // Fenwick Tree (Binary Indexed Tree) implementation
    typedef struct {
        int size;
        int* tree;
    } FenwickTree;

    FenwickTree* fenwickCreate(int size) {
        FenwickTree* ft = (FenwickTree*)malloc(sizeof(FenwickTree));
        ft->size = size;
        ft->tree = (int*)calloc(size + 1, sizeof(int));
        return ft;
    }

    void fenwickUpdate(FenwickTree* ft, int index, int delta) {
        for (++index; index <= ft->size; index += index & -index) {
            ft->tree[index] += delta;
        }
    }

    int fenwickQuery(FenwickTree* ft, int index) {
        int sum = 0;
        for (++index; index > 0; index -= index & -index) {
            sum += ft->tree[index];
        }
        return sum;
    }

    void fenwickFree(FenwickTree* ft) {
        free(ft->tree);
        free(ft);
    }

    // Main logic
    int* sorted = (int*)malloc(numsSize * sizeof(int));
    memcpy(sorted, nums, numsSize * sizeof(int));
    qsort(sorted, numsSize, sizeof(int), cmpInt);

    // Map original values to their ranks
    int* rank = (int*)malloc(numsSize * sizeof(int));
    for (int i = 0; i < numsSize; ++i) {
        rank[i] = (int)(bsearch(&nums[i], sorted, numsSize, sizeof(int), cmpInt) - (void*)sorted);
    }

    FenwickTree* ft = fenwickCreate(numsSize);
    long long operations = 0;

    for (int i = 0; i < numsSize; ++i) {
        int r = rank[i];
        int lessCount = fenwickQuery(ft, r - 1);
        operations += (i - lessCount);
        fenwickUpdate(ft, r, 1);
    }

    fenwickFree(ft);
    free(sorted);
    free(rank);

    return operations + numsSize;       
}
