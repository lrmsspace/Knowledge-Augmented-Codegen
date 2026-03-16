// Source: https://leetcode.com/problems/basic-calculator-iv/   |   Difficulty: Hard
//
// Problem Description:
// Given an expression such as expression = "e + 8 - a + 5" and an evaluation map such as {"e": 1} (given in terms of evalvars = ["e"] and evalints = [1]), return a list of tokens representing the simplified expression, such as ["-1*a","14"]
//
//
// 	An expression alternates chunks and symbols, with a space separating each chunk and symbol.
// 	A chunk is either an expression in parentheses, a variable, or a non-negative integer.
// 	A variable is a string of lowercase letters (not including digits.) Note that variables can be multiple letters, and note that variables never have a leading coefficient or unary operator like "2x" or "-x".
//
//
// Expressions are evaluated in the usual order: brackets first, then multiplication, then addition and subtraction.
//
//
// 	For example, expression = "1 + 2 * 3" has an answer of ["7"].
//
//
// The format of the output is as follows:
//
//
// 	For each term of free variables with a non-zero coefficient, we write the free variables within a term in sorted order lexicographically.
// 	
// 		For example, we would never write a term like "b*a*c", only "a*b*c".
// 	
// 	
// 	Terms have degrees equal to the number of free variables being multiplied, counting multiplicity. We write the largest degree terms of our answer first, breaking ties by lexicographic order ignoring the leading coefficient of the term.
// 	
// 		For example, "a*a*b*c" has degree 4.
// 	
// 	
// 	The leading coefficient of the term is placed directly to the left with an asterisk separating it from the variables (if they exist.) A leading coefficient of 1 is still printed.
// 	An example of a well-formatted answer is ["-2*a*a*a", "3*a*a*b", "3*b*b", "4*a", "5*c", "-6"].
// 	Terms (including constant terms) with coefficient 0 are not included.
// 	
// 		For example, an expression of "0" has an output of [].
// 	
// 	
//
//
// Note: You may assume that the given expression is always valid. All intermediate results will be in the range of [-231, 231 - 1].
//
// Example:
// Input: expression = "e + 8 - a + 5", evalvars = ["e"], evalints = [1]
// Output: ["-1*a","14"]
//
// Constraints:
// 1 <= expression.length <= 250
// 	expression consists of lowercase English letters, digits, '+', '-', '*', '(', ')', ' '.
// 	expression does not contain any leading or trailing spaces.
// 	All the tokens in expression are separated by a single space.
// 	0 <= evalvars.length <= 100
// 	1 <= evalvars[i].length <= 20
// 	evalvars[i] consists of lowercase English letters.
// 	evalints.length == evalvars.length
// 	-100 <= evalints[i] <= 100
//
// Helpful references (internal KB):
// - Operations on polynomials and series (array, recursion)
//   • When to use: When problems involve manipulating algebraic polynomials or power series, especially when their properties or coefficients are defined recursively. It is also useful for problems involving generating functions to represent sequences.
//   • Idea: This card describes recursive approaches to perform common operations on polynomials and power series, often represented by their coefficients. The complexity varies depending on the specific operation, but many are O(N^2) or O(N log N) with optimized techniques.
//   • Invariants: For a polynomial represented by P[0...N-1], P[i] always stores the coefficient of x^i.; When performing an operation recursively, the result of subproblems correctly represents the corresponding sub-polynomial or sub-series.
//   • Tips: Represent polynomials as arrays of coefficients.; Base cases for recursion are crucial (e.g., constant polynomial, empty series).
//   • Pitfalls: Incorrectly handling polynomial degrees or series truncation.; Off-by-one errors in coefficient indexing.
// - Expression parsing (stack, simulation)
//   • When to use: Use this algorithm to evaluate an arithmetic expression given in infix notation, respecting operator precedence and parentheses. It is suitable for expressions with binary, left-associative operators.
//   • Idea: This algorithm evaluates an infix arithmetic expression using two stacks: one for operands and one for operators. It processes the expression from left to right, applying operator precedence and associativity rules to achieve an O(N) time complexity.
//   • Invariants: The operand stack always contains valid numerical values or intermediate results.; The operator stack maintains operators such that operators with higher or equal precedence are processed before lower precedence ones.
//   • Tips: Clearly define operator precedence and associativity rules for all operators.; Use a separate stack for operands (numbers) and operators (including parentheses).
//   • Pitfalls: Misinterpreting operator precedence or associativity rules can lead to incorrect results.; Failure to handle mismatched or unbalanced parentheses can cause runtime errors.
// - String Hashing (string, number, hashing, prefix-sum)
//   • When to use: Use string hashing to efficiently compare strings, find duplicate strings, or perform fast substring searches and pattern matching in O(1) time after initial O(N) preprocessing.
//   • Idea: String hashing maps a string to a numerical value using a polynomial function, enabling O(1) comparison of strings or substrings after O(N) preprocessing.
//   • Invariants: prefix_hash[i] stores the polynomial hash of the substring s[0...i-1].; p_power[k] stores p^k mod m for efficient calculation.
//   • Tips: Use two different hash functions with distinct prime `p` and `m` values to minimize collision probability.; Precompute powers of `p` and prefix hashes to enable O(1) substring hash calculation.
//   • Pitfalls: Hash collisions can lead to incorrect results; always consider their possibility.; Integer overflow if modulo operations are not applied correctly at each step of calculation.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

