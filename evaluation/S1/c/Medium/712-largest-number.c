// Source: https://leetcode.com/problems/largest-number/   |   Difficulty: Medium
//
// Problem Description:
// Given a list of non-negative integers nums, arrange them such that they form the largest number and return it.
//
// Since the result may be very large, so you need to return a string instead of an integer.
//
// Example:
// Input: nums = [10,2]
// Output: "210"
//
// Constraints:
// 1 <= nums.length <= 100
// 	0 <= nums[i] <= 109
//
// Helpful references (internal KB):
// - String Sorts (array, string, recursion)
//   • When to use: Use this algorithm to sort a collection of strings lexicographically, especially when string lengths vary or are large, and the character set is limited.
//   • Idea: This algorithm sorts an array of strings lexicographically by recursively applying a counting sort-like distribution based on characters from most significant to least significant digit. It typically achieves O(N*L + R*L) time complexity, where N is the number of strings, L is the average string length, and R is the radix size.
//   • Invariants: All strings in the current `a[lo...hi]` sub-array share a common prefix of length `d`.; After the distribution pass for character `d`, `aux` contains strings from `a[lo...hi]` stably sorted by their `d`-th character.
//   • Tips: Use an auxiliary array for stable distribution during each pass to maintain relative order.; Implement a cutoff to insertion sort for small sub-arrays to improve performance due to lower overhead.
//   • Pitfalls: Can have high overhead for small N or short strings compared to comparison sorts.; Potentially memory intensive due to the auxiliary array and recursion stack depth proportional to max string length.
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: When tasks need to be processed sequentially on a single resource to optimize a cumulative metric like total completion time or weighted sum of completion times.
//   • Idea: This algorithm finds an optimal sequence for processing jobs on a single machine by applying a greedy strategy, often involving sorting based on specific criteria. It typically achieves an optimal schedule in O(N log N) time complexity.
//   • Invariants: The list of jobs is sorted according to the chosen greedy criterion.; For any prefix of the sorted jobs, the current schedule minimizes the objective function for those jobs.
//   • Tips: Identify the correct sorting key (e.g., processing time, weight/time ratio) for the objective function.; Prove optimality using an exchange argument to justify the greedy choice.
//   • Pitfalls: Applying an incorrect sorting criterion for the specific optimization objective.; Assuming a greedy approach is always optimal without a formal proof.
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

char* largestNumber(int* nums, int numsSize) {
    // Convert integers to strings
    char strNums[numsSize][12]; // max length for 10^9 + null terminator
    for (int i = 0; i < numsSize; i++) {
        sprintf(strNums[i], "%d", nums[i]);
    }

    // Custom comparator for sorting
    int compare(const void* a, const void* b) {
        char ab[24], ba[24];
        sprintf(ab, "%s%s", *(const char**)a, *(const char**)b);
        sprintf(ba, "%s%s", *(const char**)b, *(const char**)a);
        return strcmp(ba, ab); // reverse order for descending
    }

    // Create an array of pointers for qsort
    const char* ptrs[numsSize];
    for (int i = 0; i < numsSize; i++) {
        ptrs[i] = strNums[i];
    }

    // Sort the string representations
    qsort(ptrs, numsSize, sizeof(const char*), compare);

    // Handle the case where the largest number is "0"
    if (strcmp(ptrs[0], "0") == 0) {
        return "0";
    }

    // Calculate total length for the result
    int totalLength = 0;
    for (int i = 0; i < numsSize; i++) {
        totalLength += strlen(ptrs[i]);
    }

    // Allocate result string
    char* result = (char*)malloc(totalLength + 1);
    result[0] = '\0';

    // Concatenate sorted strings into result
    for (int i = 0; i < numsSize; i++) {
        strcat(result, ptrs[i]);
    }

    return result;      
}
