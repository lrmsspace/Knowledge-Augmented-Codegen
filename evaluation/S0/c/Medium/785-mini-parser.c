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
    if (!s) return NULL;

    int len = strlen(s);
    if (len == 0) return NULL;

    // If the string does not start with '[', it is a single integer
    if (s[0] != '[') {
        struct NestedInteger* ni = NestedIntegerInit();
        NestedIntegerSetInteger(ni, atoi(s));
        return ni;
    }

    // Stack to hold nested integers
    struct NestedInteger** stack = (struct NestedInteger**)malloc(len * sizeof(struct NestedInteger*));
    int top = -1;

    struct NestedInteger* current = NULL;
    int num = 0;
    int negative = 0;
    int has_num = 0;

    for (int i = 0; i < len; i++) {
        char c = s[i];

        if (c == '[') {
            struct NestedInteger* ni = NestedIntegerInit();
            if (current) {
                stack[++top] = current;
            }
            current = ni;
        } else if (c == ']') {
            if (has_num) {
                if (negative) num = -num;
                struct NestedInteger* ni = NestedIntegerInit();
                NestedIntegerSetInteger(ni, num);
                NestedIntegerAdd(current, ni);
                num = 0;
                negative = 0;
                has_num = 0;
            }
            if (top >= 0) {
                struct NestedInteger* parent = stack[top--];
                NestedIntegerAdd(parent, current);
                current = parent;
            }
        } else if (c == ',') {
            if (has_num) {
                if (negative) num = -num;
                struct NestedInteger* ni = NestedIntegerInit();
                NestedIntegerSetInteger(ni, num);
                NestedIntegerAdd(current, ni);
                num = 0;
                negative = 0;
                has_num = 0;
            }
        } else if (c == '-') {
            negative = 1;
        } else if (isdigit(c)) {
            num = num * 10 + (c - '0');
            has_num = 1;
        }
    }

    return current;     
}
