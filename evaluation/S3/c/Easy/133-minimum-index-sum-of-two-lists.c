// Source: https://leetcode.com/problems/minimum-index-sum-of-two-lists/   |   Difficulty: Easy
//
// Problem Description:
// Given two arrays of strings list1 and list2, find the common strings with the least index sum.
//
// A common string is a string that appeared in both list1 and list2.
//
// A common string with the least index sum is a common string such that if it appeared at list1[i] and list2[j] then i + j should be the minimum value among all the other common strings.
//
// Return all the common strings with the least index sum. Return the answer in any order.
//
// Example:
// Input: list1 = ["Shogun","Tapioca Express","Burger King","KFC"], list2 = ["Piatti","The Grill at Torrey Pines","Hungry Hunter Steakhouse","Shogun"]
// Output: ["Shogun"]
// Explanation: The only common string is "Shogun".
//
// Constraints:
// 1 <= list1.length, list2.length <= 1000
// 	1 <= list1[i].length, list2[i].length <= 30
// 	list1[i] and list2[i] consist of spaces ' ' and English letters.
// 	All the strings of list1 are unique.
// 	All the strings of list2 are unique.
// 	There is at least a common string between list1 and list2.
//
// Helpful references (internal KB):
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
// - String Hashing (string, number, hashing)
//   • When to use: Use when needing to compare strings or substrings quickly, reducing comparison time from linear to constant. It is ideal for problems requiring frequent string equality checks or pattern matching across large texts.
//   • Idea: String hashing maps a string to an integer hash value, allowing for O(1) equality checks between strings or substrings. This technique relies on a hash function where equal strings must produce equal hashes, though the reverse is not guaranteed.
//   • Invariants: The hash of any prefix s[0...i] is correctly computed based on s[0...i-1] and s[i].; All characters processed up to the current index i contribute to the current hash value.
//   • Tips: Use a polynomial rolling hash function with a prime base and a large prime modulus.; Employ double hashing (two different bases/moduli) to significantly reduce collision probability.
//   • Pitfalls: Hash collisions: Different strings can produce the same hash, leading to false positives if not handled.; Poor choice of base or modulus can lead to more frequent collisions.
// - String Hashing (string, number, hashing, prefix-sum)
//   • When to use: Use string hashing to efficiently compare strings, find duplicate strings, or perform fast substring searches and pattern matching in O(1) time after initial O(N) preprocessing.
//   • Idea: String hashing maps a string to a numerical value using a polynomial function, enabling O(1) comparison of strings or substrings after O(N) preprocessing.
//   • Invariants: prefix_hash[i] stores the polynomial hash of the substring s[0...i-1].; p_power[k] stores p^k mod m for efficient calculation.
//   • Tips: Use two different hash functions with distinct prime `p` and `m` values to minimize collision probability.; Precompute powers of `p` and prefix hashes to enable O(1) substring hash calculation.
//   • Pitfalls: Hash collisions can lead to incorrect results; always consider their possibility.; Integer overflow if modulo operations are not applied correctly at each step of calculation.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** findRestaurant(char** list1, int list1Size, char** list2, int list2Size, int* returnSize) {
    // Create a hash map to store the index of each restaurant in list1
    int hashSize = 2003; // A prime number for better distribution
    char* hashKeys[hashSize];
    int hashValues[hashSize];
    for (int i = 0; i < hashSize; i++) {
        hashKeys[i] = NULL;
        hashValues[i] = -1;
    }

    // Populate the hash map with restaurants from list1
    for (int i = 0; i < list1Size; i++) {
        int hashIndex = (unsigned long)list1[i] % hashSize;
        while (hashKeys[hashIndex] != NULL) {
            if (strcmp(hashKeys[hashIndex], list1[i]) == 0) {
                break; // Restaurant already in hash, skip
            }
            hashIndex = (hashIndex + 1) % hashSize; // Linear probing
        }
        if (hashKeys[hashIndex] == NULL) {
            hashKeys[hashIndex] = list1[i];
            hashValues[hashIndex] = i;
        }
    }

    // Find common restaurants with the least index sum
    int minSum = __INT_MAX__;
    char* result[1000]; // To store common restaurants
    int count = 0;

    for (int j = 0; j < list2Size; j++) {
        int hashIndex = (unsigned long)list2[j] % hashSize;
        while (hashKeys[hashIndex] != NULL) {
            if (strcmp(hashKeys[hashIndex], list2[j]) == 0) {
                int sum = hashValues[hashIndex] + j;
                if (sum < minSum) {
                    minSum = sum;
                    count = 0; // Reset count for new minimum
                    result[count++] = list2[j];
                } else if (sum == minSum) {
                    result[count++] = list2[j]; // Add to result if same minimum
                }
                break;
            }
            hashIndex = (hashIndex + 1) % hashSize; // Linear probing
        }
    }

    // Prepare the return value
    char** returnArray = malloc(count * sizeof(char*));
    for (int k = 0; k < count; k++) {
        returnArray[k] = result[k];     
}
