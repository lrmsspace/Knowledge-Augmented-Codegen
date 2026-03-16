// Source: https://leetcode.com/problems/mini-parser/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s represents the serialization of a nested list, implement a parser to deserialize it and return the deserialized NestedInteger.
//
// Each element is either an integer or a list whose elements may also be integers or other lists.
//
// Example:
// Input: s = "324"
// Output: 324
// Explanation: You should return a NestedInteger object which contains a single integer 324.
//
// Constraints:
// 1 <= s.length <= 5 * 104
// 	s consists of digits, square brackets "[]", negative sign '-', and commas ','.
// 	s is the serialization of valid NestedInteger.
// 	All the values in the input are in the range [-106, 106].
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * *********************************************************************
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * *********************************************************************
 *
 * // Initializes an empty nested list and return a reference to the nested integer.
 * struct NestedInteger *NestedIntegerInit();
 *
 * // Return true if this NestedInteger holds a single integer, rather than a nested list.
 * bool NestedIntegerIsInteger(struct NestedInteger *);
 *
 * // Return the single integer that this NestedInteger holds, if it holds a single integer
 * // The result is undefined if this NestedInteger holds a nested list
 * int NestedIntegerGetInteger(struct NestedInteger *);
 *
 * // Set this NestedInteger to hold a single integer.
 * void NestedIntegerSetInteger(struct NestedInteger *ni, int value);
 *
 * // Set this NestedInteger to hold a nested list and adds a nested integer elem to it.
 * void NestedIntegerAdd(struct NestedInteger *ni, struct NestedInteger *elem);
 *
 * // Return the nested list that this NestedInteger holds, if it holds a nested list
 * // The result is undefined if this NestedInteger holds a single integer
 * struct NestedInteger **NestedIntegerGetList(struct NestedInteger *);
 *
 * // Return the nested list's size that this NestedInteger holds, if it holds a nested list
 * // The result is undefined if this NestedInteger holds a single integer
 * int NestedIntegerGetListSize(struct NestedInteger *);
 * };
 */
struct NestedInteger* deserialize(char* s) {
    if (s == NULL || *s == '\0') {
        return NULL;
    }

    // If the string does not start with '[', it's a single integer
    if (*s != '[') {
        struct NestedInteger* ni = NestedIntegerInit();
        NestedIntegerSetInteger(ni, atoi(s));
        return ni;
    }

    // Stack to hold nested integers
    struct NestedInteger* stack[100]; // Assuming max depth of 100
    int top = -1;

    char* p = s;
    while (*p) {
        if (*p == '[') {
            // Start a new nested list
            struct NestedInteger* ni = NestedIntegerInit();
            if (top >= 0) {
                NestedIntegerAdd(stack[top], ni);
            }
            stack[++top] = ni;
            p++;
        } else if (*p == ']') {
            // End of current nested list
            top--;
            p++;
        } else if (*p == ',') {
            // Move to the next element
            p++;
        } else {
            // Parse an integer
            char* start = p;
            while (*p && *p != ',' && *p != ']') {
                p++;
            }
            char temp = *p; // Store the delimiter
            *p = '\0'; // Null-terminate the integer string

            struct NestedInteger* ni = NestedIntegerInit();
            NestedIntegerSetInteger(ni, atoi(start));
            if (top >= 0) {
                NestedIntegerAdd(stack[top], ni);
            }

            *p = temp; // Restore the delimiter
        }
    }

    return stack[0]; // The root nested integer     
}
