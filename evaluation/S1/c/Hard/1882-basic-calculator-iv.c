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
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

// Polynomial representation using a map of term to coefficient
typedef struct {
    char* term;
    long long coeff;
} PolyTerm;

typedef struct {
    PolyTerm* terms;
    int size;
    int capacity;
} Polynomial;

Polynomial* createPolynomial() {
    Polynomial* p = (Polynomial*)malloc(sizeof(Polynomial));
    p->capacity = 10;
    p->terms = (PolyTerm*)malloc(sizeof(PolyTerm) * p->capacity);
    p->size = 0;
    return p;
}

void addTerm(Polynomial* p, const char* term, long long coeff) {
    if (coeff == 0) return;
    
    for (int i = 0; i < p->size; i++) {
        if (strcmp(p->terms[i].term, term) == 0) {
            p->terms[i].coeff += coeff;
            return;
        }
    }
    
    if (p->size >= p->capacity) {
        p->capacity *= 2;
        p->terms = (PolyTerm*)realloc(p->terms, sizeof(PolyTerm) * p->capacity);
    }
    
    p->terms[p->size].term = (char*)malloc(strlen(term) + 1);
    strcpy(p->terms[p->size].term, term);
    p->terms[p->size].coeff = coeff;
    p->size++;
}

int compareTerms(const void* a, const void* b) {
    PolyTerm* ta = (PolyTerm*)a;
    PolyTerm* tb = (PolyTerm*)b;
    
    // Count '*' to get degree
    int degA = 0, degB = 0;
    for (int i = 0; ta->term[i]; i++) if (ta->term[i] == '*') degA++;
    for (int i = 0; tb->term[i]; i++) if (tb->term[i] == '*') degB++;
    
    if (degA != degB) return degB - degA; // Higher degree first
    return strcmp(ta->term, tb->term); // Lexicographic order
}

Polynomial* parseExpression(char* expr, char** evalvars, int evalvarsSize, int* evalints);

Polynomial* parseMultiplication(char* expr, char** evalvars, int evalvarsSize, int* evalints);

Polynomial* parseAddition(char* expr, char** evalvars, int evalvarsSize, int* evalints) {
    char* copy = (char*)malloc(strlen(expr) + 1);
    strcpy(copy, expr);
    
    Polynomial* result = createPolynomial();
    char* token = strtok(copy, " ");
    Polynomial* current = NULL;
    char op = '+';
    
    while (token != NULL) {
        if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0) {
            op = token[0];
        } else {
            Polynomial* term = parseMultiplication(token, evalvars, evalvarsSize, evalints);
            if (current == NULL) {
                current = term;
            } else {
                if (op == '+') {
                    for (int i = 0; i < term->size; i++) {
                        addTerm(current, term->terms[i].term, term->terms[i].coeff);
                    }
                } else {
                    for (int i = 0; i < term->size; i++) {
                        addTerm(current, term->terms[i].term, -term->terms[i].coeff);
                    }
                }
                free(term->terms);
                free(term);
            }
        }
        token = strtok(NULL, " ");
    }
    
    if (current == NULL) {
        addTerm(result, "1", 0);
    } else {
        for (int i = 0; i < current->size; i++) {
            addTerm(result, current->terms[i].term, current->terms[i].coeff);
        }
        free(current->terms);
        free(current);
    }
    
    free(copy);
    return result;
}

