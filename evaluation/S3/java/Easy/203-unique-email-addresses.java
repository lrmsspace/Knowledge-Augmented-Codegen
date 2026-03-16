// Source: https://leetcode.com/problems/unique-email-addresses/   |   Difficulty: Easy
//
// Problem Description:
// Every valid email consists of a local name and a domain name, separated by the '@' sign. Besides lowercase letters, the email may contain one or more '.' or '+'.
//
//
// 	For example, in "alice@leetcode.com", "alice" is the local name, and "leetcode.com" is the domain name.
//
//
// If you add periods '.' between some characters in the local name part of an email address, mail sent there will be forwarded to the same address without dots in the local name. Note that this rule does not apply to domain names.
//
//
// 	For example, "alice.z@leetcode.com" and "alicez@leetcode.com" forward to the same email address.
//
//
// If you add a plus '+' in the local name, everything after the first plus sign will be ignored. This allows certain emails to be filtered. Note that this rule does not apply to domain names.
//
//
// 	For example, "m.y+name@email.com" will be forwarded to "my@email.com".
//
//
// It is possible to use both of these rules at the same time.
//
// Given an array of strings emails where we send one email to each emails[i], return the number of different addresses that actually receive mails.
//
// Example:
// Input: emails = ["test.email+alex@leetcode.com","test.e.mail+bob.cathy@leetcode.com","testemail+david@lee.tcode.com"]
// Output: 2
// Explanation: "testemail@leetcode.com" and "testemail@lee.tcode.com" actually receive mails.
//
// Constraints:
// 1 <= emails.length <= 100
// 	1 <= emails[i].length <= 100
// 	emails[i] consist of lowercase English letters, '+', '.' and '@'.
// 	Each emails[i] contains exactly one '@' character.
// 	All local and domain names are non-empty.
// 	Local names do not start with a '+' character.
// 	Domain names end with the ".com" suffix.
// 	Domain names must contain at least one character before ".com" suffix.
//
// Helpful references (internal KB):
// - Expression parsing (stack, simulation)
//   • When to use: This algorithm is used to evaluate expressions given in Reverse Polish Notation (postfix notation) to compute their final numerical value.
//   • Idea: This algorithm evaluates an expression in Reverse Polish Notation by processing elements sequentially. Numbers are pushed onto a stack, and operators pop two operands, compute, and push the result.
//   • Invariants: The stack always contains only numbers (operands or intermediate results).; For a valid RPN expression, the stack will have at least two elements when an operator is processed.
//   • Tips: Process the RPN expression from left to right, token by token.; Push numerical operands directly onto the stack.
//   • Pitfalls: Attempting to pop from an empty stack when an operator is encountered, indicating an invalid RPN expression.; Incorrect order of operands for non-commutative operations like subtraction or division.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Substring Search (string, array, kmp, simulation)
//   • When to use: Use when efficiently finding all occurrences or the first occurrence of a pattern within a larger text, especially when the pattern might have repeating or overlapping prefixes.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm is an efficient string-searching algorithm that avoids re-scanning characters in the text by pre-processing the pattern to build a 'longest proper prefix suffix' (LPS) array. It achieves optimal O(N + M) time complexity, where N is the text length and M is the pattern length.
//   • Invariants: The `j` pointer always indicates the length of the longest proper prefix of `pattern[0...j-1]` that is also a suffix of `text[0...i-1]`.; The `lps[j]` value stores the length of the longest proper prefix of `pattern[0...j-1]` that is also a suffix of `pattern[0...j-1]`.
//   • Tips: Pre-compute the LPS array (also known as failure function or border array) for the pattern.; The LPS array helps determine the next best match position after a mismatch, avoiding redundant comparisons.
//   • Pitfalls: Incorrectly building the LPS array can lead to wrong matches or infinite loops.; Off-by-one errors when indexing the pattern or text are common.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int numUniqueEmails(String[] emails) {
        Set<String> uniqueEmails = new HashSet<>();

        for (String email : emails) {
            String[] parts = email.split("@");
            String localName = parts[0];
            String domainName = parts[1];

            // Remove all '.' from the local name
            localName = localName.replace(".", "");

            // Ignore everything after the first '+' in the local name
            int plusIndex = localName.indexOf('+');
            if (plusIndex != -1) {
                localName = localName.substring(0, plusIndex);
            }

            // Combine the processed local name with the domain name
            String processedEmail = localName + "@" + domainName;
            uniqueEmails.add(processedEmail);
        }

        return uniqueEmails.size();         
    }
}
