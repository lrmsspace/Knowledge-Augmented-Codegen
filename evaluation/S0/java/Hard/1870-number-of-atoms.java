// Source: https://leetcode.com/problems/number-of-atoms/   |   Difficulty: Hard
//
// Problem Description:
// Given a string formula representing a chemical formula, return the count of each atom.
//
// The atomic element always starts with an uppercase character, then zero or more lowercase letters, representing the name.
//
// One or more digits representing that element's count may follow if the count is greater than 1. If the count is 1, no digits will follow.
//
//
// 	For example, "H2O" and "H2O2" are possible, but "H1O2" is impossible.
//
//
// Two formulas are concatenated together to produce another formula.
//
//
// 	For example, "H2O2He3Mg4" is also a formula.
//
//
// A formula placed in parentheses, and a count (optionally added) is also a formula.
//
//
// 	For example, "(H2O2)" and "(H2O2)3" are formulas.
//
//
// Return the count of all elements as a string in the following form: the first name (in sorted order), followed by its count (if that count is more than 1), followed by the second name (in sorted order), followed by its count (if that count is more than 1), and so on.
//
// The test cases are generated so that all the values in the output fit in a 32-bit integer.
//
// Example:
// Input: formula = "H2O"
// Output: "H2O"
// Explanation: The count of elements are {'H': 2, 'O': 1}.
//
// Constraints:
// 1 <= formula.length <= 1000
// 	formula consists of English letters, digits, '(', and ')'.
// 	formula is always valid.
//

class Solution {
    public String countOfAtoms(String formula) {
        int i = 0;
        int n = formula.length();
        Deque<Map<String, Integer>> stack = new ArrayDeque<>();
        stack.push(new TreeMap<>());

        while (i < n) {
            char ch = formula.charAt(i);

            if (ch == '(') {
                stack.push(new TreeMap<>());
                i++;
            } else if (ch == ')') {
                i++;
                int start = i;
                while (i < n && Character.isDigit(formula.charAt(i))) {
                    i++;
                }
                int multiplier = start < i ? Integer.parseInt(formula.substring(start, i)) : 1;

                Map<String, Integer> top = stack.pop();
                Map<String, Integer> next = stack.peek();

                for (String atom : top.keySet()) {
                    next.put(atom, next.getOrDefault(atom, 0) + top.get(atom) * multiplier);
                }
            } else {
                int start = i;
                i++;
                while (i < n && Character.isLowerCase(formula.charAt(i))) {
                    i++;
                }
                String atom = formula.substring(start, i);

                start = i;
                while (i < n && Character.isDigit(formula.charAt(i))) {
                    i++;
                }
                int count = start < i ? Integer.parseInt(formula.substring(start, i)) : 1;

                Map<String, Integer> top = stack.peek();
                top.put(atom, top.getOrDefault(atom, 0) + count);
            }
        }

        StringBuilder result = new StringBuilder();
        Map<String, Integer> finalMap = stack.pop();
        for (String atom : finalMap.keySet()) {
            result.append(atom);
            int count = finalMap.get(atom);
            if (count > 1) {
                result.append(count);
            }
        }

        return result.toString();           
    }
}
