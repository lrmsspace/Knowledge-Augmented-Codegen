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
// - Hash Tables (array, number, string, hashing)
//   • When to use: Use when you need to store and retrieve key-value pairs efficiently by transforming keys into array indices, managing potential collisions.
//   • Idea: Hash tables map keys to array indices using a hash function, enabling average O(1) time complexity for insertions, deletions, and lookups by efficiently managing potential collisions.
//   • Invariants: The hash function always produces an index within the valid array bounds [0, M-1].; For any two equal keys, their hash values remain identical.
//   • Tips: Design hash functions for uniform key distribution across the array.; Ensure hash functions are deterministic and efficient to compute.
//   • Pitfalls: Using a hash function that does not uniformly distribute keys, leading to many collisions.; Failing to implement a proper collision resolution strategy.
// - Expression parsing (stack, simulation)
//   • When to use: This algorithm is used to evaluate expressions given in Reverse Polish Notation (postfix notation) to compute their final numerical value.
//   • Idea: This algorithm evaluates an expression in Reverse Polish Notation by processing elements sequentially. Numbers are pushed onto a stack, and operators pop two operands, compute, and push the result.
//   • Invariants: The stack always contains only numbers (operands or intermediate results).; For a valid RPN expression, the stack will have at least two elements when an operator is processed.
//   • Tips: Process the RPN expression from left to right, token by token.; Push numerical operands directly onto the stack.
//   • Pitfalls: Attempting to pop from an empty stack when an operator is encountered, indicating an invalid RPN expression.; Incorrect order of operands for non-commutative operations like subtraction or division.
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
    // Step 1: Parse transactions into structured format
    typedef struct {
        char name[11];
        int time;
        int amount;
        char city[11];
        char original[50]; // To store the original transaction string
    } Transaction;

    Transaction parsed[transactionsSize];
    for (int i = 0; i < transactionsSize; i++) {
        sscanf(transactions[i], "%[^,],%d,%d,%[^,]", parsed[i].name, &parsed[i].time, &parsed[i].amount, parsed[i].city);
        strcpy(parsed[i].original, transactions[i]);
    }

    // Step 2: Identify invalid transactions
    char** invalids = (char**)malloc(transactionsSize * sizeof(char*));
    int count = 0;
    for (int i = 0; i < transactionsSize; i++) {
        if (parsed[i].amount > 1000) {
            invalids[count++] = strdup(parsed[i].original);
            continue;
        }
        for (int j = 0; j < transactionsSize; j++) {
            if (i != j && strcmp(parsed[i].name, parsed[j].name) == 0 && strcmp(parsed[i].city, parsed[j].city) != 0 && abs(parsed[i].time - parsed[j].time) <= 60) {
                invalids[count++] = strdup(parsed[i].original);
                break;
            }
        }
    }
    *returnSize = count;
    return invalids;
}
