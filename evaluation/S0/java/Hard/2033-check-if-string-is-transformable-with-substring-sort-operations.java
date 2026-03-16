// Source: https://leetcode.com/problems/check-if-string-is-transformable-with-substring-sort-operations/   |   Difficulty: Hard
//
// Problem Description:
// Given two strings s and t, transform string s into string t using the following operation any number of times:
//
//
// 	Choose a non-empty substring in s and sort it in place so the characters are in ascending order.
//
// 	
// 		For example, applying the operation on the underlined substring in "14234" results in "12344".
// 	
// 	
//
//
// Return true if it is possible to transform s into t. Otherwise, return false.
//
// A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: s = "84532", t = "34852"
// Output: true
// Explanation: You can transform s into t using the following sort operations:
// "84532" (from index 2 to 3) -> "84352"
// "84352" (from index 0 to 2) -> "34852"
//
// Constraints:
// s.length == t.length
// 	1 <= s.length <= 105
// 	s and t consist of only digits.
//

class Solution {
    public boolean isTransformable(String s, String t) {
        int n = s.length();
        List<Deque<Integer>> pos = new ArrayList<>();
        for (int i = 0; i < 10; i++) {
            pos.add(new ArrayDeque<>());
        }
        for (int i = 0; i < n; i++) {
            pos.get(s.charAt(i) - '0').addLast(i);
        }

        FenwickTree fenwickTree = new FenwickTree(n);
        for (int i = 0; i < n; i++) {
            int digit = t.charAt(i) - '0';
            for (int d = 0; d < digit; d++) {
                if (!pos.get(d).isEmpty()) {
                    int index = pos.get(d).peekFirst();
                    int shifts = fenwickTree.query(index + 1, n - 1);
                    if (index + shifts < i) {
                        return false;
                    }
                }
            }
            if (pos.get(digit).isEmpty()) {
                return false;
            }
            int index = pos.get(digit).pollFirst();
            int shifts = fenwickTree.query(index + 1, n - 1);
            if (index + shifts > i) {
                return false;
            }
            fenwickTree.update(1, index);
        }
        return true;                    
    }
}
