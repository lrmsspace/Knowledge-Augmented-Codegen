// Source: https://leetcode.com/problems/fair-distribution-of-cookies/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array cookies, where cookies[i] denotes the number of cookies in the ith bag. You are also given an integer k that denotes the number of children to distribute all the bags of cookies to. All the cookies in the same bag must go to the same child and cannot be split up.
//
// The unfairness of a distribution is defined as the maximum total cookies obtained by a single child in the distribution.
//
// Return the minimum unfairness of all distributions.
//
// Example:
// Input: cookies = [8,15,10,20,8], k = 2
// Output: 31
// Explanation: One optimal distribution is [8,15,8] and [10,20]
// - The 1st child receives [8,15,8] which has a total of 8 + 15 + 8 = 31 cookies.
// - The 2nd child receives [10,20] which has a total of 10 + 20 = 30 cookies.
// The unfairness of the distribution is max(31,30) = 31.
// It can be shown that there is no distribution with an unfairness less than 31.
//
// Constraints:
// 2 <= cookies.length <= 8
// 	1 <= cookies[i] <= 105
// 	2 <= k <= cookies.length
//
// Helpful references (internal KB):
// - Generating all K-combinations (bitset, recursion, enumeration)
//   • When to use: Use when an exhaustive list of all subsets of a specific size K from a set of N items is required. It's suitable for problems needing to explore every possible configuration of K elements.
//   • Idea: This algorithm systematically generates all unique subsets of size K from a set of N distinct elements, commonly employing recursion or bit manipulation. The typical time complexity is O(N choose K * K) for construction or O(N choose K) if just iterating.
//   • Invariants: The current partial combination always contains unique elements.; The number of elements chosen so far does not exceed K.
//   • Tips: Employ backtracking or recursion for a straightforward implementation.; Utilize bitmasks for efficient representation and generation, especially for smaller N.
//   • Pitfalls: Accidentally generating duplicate combinations if elements are not handled uniquely.; Failing to correctly define base cases or termination conditions for recursive calls.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Generating all K-combinations (bitset, enumeration)
//   • When to use: When all subsets of a fixed size K need to be generated, either in lexicographical order or such that successive combinations differ by exactly one element.
//   • Idea: This algorithm enumerates all K-combinations from a set, either in lexicographical order or using a Gray code approach where adjacent combinations differ by a single element. It typically runs in O(N choose K) time, generating each combination in O(K) or O(1) amortized time.
//   • Invariants: Each generated combination contains exactly K distinct elements.; All elements within a combination are unique and from the original set.
//   • Tips: For lexicographical generation, find the rightmost element that can be incremented without exceeding its maximum possible value.; After incrementing an element, set all subsequent elements to their minimum valid values.
//   • Pitfalls: Incorrectly handling boundary conditions for the rightmost element or its maximum value.; Off-by-one errors when assigning subsequent elements after an increment.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int distributeCookies(int* cookies, int cookiesSize, int k) {
    // The maximum number of cookies any child can receive is at least the largest bag of cookies.
    int max_cookies = 0;
    for (int i = 0; i < cookiesSize; i++) {
        if (cookies[i] > max_cookies) {
            max_cookies = cookies[i];
        }
    }

    // The minimum unfairness cannot be less than the largest bag of cookies.
    int left = max_cookies;
    // The maximum unfairness cannot be more than the total number of cookies.
    int right = 0;
    for (int i = 0; i < cookiesSize; i++) {
        right += cookies[i];
    }

    // Binary search to find the minimum unfairness.
    while (left < right) {
        int mid = left + (right - left) / 2;

        // Check if it's possible to distribute cookies with unfairness <= mid.
        int child_count = 1;
        int current_sum = 0;
        for (int i = 0; i < cookiesSize; i++) {
            if (current_sum + cookies[i] > mid) {
                child_count++;
                current_sum = cookies[i];
                if (child_count > k) {
                    break;
                }
            } else {
                current_sum += cookies[i];
            }
        }

        if (child_count <= k) {
            right = mid; // Try for a smaller unfairness.
        } else {
            left = mid + 1; // Increase unfairness.
        }
    }

    return left;        
}
