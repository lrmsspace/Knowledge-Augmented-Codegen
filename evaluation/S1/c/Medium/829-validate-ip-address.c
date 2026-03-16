// Source: https://leetcode.com/problems/validate-ip-address/   |   Difficulty: Medium
//
// Problem Description:
// Given a string queryIP, return "IPv4" if IP is a valid IPv4 address, "IPv6" if IP is a valid IPv6 address or "Neither" if IP is not a correct IP of any type.
//
// A valid IPv4 address is an IP in the form "x1.x2.x3.x4" where 0 <= xi <= 255 and xi cannot contain leading zeros. For example, "192.168.1.1" and "192.168.1.0" are valid IPv4 addresses while "192.168.01.1", "192.168.1.00", and "192.168@1.1" are invalid IPv4 addresses.
//
// A valid IPv6 address is an IP in the form "x1:x2:x3:x4:x5:x6:x7:x8" where:
//
//
// 	1 <= xi.length <= 4
// 	xi is a hexadecimal string which may contain digits, lowercase English letter ('a' to 'f') and upper-case English letters ('A' to 'F').
// 	Leading zeros are allowed in xi.
//
//
// For example, "2001:0db8:85a3:0000:0000:8a2e:0370:7334" and "2001:db8:85a3:0:0:8A2E:0370:7334" are valid IPv6 addresses, while "2001:0db8:85a3::8A2E:037j:7334" and "02001:0db8:85a3:0000:0000:8a2e:0370:7334" are invalid IPv6 addresses.
//
// Example:
// Input: queryIP = "172.16.254.1"
// Output: "IPv4"
// Explanation: This is a valid IPv4 address, return "IPv4".
//
// Constraints:
// queryIP consists only of English letters, digits and the characters '.' and ':'.
//
// Helpful references (internal KB):
// - palindrome-partitioning (string, array, backtracking, recursion)
//   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
//   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
//   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
//   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
//   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
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

char* validIPAddress(char* queryIP) {
    int is_ipv4 = 1, is_ipv6 = 1;
    int len = 0, seg_count = 0;
    char *p = queryIP;

    while (*p) {
        if (*p == '.') {
            seg_count++;
            len = 0;
        } else if (*p == ':') {
            seg_count++;
            len = 0;
        } else {
            len++;
        }
        p++;
    }
    seg_count++; // last segment

    if (seg_count == 4) {
        p = queryIP;
        for (int i = 0; i < 4; i++) {
            int seg_len = 0, seg_val = 0;
            if (i > 0) {
                if (*p != '.') {
                    is_ipv4 = 0;
                    break;
                }
                p++;
            }
            while (*p && *p != '.' && *p != ':') {
                if (!(*p >= '0' && *p <= '9')) {
                    is_ipv4 = 0;
                    break;
                }
                seg_val = seg_val * 10 + (*p - '0');
                seg_len++;
                p++;
            }
            if (seg_len == 0 || seg_len > 3 || (seg_len > 1 && *(p - seg_len) == '0') || seg_val > 255) {
                is_ipv4 = 0;
                break;
            }
        }
    } else {
        is_ipv4 = 0;
    }

    if (seg_count == 8) {
        p = queryIP;
        for (int i = 0; i < 8; i++) {
            int seg_len = 0;
            if (i > 0) {
                if (*p != ':') {
                    is_ipv6 = 0;
                    break;
                }
                p++;
            }
            while (*p && *p != '.' && *p != ':') {
                if (!((*p >= '0' && *p <= '9') || (*p >= 'a' && *p <= 'f') || (*p >= 'A' && *p <= 'F'))) {
                    is_ipv6 = 0;
                    break;
                }
                seg_len++;
                p++;
            }
            if (seg_len == 0 || seg_len > 4) {
                is_ipv6 = 0;
                break;
            }
        }
    } else {
        is_ipv6 = 0;
    }
    if (is_ipv4) return "IPv4";
    if (is_ipv6) return "IPv6";
    return "Neither"; 
}
