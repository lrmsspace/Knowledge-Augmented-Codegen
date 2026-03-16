// Source: https://leetcode.com/problems/parse-lisp-expression/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string expression representing a Lisp-like expression to return the integer value of.
//
// The syntax for these expressions is given as follows.
//
//
// 	An expression is either an integer, let expression, add expression, mult expression, or an assigned variable. Expressions always evaluate to a single integer.
// 	(An integer could be positive or negative.)
// 	A let expression takes the form "(let v1 e1 v2 e2 ... vn en expr)", where let is always the string "let", then there are one or more pairs of alternating variables and expressions, meaning that the first variable v1 is assigned the value of the expression e1, the second variable v2 is assigned the value of the expression e2, and so on sequentially; and then the value of this let expression is the value of the expression expr.
// 	An add expression takes the form "(add e1 e2)" where add is always the string "add", there are always two expressions e1, e2 and the result is the addition of the evaluation of e1 and the evaluation of e2.
// 	A mult expression takes the form "(mult e1 e2)" where mult is always the string "mult", there are always two expressions e1, e2 and the result is the multiplication of the evaluation of e1 and the evaluation of e2.
// 	For this question, we will use a smaller subset of variable names. A variable starts with a lowercase letter, then zero or more lowercase letters or digits. Additionally, for your convenience, the names "add", "let", and "mult" are protected and will never be used as variable names.
// 	Finally, there is the concept of scope. When an expression of a variable name is evaluated, within the context of that evaluation, the innermost scope (in terms of parentheses) is checked first for the value of that variable, and then outer scopes are checked sequentially. It is guaranteed that every expression is legal. Please see the examples for more details on the scope.
//
// Example:
// Input: expression = "(let x 2 (mult x (let x 3 y 4 (add x y))))"
// Output: 14
// Explanation: In the expression (add x y), when checking for the value of the variable x,
// we check from the innermost scope to the outermost in the context of the variable we are trying to evaluate.
// Since x = 3 is found first, the value of x is 3.
//
// Constraints:
// 1 <= expression.length <= 2000
// 	There are no leading or trailing spaces in expression.
// 	All tokens are separated by a single space in expression.
// 	The answer and all intermediate calculations of that answer are guaranteed to fit in a 32-bit integer.
// 	The expression is guaranteed to be legal and evaluate to an integer.
//
// Helpful references (internal KB):
// - Expression parsing (stack, simulation)
//   • When to use: Use this algorithm to evaluate an arithmetic expression given in infix notation, respecting operator precedence and parentheses. It is suitable for expressions with binary, left-associative operators.
//   • Idea: This algorithm evaluates an infix arithmetic expression using two stacks: one for operands and one for operators. It processes the expression from left to right, applying operator precedence and associativity rules to achieve an O(N) time complexity.
//   • Invariants: The operand stack always contains valid numerical values or intermediate results.; The operator stack maintains operators such that operators with higher or equal precedence are processed before lower precedence ones.
//   • Tips: Clearly define operator precedence and associativity rules for all operators.; Use a separate stack for operands (numbers) and operators (including parentheses).
//   • Pitfalls: Misinterpreting operator precedence or associativity rules can lead to incorrect results.; Failure to handle mismatched or unbalanced parentheses can cause runtime errors.
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Search for connected components in a graph (stack, graph, dfs, recursion)
//   • When to use: Use when the goal is to identify distinct groups of interconnected nodes within a graph, or to find all nodes reachable from a specific starting point.
//   • Idea: Depth-First Search (DFS) explores a graph by traversing as far as possible along each branch before backtracking. It efficiently finds connected components by visiting all reachable nodes from an unvisited starting point, typically with O(V+E) time complexity.
//   • Invariants: All nodes in the current DFS path from the start node to the current node are on the recursion stack.; Any node marked as visited will not be re-processed by the current DFS call.
//   • Tips: Maintain a 'visited' status for each node to prevent cycles and redundant work.; Iterate through all nodes and start DFS if a node is unvisited to find all components.
//   • Pitfalls: Excessive recursion depth can lead to stack overflow errors for large graphs.; Forgetting to mark nodes as visited results in infinite loops in cyclic graphs.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

