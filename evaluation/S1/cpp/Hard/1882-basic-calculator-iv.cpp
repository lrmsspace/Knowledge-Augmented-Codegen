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
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
private:
    // 多项式项，用map存储变量组合到系数的映射
    typedef map<vector<string>, int> Poly;
    
    // 合并多项式
    Poly merge(Poly p1, Poly p2, char op) {
        if (op == '+') {
            for (auto& [vars, coef] : p2) {
                p1[vars] += coef;
            }
        } else if (op == '-') {
            for (auto& [vars, coef] : p2) {
                p1[vars] -= coef;
            }
        } else if (op == '*') {
            Poly res;
            for (auto& [v1, c1] : p1) {
                for (auto& [v2, c2] : p2) {
                    vector<string> vars = v1;
                    vars.insert(vars.end(), v2.begin(), v2.end());
                    sort(vars.begin(), vars.end());
                    res[vars] += c1 * c2;
                }
            }
            return res;
        }
        return p1;
    }
    
    // 解析表达式
    Poly parse(const string& s, int& i, unordered_map<string, int>& evalMap) {
        vector<Poly> polys;
        vector<char> ops;
        
        while (i < s.size()) {
            if (s[i] == '(') {
                i++; // skip '('
                polys.push_back(parse(s, i, evalMap));
                i++; // skip ')'
            } else if (isalnum(s[i])) {
                string token;
                while (i < s.size() && isalnum(s[i])) {
                    token += s[i++];
                }
                
                Poly poly;
                if (isdigit(token[0])) {
                    // 数字
                    poly[{}] = stoi(token);
                } else {
                    // 变量
                    if (evalMap.count(token)) {
                        poly[{}] = evalMap[token];
                    } else {
                        poly[{token}] = 1;
                    }
                }
                polys.push_back(poly);
            } else if (s[i] == '+' || s[i] == '-' || s[i] == '*') {
                ops.push_back(s[i]);
                i++;
            } else if (s[i] == ' ') {
                i++;
            } else if (s[i] == ')') {
                break;
            } else {
                i++;
            }
        }
        
        // 先处理乘法
        vector<Poly> newPolys;
        vector<char> newOps;
        
        newPolys.push_back(polys[0]);
        for (int j = 0; j < ops.size(); j++) {
            if (ops[j] == '*') {
                newPolys.back() = merge(newPolys.back(), polys[j + 1], '*');
            } else {
                newPolys.push_back(polys[j + 1]);
                newOps.push_back(ops[j]);
            }
        }
        
        // 再处理加减
        Poly result = newPolys[0];
        for (int j = 0; j < newOps.size(); j++) {
            result = merge(result, newPolys[j + 1], newOps[j]);
        }
        
        return result;
    }
    
public:
    vector<string> basicCalculatorIV(string expression, vector<string>& evalvars, vector<int>& evalints) {
        // 创建变量到值的映射
        unordered_map<string, int> evalMap;
        for (int i = 0; i < evalvars.size(); i++) {
            evalMap[evalvars[i]] = evalints[i];
        }
        
        // 解析表达式
        int idx = 0;
        Poly poly = parse(expression, idx, evalMap);
        
        // 移除系数为0的项
        vector<pair<vector<string>, int>> terms;
        for (auto& [vars, coef] : poly) {
            if (coef != 0) {
                terms.push_back({vars, coef});
            }
        }
        
        // 排序：先按度数降序，再按字典序
        sort(terms.begin(), terms.end(), [](const auto& a, const auto& b) {
            if (a.first.size() != b.first.size()) {
                return a.first.size() > b.first.size();
            }
            return a.first < b.first;
        });
        
        // 格式化输出
        vector<string> result;
        for (auto& [vars, coef] : terms) {
            string term = to_string(coef);
            for (const string& var : vars) {
                term += "*" + var;
            }
            result.push_back(term);
        }
        
        return result;
    }
};
