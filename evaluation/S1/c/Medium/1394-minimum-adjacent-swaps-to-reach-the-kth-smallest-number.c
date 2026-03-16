// Source: https://leetcode.com/problems/minimum-adjacent-swaps-to-reach-the-kth-smallest-number/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string num, representing a large integer, and an integer k.
//
// We call some integer wonderful if it is a permutation of the digits in num and is greater in value than num. There can be many wonderful integers. However, we only care about the smallest-valued ones.
//
//
// 	For example, when num = "5489355142":
//
// 	
// 		The 1st smallest wonderful integer is "5489355214".
// 		The 2nd smallest wonderful integer is "5489355241".
// 		The 3rd smallest wonderful integer is "5489355412".
// 		The 4th smallest wonderful integer is "5489355421".
// 	
// 	
//
//
// Return the minimum number of adjacent digit swaps that needs to be applied to num to reach the kth smallest wonderful integer.
//
// The tests are generated in such a way that kth smallest wonderful integer exists.
//
// Example:
// Input: num = "5489355142", k = 4
// Output: 2
// Explanation: The 4th smallest wonderful number is "5489355421". To get this number:
// - Swap index 7 with index 8: "5489355142" -> "5489355412"
// - Swap index 8 with index 9: "5489355412" -> "5489355421"
//
// Constraints:
// 2 <= num.length <= 1000
// 	1 <= k <= 1000
// 	num only consists of digits.
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Fenwick Tree (array, bit-fenwick, difference-array)
//   • When to use: Use when an array requires frequent point updates and efficient retrieval of prefix sums or range sums. It offers logarithmic time complexity for both operations.
//   • Idea: A Fenwick Tree, or Binary Indexed Tree (BIT), is a data structure that efficiently supports point updates and prefix sum queries on an array in O(log N) time.
//   • Invariants: Each `bit[i]` stores the sum of a contiguous range of elements from the original array.; The range length represented by `bit[i]` is determined by `i & -i` (the least significant bit).
//   • Tips: Use 1-based indexing for simpler bitwise operations (`i & -i`).; Initialize with an existing array in O(N) time using a linear construction method.
//   • Pitfalls: Directly finding range minimum/maximum is not efficient or generally supported.; Operations must be associative and preferably invertible for general range queries.
// - Lyndon factorization (string, greedy, two-pointers)
//   • When to use: Use this algorithm to decompose a string into a unique sequence of Lyndon words, which are lexicographically smallest among their cyclic shifts. It is also applicable for finding the smallest cyclic shift of a string.
//   • Idea: The Duval algorithm greedily factorizes a string into a sequence of Lyndon words by maintaining three pointers to manage processed, pre-simple, and untouched parts. It achieves this in O(N) time complexity.
//   • Invariants: The prefix s[0...i-1] always contains a valid Lyndon factorization.; The substring s[i...j-1] is always a pre-simple string.
//   • Tips: Thoroughly understand the definitions of 'simple string' and 'pre-simple string' to correctly apply the comparison logic.; The three pointers (i, j, k) are crucial; 'i' marks the start of the current pre-simple string, 'j' the start of the untouched part, and 'k' for comparison within the pre-simple string.
//   • Pitfalls: Incorrectly resetting the 'k' pointer when s[j] > s[k], which should point back to the beginning of the simple word within s2.; Misinterpreting the length of the simple string (j - k) when a factorization step occurs.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int getMinSwaps(char* num, int k) {
    // Generate the k-th smallest wonderful number
    char target[1001];
    int len = 0;
    while (num[len]) {
        target[len] = num[len];
        len++;
    }
    target[len] = '\0';

    for (int step = 0; step < k; step++) {
        // Find the next permutation
        int i = len - 2;
        while (i >= 0 && target[i] >= target[i + 1]) {
            i--;
        }
        if (i >= 0) {
            int j = len - 1;
            while (target[j] <= target[i]) {
                j--;
            }
            char temp = target[i];
            target[i] = target[j];
            target[j] = temp;
        }
        // Reverse the suffix
        int left = i + 1, right = len - 1;
        while (left < right) {
            char temp = target[left];
            target[left] = target[right];
            target[right] = temp;
            left++;
            right--;
        }
    }

    // Calculate minimum adjacent swaps to transform num to target
    int swaps = 0;
    char numArr[1001];
    for (int i = 0; i < len; i++) {
        numArr[i] = num[i];
    }

    for (int i = 0; i < len; i++) {
        if (numArr[i] != target[i]) {
            int j = i + 1;
            while (numArr[j] != target[i]) {
                j++;
            }
            while (j > i) {
                char temp = numArr[j];
                numArr[j] = numArr[j - 1];
                numArr[j - 1] = temp;
                swaps++;
                j--;
            }
        }
    }

    return swaps;       
}