// Helper structure for variable scope management
typedef struct VarNode {
    char* name;
    int value;
    struct VarNode* next;
} VarNode;

// Helper function to check if a string is a number
int isNumber(char* s) {
    if (*s == '-' || *s == '+') s++;
    if (!*s) return 0;
    while (*s) {
        if (*s < '0' || *s > '9') return 0;
        s++;
    }
    return 1;
}

// Helper function to convert string to integer
int toInt(char* s) {
    int sign = 1, result = 0;
    if (*s == '-') {
        sign = -1;
        s++;
    } else if (*s == '+') {
        s++;
    }
    while (*s) {
        result = result * 10 + (*s - '0');
        s++;
    }
    return sign * result;
}

// Helper function to look up variable in scope chain
int lookupVar(VarNode* scope, char* name) {
    while (scope) {
        if (strcmp(scope->name, name) == 0) {
            return scope->value;
        }
        scope = scope->next;
    }
    return 0; // Should never reach here if expression is valid
}

// Helper function to parse next token
char* parseToken(char* expr, int* pos, char* token) {
    while (expr[*pos] == ' ') (*pos)++;
    
    int start = *pos;
    if (expr[*pos] == '(') {
        token[0] = '(';
        token[1] = '\0';
        (*pos)++;
        return token;
    }
    if (expr[*pos] == ')') {
        token[0] = ')';
        token[1] = '\0';
        (*pos)++;
        return token;
    }
    
    int i = 0;
    while (expr[*pos] && expr[*pos] != ' ' && expr[*pos] != '(' && expr[*pos] != ')') {
        token[i++] = expr[*pos];
        (*pos)++;
    }
    token[i] = '\0';
    return token;
}

// Main evaluation function with scope
int eval(char* expr, int* pos, VarNode* scope);

int eval(char* expr, int* pos, VarNode* scope) {
    char token[100];
    parseToken(expr, pos, token);
    
    // If it's a number, return it
    if (isNumber(token)) {
        return toInt(token);
    }
    
    // If it's a variable, look it up
    if (token[0] != '(') {
        return lookupVar(scope, token);
    }
    
    // It's an expression starting with '('
    parseToken(expr, pos, token);
    
    if (strcmp(token, "add") == 0) {
        int val1 = eval(expr, pos, scope);
        int val2 = eval(expr, pos, scope);
        parseToken(expr, pos, token); // consume ')'
        return val1 + val2;
    }
    
    if (strcmp(token, "mult") == 0) {
        int val1 = eval(expr, pos, scope);
        int val2 = eval(expr, pos, scope);
        parseToken(expr, pos, token); // consume ')'
        return val1 * val2;
    }
    
    if (strcmp(token, "let") == 0) {
        // Create new scope by copying old scope variables
        VarNode* newScope = scope;
        
        while (1) {
            // Peek ahead to see if we're at the final expression
            int savedPos = *pos;
            char nextToken[100];
            parseToken(expr, &savedPos, nextToken);
            
            // Check if it's a closing paren or an expression
            if (nextToken[0] == ')') {
                parseToken(expr, pos, token); // consume ')'
                return 0; // Empty let expression
            }
            
            // Check if next is the final expression (by looking further)
            int peekPos = savedPos;
            char peekToken[100];
            parseToken(expr, &peekPos, peekToken);
            
            if (peekToken[0] == ')') {
                // nextToken is the final expression
                int result = eval(expr, pos, newScope);
                parseToken(expr, pos, token); // consume ')'
                return result;
            }
            
            // We have a variable assignment: var expr
            parseToken(expr, pos, token); // get variable name
            char* varName = malloc(strlen(token) + 1);
            strcpy(varName, token);
            
            int varValue = eval(expr, pos, newScope);
            
            // Add to scope
            VarNode* newVar = malloc(sizeof(VarNode));
            newVar->name = varName;
            newVar->value = varValue;
            newVar->next = newScope;
            newScope = newVar;
        }
    }
    
    return 0;
}

int evaluate(char* expression) {
    int pos = 0;
    return eval(expression, &pos, NULL);
}
