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

class Solution {
public:
    vector<string> basicCalculatorIV(string expression, vector<string>& evalvars, vector<int>& evalints) {
        // Create evaluation map
        unordered_map<string, int> evalMap;
        for (int i = 0; i < evalvars.size(); i++) {
            evalMap[evalvars[i]] = evalints[i];
        }
        
        // Parse and evaluate the expression
        Poly result = parse(expression, evalMap);
        return result.toList();
    }
    
private:
    // Polynomial class to represent terms with coefficients
    class Poly {
    public:
        map<vector<string>, int> terms; // maps sorted variable list to coefficient
        
        Poly() {}
        
        Poly(int coef) {
            if (coef != 0) {
                terms[vector<string>()] = coef;
            }
        }
        
        Poly(string var) {
            terms[vector<string>{var}] = 1;
        }
        
        Poly operator+(const Poly& other) const {
            Poly result = *this;
            for (auto& [vars, coef] : other.terms) {
                result.terms[vars] += coef;
                if (result.terms[vars] == 0) {
                    result.terms.erase(vars);
                }
            }
            return result;
        }
        
        Poly operator-(const Poly& other) const {
            Poly result = *this;
            for (auto& [vars, coef] : other.terms) {
                result.terms[vars] -= coef;
                if (result.terms[vars] == 0) {
                    result.terms.erase(vars);
                }
            }
            return result;
        }
        
        Poly operator*(const Poly& other) const {
            Poly result;
            for (auto& [vars1, coef1] : this->terms) {
                for (auto& [vars2, coef2] : other.terms) {
                    vector<string> combined = vars1;
                    combined.insert(combined.end(), vars2.begin(), vars2.end());
                    sort(combined.begin(), combined.end());
                    result.terms[combined] += coef1 * coef2;
                    if (result.terms[combined] == 0) {
                        result.terms.erase(combined);
                    }
                }
            }
            return result;
        }
        
        vector<string> toList() const {
            vector<pair<vector<string>, int>> sorted_terms;
            for (auto& [vars, coef] : terms) {
                sorted_terms.push_back({vars, coef});
            }
            
            // Sort by degree (descending), then lexicographically
            sort(sorted_terms.begin(), sorted_terms.end(), 
                [](const auto& a, const auto& b) {
                    if (a.first.size() != b.first.size()) {
                        return a.first.size() > b.first.size(); // Higher degree first
                    }
                    return a.first < b.first; // Lexicographic order
                });
            
            vector<string> result;
            for (auto& [vars, coef] : sorted_terms) {
                string term = to_string(coef);
                for (const string& var : vars) {
                    term += "*" + var;
                }
                result.push_back(term);
            }
            return result;
        }
    };
    
    Poly parse(const string& expr, unordered_map<string, int>& evalMap) {
        vector<string> tokens = tokenize(expr);
        int pos = 0;
        return parseExpression(tokens, pos, evalMap);
    }
    
    vector<string> tokenize(const string& expr) {
        vector<string> tokens;
        stringstream ss(expr);
        string token;
        while (ss >> token) {
            tokens.push_back(token);
        }
        return tokens;
    }
    
    Poly parseExpression(vector<string>& tokens, int& pos, unordered_map<string, int>& evalMap) {
        Poly result = parseTerm(tokens, pos, evalMap);
        
        while (pos < tokens.size() && (tokens[pos] == "+" || tokens[pos] == "-")) {
            string op = tokens[pos++];
            Poly term = parseTerm(tokens, pos, evalMap);
            if (op == "+") {
                result = result + term;
            } else {
                result = result - term;
            }
        }
        
        return result;
    }
    
    Poly parseTerm(vector<string>& tokens, int& pos, unordered_map<string, int>& evalMap) {
        Poly result = parseFactor(tokens, pos, evalMap);
        
        while (pos < tokens.size() && tokens[pos] == "*") {
            pos++; // skip '*'
            Poly factor = parseFactor(tokens, pos, evalMap);
            result = result * factor;
        }
        
        return result;
    }
    
    Poly parseFactor(vector<string>& tokens, int& pos, unordered_map<string, int>& evalMap) {
        string token = tokens[pos++];
        
        if (token == "(") {
            Poly result = parseExpression(tokens, pos, evalMap);
            pos++; // skip ')'
            return result;
        } else if (isdigit(token[0])) {
            return Poly(stoi(token));
        } else {
            // It's a variable
            if (evalMap.count(token)) {
                return Poly(evalMap[token]);
            } else {
                return Poly(token);
            }
        }
    }
};