Polynomial* multiplyPolynomials(Polynomial* a, Polynomial* b) {
    Polynomial* result = createPolynomial();
    
    for (int i = 0; i < a->size; i++) {
        for (int j = 0; j < b->size; j++) {
            long long newCoeff = a->terms[i].coeff * b->terms[j].coeff;
            
            char* termA = a->terms[i].term;
            char* termB = b->terms[j].term;
            
            char combined[512] = "";
            if (strcmp(termA, "1") == 0) {
                strcpy(combined, termB);
            } else if (strcmp(termB, "1") == 0) {
                strcpy(combined, termA);
            } else {
                char* vars[100];
                int varCount = 0;
                
                char* copyA = (char*)malloc(strlen(termA) + 1);
                strcpy(copyA, termA);
                char* p = strtok(copyA, "*");
                while (p != NULL) {
                    vars[varCount++] = (char*)malloc(strlen(p) + 1);
                    strcpy(vars[varCount - 1], p);
                    p = strtok(NULL, "*");
                }
                free(copyA);
                
                char* copyB = (char*)malloc(strlen(termB) + 1);
                strcpy(copyB, termB);
                p = strtok(copyB, "*");
                while (p != NULL) {
                    vars[varCount++] = (char*)malloc(strlen(p) + 1);
                    strcpy(vars[varCount - 1], p);
                    p = strtok(NULL, "*");
                }
                free(copyB);
                
                qsort(vars, varCount, sizeof(char*), (int(*)(const void*, const void*))strcmp);
                
                strcpy(combined, vars[0]);
                for (int k = 1; k < varCount; k++) {
                    strcat(combined, "*");
                    strcat(combined, vars[k]);
                    free(vars[k]);
                }
                free(vars[0]);
            }
            
            addTerm(result, combined, newCoeff);
        }
    }
    
    return result;
}

Polynomial* parseMultiplication(char* expr, char** evalvars, int evalvarsSize, int* evalints) {
    Polynomial* result = createPolynomial();
    
    // Check if it's a number
    if (isdigit(expr[0])) {
        long long num = 0;
        for (int i = 0; isdigit(expr[i]); i++) {
            num = num * 10 + (expr[i] - '0');
        }
        addTerm(result, "1", num);
        return result;
    }
    
    // Check if it's a variable
    if (isalpha(expr[0])) {
        for (int i = 0; i < evalvarsSize; i++) {
            if (strcmp(expr, evalvars[i]) == 0) {
                addTerm(result, "1", evalints[i]);
                return result;
            }
        }
        addTerm(result, expr, 1);
        return result;
    }
    
    // Check if it's a parenthesized expression
    if (expr[0] == '(') {
        char* inner = (char*)malloc(strlen(expr));
        strcpy(inner, expr + 1);
        inner[strlen(inner) - 1] = '\0';
        Polynomial* p = parseExpression(inner, evalvars, evalvarsSize, evalints);
        free(inner);
        return p;
    }
    
    return result;
}

Polynomial* parseExpression(char* expr, char** evalvars, int evalvarsSize, int* evalints) {
    return parseAddition(expr, evalvars, evalvarsSize, evalints);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** basicCalculatorIV(char* expression, char** evalvars, int evalvarsSize, int* evalints, int evalintsSize, int* returnSize) {
    Polynomial* poly = parseExpression(expression, evalvars, evalvarsSize, evalints);
    
    // Filter out zero coefficients and sort
    Polynomial* nonZero = createPolynomial();
    for (int i = 0; i < poly->size; i++) {
        if (poly->terms[i].coeff != 0) {
            addTerm(nonZero, poly->terms[i].term, poly->terms[i].coeff);
        }
    }
    
    qsort(nonZero->terms, nonZero->size, sizeof(PolyTerm), compareTerms);
    
    char** result = (char**)malloc(sizeof(char*) * (nonZero->size + 1));
    *returnSize = nonZero->size;
    
    for (int i = 0; i < nonZero->size; i++) {
        int len = 50 + strlen(nonZero->terms[i].term);
        result[i] = (char*)malloc(len);
        sprintf(result[i], "%lld*%s", nonZero->terms[i].coeff, nonZero->terms[i].term);
    }
    
    for (int i = 0; i < poly->size; i++) {
        free(poly->terms[i].term);
    }
    free(poly->terms);
    free(poly);
    
    for (int i = 0; i < nonZero->size; i++) {
        free(nonZero->terms[i].term);
    }
    free(nonZero->terms);
    free(nonZero);
    
    return result;
}