class Solution {
    public List<String> basicCalculatorIV(String expression, String[] evalvars, int[] evalints) {
        Map<String, Integer> eval = new HashMap<>();
        for (int i = 0; i < evalvars.length; i++) {
            eval.put(evalvars[i], evalints[i]);
        }

        String[] tokens = expression.split(" ");
        int[] index = new int[] {0};
        Poly poly = parseExpr(tokens, index, eval);
        return poly.toList();
    }

    private Poly parseExpr(String[] tokens, int[] index, Map<String, Integer> eval) {
        Poly result = parseTerm(tokens, index, eval);
        while (index[0] < tokens.length) {
            String op = tokens[index[0]];
            if (!op.equals("+") && !op.equals("-")) {
                break;
            }
            index[0]++;
            Poly right = parseTerm(tokens, index, eval);
            if (op.equals("+")) {
                result = result.add(right);
            } else {
                result = result.sub(right);
            }
        }
        return result;
    }

    private Poly parseTerm(String[] tokens, int[] index, Map<String, Integer> eval) {
        Poly result = parseFactor(tokens, index, eval);
        while (index[0] < tokens.length) {
            String op = tokens[index[0]];
            if (!op.equals("*")) {
                break;
            }
            index[0]++;
            Poly right = parseFactor(tokens, index, eval);
            result = result.mul(right);
        }
        return result;
    }

    private Poly parseFactor(String[] tokens, int[] index, Map<String, Integer> eval) {
        String token = tokens[index[0]];
        if (token.equals("(")) {
            index[0]++;
            Poly inside = parseExpr(tokens, index, eval);
            if (index[0] < tokens.length && tokens[index[0]].equals(")")) {
                index[0]++;
            }
            return inside;
        }

        index[0]++;
        if (isNumber(token)) {
            return Poly.fromConst(Integer.parseInt(token));
        }

        if (eval.containsKey(token)) {
            return Poly.fromConst(eval.get(token));
        }
        return Poly.fromVar(token);
    }

    private boolean isNumber(String token) {
        int n = token.length();
        if (n == 0) {
            return false;
        }
        for (int i = 0; i < n; i++) {
            char c = token.charAt(i);
            if (c < '0' || c > '9') {
                return false;
            }
        }
        return true;
    }

    private static class Poly {
        private final Map<List<String>, Integer> terms;

        private Poly() {
            this.terms = new HashMap<>();
        }

        public static Poly fromConst(int value) {
            Poly poly = new Poly();
            if (value != 0) {
                poly.terms.put(Collections.emptyList(), value);
            }
            return poly;
        }

        public static Poly fromVar(String var) {
            Poly poly = new Poly();
            List<String> key = new ArrayList<>();
            key.add(var);
            poly.terms.put(key, 1);
            return poly;
        }

        public Poly add(Poly other) {
            Poly res = new Poly();
            res.terms.putAll(this.terms);
            for (Map.Entry<List<String>, Integer> entry : other.terms.entrySet()) {
                res.terms.put(entry.getKey(), res.terms.getOrDefault(entry.getKey(), 0) + entry.getValue());
            }
            res.removeZeroes();
            return res;
        }

        public Poly sub(Poly other) {
            Poly res = new Poly();
            res.terms.putAll(this.terms);
            for (Map.Entry<List<String>, Integer> entry : other.terms.entrySet()) {
                res.terms.put(entry.getKey(), res.terms.getOrDefault(entry.getKey(), 0) - entry.getValue());
            }
            res.removeZeroes();
            return res;
        }

        public Poly mul(Poly other) {
            Poly res = new Poly();
            for (Map.Entry<List<String>, Integer> e1 : this.terms.entrySet()) {
                for (Map.Entry<List<String>, Integer> e2 : other.terms.entrySet()) {
                    List<String> merged = new ArrayList<>(e1.getKey().size() + e2.getKey().size());
                    merged.addAll(e1.getKey());
                    merged.addAll(e2.getKey());
                    Collections.sort(merged);
                    int coeff = e1.getValue() * e2.getValue();
                    res.terms.put(merged, res.terms.getOrDefault(merged, 0) + coeff);
                }
            }
            res.removeZeroes();
            return res;
        }

        private void removeZeroes() {
            List<List<String>> toRemove = new ArrayList<>();
            for (Map.Entry<List<String>, Integer> entry : terms.entrySet()) {
                if (entry.getValue() == 0) {
                    toRemove.add(entry.getKey());
                }
            }
            for (List<String> key : toRemove) {
                terms.remove(key);
            }
        }

        public List<String> toList() {
            List<List<String>> keys = new ArrayList<>(terms.keySet());
            keys.sort(new Comparator<List<String>>() {
                @Override
                public int compare(List<String> a, List<String> b) {
                    if (a.size() != b.size()) {
                        return Integer.compare(b.size(), a.size());
                    }
                    int n = Math.min(a.size(), b.size());
                    for (int i = 0; i < n; i++) {
                        int cmp = a.get(i).compareTo(b.get(i));
                        if (cmp != 0) {
                            return cmp;
                        }
                    }
                    return Integer.compare(a.size(), b.size());
                }
            });

            List<String> result = new ArrayList<>();
            for (List<String> key : keys) {
                int coeff = terms.getOrDefault(key, 0);
                if (coeff == 0) {
                    continue;
                }
                if (key.isEmpty()) {
                    result.add(String.valueOf(coeff));
                    continue;
                }
                StringBuilder sb = new StringBuilder();
                sb.append(coeff);
                for (String var : key) {
                    sb.append('*').append(var);
                }
                result.add(sb.toString());
            }
            return result;
        }
    }
}
