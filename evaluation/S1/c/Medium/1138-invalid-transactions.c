// Source: https://leetcode.com/problems/invalid-transactions/   |   Difficulty: Medium
//
// Problem Description:
// A transaction is possibly invalid if:
//
//
// 	the amount exceeds $1000, or;
// 	if it occurs within (and including) 60 minutes of another transaction with the same name in a different city.
//
//
// You are given an array of strings transaction where transactions[i] consists of comma-separated values representing the name, time (in minutes), amount, and city of the transaction.
//
// Return a list of transactions that are possibly invalid. You may return the answer in any order.
//
// Example:
// Input: transactions = ["alice,20,800,mtv","alice,50,100,beijing"]
// Output: ["alice,20,800,mtv","alice,50,100,beijing"]
// Explanation: The first transaction is invalid because the second transaction occurs within a difference of 60 minutes, have the same name and is in a different city. Similarly the second one is invalid too.
//
// Constraints:
// transactions.length <= 1000
// 	Each transactions[i] takes the form "{name},{time},{amount},{city}"
// 	Each {name} and {city} consist of lowercase English letters, and have lengths between 1 and 10.
// 	Each {time} consist of digits, and represent an integer between 0 and 1000.
// 	Each {amount} consist of digits, and represent an integer between 0 and 2000.
//
// Helpful references (internal KB):
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
// - palindrome-partitioning (string, two-pointers, simulation)
//   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
//   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
//   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
//   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
//   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
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
char** invalidTransactions(char** transactions, int transactionsSize, int* returnSize) {
    typedef struct {
        char name[11];
        int time;
        int amount;
        char city[11];
        int index;
    } Transaction;
    Transaction transList[transactionsSize];
    for (int i = 0; i < transactionsSize; i++) {
        char* token = strtok(transactions[i], ",");
        strcpy(transList[i].name, token);
        token = strtok(NULL, ",");
        transList[i].time = atoi(token);
        token = strtok(NULL, ",");
        transList[i].amount = atoi(token);
        token = strtok(NULL, ",");
        strcpy(transList[i].city, token);
        transList[i].index = i;
    }
    int invalidFlags[transactionsSize];
    memset(invalidFlags, 0, sizeof(invalidFlags));

    for (int i = 0; i < transactionsSize; i++) {
        if (transList[i].amount > 1000) {
            invalidFlags[i] = 1;
        }
        for (int j = 0; j < transactionsSize; j++) {
            if (i != j && strcmp(transList[i].name, transList[j].name) == 0 &&
                strcmp(transList[i].city, transList[j].city) != 0 &&
                abs(transList[i].time - transList[j].time) <= 60) {
                invalidFlags[i] = 1;
                break;
            }
        }
    }
    char** result = (char**)malloc(transactionsSize * sizeof(char*));
    int count = 0;
    for (int i = 0; i < transactionsSize; i++) {
        if (invalidFlags[i]) {
            result[count++] = transactions[transList[i].index];
        }
    }
    *returnSize = count;
    return result;
}