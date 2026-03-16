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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

typedef struct {
    long long coeff;
    char vars[100];  // space-separated sorted variable string
} Term;

typedef struct {
    Term* terms;
    int size;
} Polynomial;

typedef struct {
    char* key;
    long long value;
} HashMap;

int getEvalValue(char** evalvars, int* evalints, int evalvarsSize, const char* var) {
    for (int i = 0; i < evalvarsSize; i++) {
        if (strcmp(evalvars[i], var) == 0) {
            return evalints[i];
        }
    }
    return -999999;  // not found
}

void insertTerm(Polynomial* poly, long long coeff, const char* vars) {
    if (coeff == 0) return;
    
    // Find if term already exists
    for (int i = 0; i < poly->size; i++) {
        if (strcmp(poly->terms[i].vars, vars) == 0) {
            poly->terms[i].coeff += coeff;
            return;
        }
    }
    
    // Add new term
    poly->terms[poly->size].coeff = coeff;
    strcpy(poly->terms[poly->size].vars, vars);
    poly->size++;
}

int compareTerms(const void* a, const void* b) {
    Term* t1 = (Term*)a;
    Term* t2 = (Term*)b;
    
    // Count degree (number of variables)
    int deg1 = 0, deg2 = 0;
    for (int i = 0; t1->vars[i]; i++) if (t1->vars[i] != ' ') deg1++;
    for (int i = 0; t2->vars[i]; i++) if (t2->vars[i] != ' ') deg2++;
    
    if (deg1 != deg2) return deg2 - deg1;  // higher degree first
    
    // Same degree, sort lexicographically by variables
    int cmp = strcmp(t1->vars, t2->vars);
    if (cmp != 0) return cmp;
    
    return 0;
}

int idx = 0;

Polynomial* parseExpr(char* expression, char** evalvars, int evalvarsSize, int* evalints);
Polynomial* parseTerm(char* expression, char** evalvars, int evalvarsSize, int* evalints);
Polynomial* parseFactor(char* expression, char** evalvars, int evalvarsSize, int* evalints);

Polynomial* multiply(Polynomial* p1, Polynomial* p2) {
    Polynomial* result = (Polynomial*)malloc(sizeof(Polynomial));
    result->terms = (Term*)malloc(sizeof(Term) * 10000);
    result->size = 0;
    
    for (int i = 0; i < p1->size; i++) {
        for (int j = 0; j < p2->size; j++) {
            long long newCoeff = p1->terms[i].coeff * p2->terms[j].coeff;
            
            char newVars[100] = {0};
            char* vars1 = p1->terms[i].vars;
            char* vars2 = p2->terms[j].vars;
            
            // Merge variables sorted
            char allVars[100] = {0};
            int k = 0;
            
            while (*vars1 && *vars2) {
                if (*vars1 < *vars2) {
                    allVars[k++] = *vars1++;
                } else {
                    allVars[k++] = *vars2++;
                }
            }
            while (*vars1) allVars[k++] = *vars1++;
            while (*vars2) allVars[k++] = *vars2++;
            
            insertTerm(result, newCoeff, allVars);
        }
    }
    
    return result;
}

Polynomial* add(Polynomial* p1, Polynomial* p2) {
    Polynomial* result = (Polynomial*)malloc(sizeof(Polynomial));
    result->terms = (Term*)malloc(sizeof(Term) * 10000);
    result->size = 0;
    
    for (int i = 0; i < p1->size; i++) {
        insertTerm(result, p1->terms[i].coeff, p1->terms[i].vars);
    }
    for (int i = 0; i < p2->size; i++) {
        insertTerm(result, p2->terms[i].coeff, p2->terms[i].vars);
    }
    
    return result;
}

Polynomial* subtract(Polynomial* p1, Polynomial* p2) {
    Polynomial* result = (Polynomial*)malloc(sizeof(Polynomial));
    result->terms = (Term*)malloc(sizeof(Term) * 10000);
    result->size = 0;
    
    for (int i = 0; i < p1->size; i++) {
        insertTerm(result, p1->terms[i].coeff, p1->terms[i].vars);
    }
    for (int i = 0; i < p2->size; i++) {
        insertTerm(result, -p2->terms[i].coeff, p2->terms[i].vars);
    }
    
    return result;
}

