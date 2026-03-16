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
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Constructor initializes an empty nested list.
 *     NestedInteger();
 *
 *     // Constructor initializes a single integer.
 *     NestedInteger(int value);
 *
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Set this NestedInteger to hold a single integer.
 *     void setInteger(int value);
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     void add(const NestedInteger &ni);
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class Solution {
public:
    NestedInteger deserialize(string s) {
        if (s.empty()) return NestedInteger();

        // If the string does not start with '[', it's a single integer
        if (s[0] != '[') {
            return NestedInteger(stoi(s));
        }

        stack<NestedInteger> stk;
        NestedInteger currentList;
        int num = 0;
        bool negative = false;
        bool hasNum = false;

        for (size_t i = 0; i < s.size(); ++i) {
            char ch = s[i];
            if (ch == '[') {
                // Start a new nested list
                stk.push(currentList);
                currentList = NestedInteger();
            } else if (ch == ']') {
                // End of a nested list
                if (hasNum) {
                    currentList.add(NestedInteger(negative ? -num : num));
                    num = 0;
                    negative = false;
                    hasNum = false;
                }
                NestedInteger completedList = currentList;
                currentList = stk.top();
                stk.pop();
                currentList.add(completedList);
            } else if (ch == ',') {
                // Separator between elements
                if (hasNum) {
                    currentList.add(NestedInteger(negative ? -num : num));
                    num = 0;
                    negative = false;
                    hasNum = false;
                }
            } else if (ch == '-') {
                negative = true;
            } else if (isdigit(ch)) {
                num = num * 10 + (ch - '0');
                hasNum = true;
            }
        }

        return currentList;         
    }
};
