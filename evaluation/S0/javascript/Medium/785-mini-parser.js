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
 * function NestedInteger() {
 *
 *     Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     @return {boolean}
 *     this.isInteger = function() {
 *         ...
 *     };
 *
 *     Return the single integer that this NestedInteger holds, if it holds a single integer
 *     Return null if this NestedInteger holds a nested list
 *     @return {integer}
 *     this.getInteger = function() {
 *         ...
 *     };
 *
 *     Set this NestedInteger to hold a single integer equal to value.
 *     @return {void}
 *     this.setInteger = function(value) {
 *         ...
 *     };
 *
 *     Set this NestedInteger to hold a nested list and adds a nested integer elem to it.
 *     @return {void}
 *     this.add = function(elem) {
 *         ...
 *     };
 *
 *     Return the nested list that this NestedInteger holds, if it holds a nested list
 *     Return null if this NestedInteger holds a single integer
 *     @return {NestedInteger[]}
 *     this.getList = function() {
 *         ...
 *     };
 * };
 */
/**
 * @param {string} s
 * @return {NestedInteger}
 */
var deserialize = function(s) {
    if (s[0] !== '[') {
        const ni = new NestedInteger();
        ni.setInteger(parseInt(s, 10));
        return ni;
    }
    const stack = [];
    let current = null;
    let numBuffer = '';
    for (let i = 0; i < s.length; i++) {
        const char = s[i];
        if (char === '[') {
            if (current !== null) {
                stack.push(current);
            }
            current = new NestedInteger();
        }
        else if (char === ']') {
            if (numBuffer.length > 0) {
                const ni = new NestedInteger();
                ni.setInteger(parseInt(numBuffer, 10));
                current.add(ni);
                numBuffer = '';
            }
            if (stack.length > 0) {
                const parent = stack.pop();
                parent.add(current);
                current = parent;
            }
        }
        else if (char === ',') {
            if (numBuffer.length > 0) { 
                const ni = new NestedInteger();
                ni.setInteger(parseInt(numBuffer, 10));
                current.add(ni);
                numBuffer = '';
            }
        }
        else {
            numBuffer += char;
        }
    }
    return current; 
};
