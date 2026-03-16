// Source: https://leetcode.com/problems/number-of-squareful-arrays/   |   Difficulty: Hard
//
// Problem Description:
// An array is squareful if the sum of every pair of adjacent elements is a perfect square.
//
// Given an integer array nums, return the number of permutations of nums that are squareful.
//
// Two permutations perm1 and perm2 are different if there is some index i such that perm1[i] != perm2[i].
//
// Example:
// Input: nums = [1,17,8]
// Output: 2
// Explanation: [1,8,17] and [17,8,1] are the valid permutations.
//
// Constraints:
// 1 <= nums.length <= 12
// 	0 <= nums[i] <= 109
//
// Helpful references (internal KB):
// - Sieve of Eratosthenes (array, sieve, enumeration)
//   • When to use: Use when you need to find all prime numbers up to a certain limit or precompute primality for a range. It is efficient for generating primes within a reasonable upper bound.
//   • Idea: The Sieve of Eratosthenes efficiently finds all prime numbers up to a specified integer by iteratively marking multiples of primes as composite. It achieves a time complexity of O(N log log N).
//   • Invariants: All numbers less than the current prime 'p' have already been processed.; If 'i' is marked as prime, then all its multiples less than 'i*i' have been marked composite by smaller primes.
//   • Tips: Optimize by starting inner loop from p*p, as smaller multiples would have been marked.; Use a boolean array for primality, or an integer array to store smallest prime factor (SPF).
//   • Pitfalls: Incorrectly handling 0 and 1, which are neither prime nor composite.; Off-by-one errors when setting array bounds or loop conditions.
// - Sqrt Decomposition (array, enumeration, difference-array)
//   • When to use: Efficiently calculate sums or properties over various ranges in a static array. Useful for many range queries or when combining range updates with point queries.
//   • Idea: Prefix sums allow O(1) range sum queries after O(N) preprocessing. Difference arrays enable O(1) range updates and O(N) point queries after O(N) reconstruction.
//   • Invariants: The prefix sum array P[i] stores the sum of elements from A[0] to A[i-1].; The difference array D[i] stores A[i] - A[i-1] (for i > 0).
//   • Tips: Precompute prefix sums to answer range sum queries in constant time.; Use a difference array to apply range updates efficiently.
//   • Pitfalls: Off-by-one errors in range boundaries for prefix sums.; Forgetting to initialize the difference array correctly (e.g., diff[0] = arr[0] for 0-indexed).
// - Sqrt Decomposition (array, enumeration, prefix-sum)
//   • When to use: Use when frequent range queries and point/range updates are needed on an array, offering a balanced O(sqrt(N)) time complexity for both operations. It's a good alternative when a segment tree is too complex or overkill.
//   • Idea: Sqrt decomposition divides an array into blocks of size approximately sqrt(N) to optimize range queries and updates. It achieves an O(sqrt(N)) time complexity for both query and update operations.
//   • Invariants: Each block maintains an up-to-date aggregate of its elements.; For any query, fully contained blocks are processed using their precomputed aggregates.
//   • Tips: Choose block size carefully, typically sqrt(N) for optimal balance.; Precompute block aggregates (sum, min, max) for efficient queries.
//   • Pitfalls: Incorrectly handling partial blocks or boundary conditions.; Off-by-one errors in block indices or element indices within blocks.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int numSquarefulPerms(int* nums, int numsSize) {
    // This problem can be solved using backtracking to generate all permutations of the input array and checking if each permutation is squareful. 
    // We can optimize the backtracking by skipping duplicate elements to avoid generating the same permutation multiple times.

    // Helper function to check if a number is a perfect square
    int isPerfectSquare(int num) {
        int root = (int)sqrt(num);
        return root * root == num;
    }

    // Backtracking function to generate permutations
    void backtrack(int* nums, int numsSize, int* used, int* path, int depth, int* count) {
        if (depth == numsSize) {
            (*count)++;
            return;
        }
        for (int i = 0; i < numsSize; i++) {
            if (used[i]) continue; // Skip used elements
            if (i > 0 && nums[i] == nums[i - 1] && !used[i - 1]) continue; // Skip duplicates
            if (depth > 0 && !isPerfectSquare(path[depth - 1] + nums[i])) continue; // Check if adjacent sum is a perfect square

            used[i] = 1; // Mark the element as used
            path[depth] = nums[i]; // Add the element to the current path
            backtrack(nums, numsSize, used, path, depth + 1, count); // Recur with the next depth
            used[i] = 0; // Backtrack: unmark the element
        }
    }

    // Sort the input array to handle duplicates easily
    qsort(nums, numsSize, sizeof(int), compare);

    int count = 0;
    int* used = (int*)calloc(numsSize, sizeof(int)); // Array to track used elements
    int* path = (int*)malloc(numsSize * sizeof(int)); // Array to store the current permutation path

    backtrack(nums, numsSize, used, path, 0, &count); // Start backtracking

    free(used);
    free(path);
    
    return count;       
}
