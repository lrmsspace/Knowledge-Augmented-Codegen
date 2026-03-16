// Source: https://leetcode.com/problems/check-if-binary-string-has-at-most-one-segment-of-ones/   |   Difficulty: Easy
//
// Problem Description:
// Given a binary string s ​​​​​without leading zeros, return true​​​ if s contains at most one contiguous segment of ones. Otherwise, return false.
//
// Example:
// Input: s = "1001"
// Output: false
// Explanation: The ones do not form a contiguous segment.
//
// Constraints:
// 1 <= s.length <= 100
// 	s[i]​​​​ is either '0' or '1'.
// 	s[0] is '1'.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public boolean checkOnesSegment(String s) {
        return !s.contains("01");           
    }
}
