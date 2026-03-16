// Source: https://leetcode.com/problems/restore-ip-addresses/   |   Difficulty: Medium
//
// Problem Description:
// A valid IP address consists of exactly four integers separated by single dots. Each integer is between 0 and 255 (inclusive) and cannot have leading zeros.
//
//
// 	For example, "0.1.2.201" and "192.168.1.1" are valid IP addresses, but "0.011.255.245", "192.168.1.312" and "192.168@1.1" are invalid IP addresses.
//
//
// Given a string s containing only digits, return all possible valid IP addresses that can be formed by inserting dots into s. You are not allowed to reorder or remove any digits in s. You may return the valid IP addresses in any order.
//
// Example:
// Input: s = "25525511135"
// Output: ["255.255.11.135","255.255.111.35"]
//
// Constraints:
// 1 <= s.length <= 20
// 	s consists of digits only.
//
// Helpful references (internal KB):
// - palindrome-partitioning (string, array, backtracking, recursion)
//   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
//   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
//   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
//   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
//   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
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
char** restoreIpAddresses(char* s, int* returnSize) {
    int len = strlen(s);
    char** result = (char**)malloc(1000 * sizeof(char*)); // Allocate memory for results
    *returnSize = 0;

    for (int i = 1; i < 4 && i < len - 2; i++) {
        for (int j = i + 1; j < i + 4 && j < len - 1; j++) {
            for (int k = j + 1; k < j + 4 && k < len; k++) {
                if (len - k > 3) continue;

                char part1[4], part2[4], part3[4], part4[4];
                strncpy(part1, s, i);
                part1[i] = '\0';
                strncpy(part2, s + i, j - i);
                part2[j - i] = '\0';
                strncpy(part3, s + j, k - j);
                part3[k - j] = '\0';
                strncpy(part4, s + k, len - k);
                part4[len - k] = '\0';

                int num1 = atoi(part1);
                int num2 = atoi(part2);
                int num3 = atoi(part3);
                int num4 = atoi(part4);

                if ((part1[0] == '0' && strlen(part1) > 1) || num1 > 255) continue;
                if ((part2[0] == '0' && strlen(part2) > 1) || num2 > 255) continue;
                if ((part3[0] == '0' && strlen(part3) > 1) || num3 > 255) continue;
                if ((part4[0] == '0' && strlen(part4) > 1) || num4 > 255) continue;

                char* ipAddress = (char*)malloc(16 * sizeof(char));
                sprintf(ipAddress, "%s.%s.%s.%s", part1, part2, part3, part4);
                result[(*returnSize)++] = ipAddress;
            }
        }
    }

    return result;      
}