Polynomial* parseFactor(char* expression, char** evalvars, int evalvarsSize, int* evalints) {
    Polynomial* result = (Polynomial*)malloc(sizeof(Polynomial));
    result->terms = (Term*)malloc(sizeof(Term) * 10000);
    result->size = 0;
    
    // Skip spaces
    while (expression[idx] == ' ') idx++;
    
    if (expression[idx] == '(') {
        idx++;  // skip '('
        result = parseExpr(expression, evalvars, evalvarsSize, evalints);
        while (expression[idx] == ' ') idx++;
        idx++;  // skip ')'
    } else if (isalpha(expression[idx])) {
        // Variable
        char var[21] = {0};
        int i = 0;
        while (isalpha(expression[idx])) {
            var[i++] = expression[idx++];
        }
        var[i] = 0;
        
        int val = getEvalValue(evalvars, evalints, evalvarsSize, var);
        if (val != -999999) {
            insertTerm(result, val, "");
        } else {
            insertTerm(result, 1, var);
        }
    } else {
        // Number
        long long num = 0;
        while (isdigit(expression[idx])) {
            num = num * 10 + (expression[idx++] - '0');
        }
        insertTerm(result, num, "");
    }
    
    while (expression[idx] == ' ') idx++;
    return result;
}

Polynomial* parseTerm(char* expression, char** evalvars, int evalvarsSize, int* evalints) {
    Polynomial* result = parseFactor(expression, evalvars, evalvarsSize, evalints);
    
    while (expression[idx] == '*') {
        idx++;  // skip '*'
        Polynomial* right = parseFactor(expression, evalvars, evalvarsSize, evalints);
        Polynomial* newResult = multiply(result, right);
        free(result->terms);
        free(result);
        result = newResult;
    }
    
    return result;
}

Polynomial* parseExpr(char* expression, char** evalvars, int evalvarsSize, int* evalints) {
    Polynomial* result = parseTerm(expression, evalvars, evalvarsSize, evalints);
    
    while (expression[idx] && expression[idx] != ')') {
        while (expression[idx] == ' ') idx++;
        
        if (expression[idx] == '+') {
            idx++;  // skip '+'
            Polynomial* right = parseTerm(expression, evalvars, evalvarsSize, evalints);
            Polynomial* newResult = add(result, right);
            free(result->terms);
            free(result);
            result = newResult;
        } else if (expression[idx] == '-') {
            idx++;  // skip '-'
            Polynomial* right = parseTerm(expression, evalvars, evalvarsSize, evalints);
            Polynomial* newResult = subtract(result, right);
            free(result->terms);
            free(result);
            result = newResult;
        } else {
            break;
        }
    }
    
    return result;
}

char** basicCalculatorIV(char* expression, char** evalvars, int evalvarsSize, int* evalints, int evalintsSize, int* returnSize) {
    idx = 0;
    Polynomial* poly = parseExpr(expression, evalvars, evalvarsSize, evalints);
    
    // Remove zero coefficients
    Polynomial* cleanPoly = (Polynomial*)malloc(sizeof(Polynomial));
    cleanPoly->terms = (Term*)malloc(sizeof(Term) * 10000);
    cleanPoly->size = 0;
    
    for (int i = 0; i < poly->size; i++) {
        if (poly->terms[i].coeff != 0) {
            cleanPoly->terms[cleanPoly->size] = poly->terms[i];
            cleanPoly->size++;
        }
    }
    
    // Sort terms
    qsort(cleanPoly->terms, cleanPoly->size, sizeof(Term), compareTerms);
    
    // Format output
    char** result = (char**)malloc(sizeof(char*) * (cleanPoly->size + 1));
    
    for (int i = 0; i < cleanPoly->size; i++) {
        char buffer[200] = {0};
        
        sprintf(buffer, "%lld", cleanPoly->terms[i].coeff);
        
        if (cleanPoly->terms[i].vars[0]) {
            strcat(buffer, "*");
            strcat(buffer, cleanPoly->terms[i].vars);
        }
        
        result[i] = (char*)malloc(strlen(buffer) + 1);
        strcpy(result[i], buffer);
    }
    
    *returnSize = cleanPoly->size;
    
    free(poly->terms);
    free(poly);
    free(cleanPoly->terms);
    free(cleanPoly);
    
    return result;
}