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
//   • When to use: When you need to model and solve combinatorial counting problems using algebraic methods, especially when dealing with recurrence relations or products of independent choices. It's also useful for analyzing properties of sequences.
//   • Idea: This involves performing algebraic operations like addition, multiplication, and composition on polynomials or formal power series, represented by coefficients. These operations model combinatorial structures and solve recurrence relations, typically with complexities from O(N) to O(N log N).
//   • Invariants: The array `coefficients[i]` stores the coefficient of `x^i` for the current polynomial.; For any intermediate product `C(x) = A(x) * B(x)`, the coefficient `C[k]` correctly accumulates `A[i] * B[j]` for all `i+j=k`.
//   • Tips: Represent polynomials as arrays of coefficients; Understand the combinatorial meaning of operations (e.g., product for independent choices)
//   • Pitfalls: Confusing ordinary and exponential generating functions; Incorrectly applying convolution for non-independent events
// - Operations on polynomials and series (array, recursion)
//   • When to use: When problems involve manipulating algebraic polynomials or power series, especially when their properties or coefficients are defined recursively. It is also useful for problems involving generating functions to represent sequences.
//   • Idea: This card describes recursive approaches to perform common operations on polynomials and power series, often represented by their coefficients. The complexity varies depending on the specific operation, but many are O(N^2) or O(N log N) with optimized techniques.
//   • Invariants: For a polynomial represented by P[0...N-1], P[i] always stores the coefficient of x^i.; When performing an operation recursively, the result of subproblems correctly represents the corresponding sub-polynomial or sub-series.
//   • Tips: Represent polynomials as arrays of coefficients.; Base cases for recursion are crucial (e.g., constant polynomial, empty series).
//   • Pitfalls: Incorrectly handling polynomial degrees or series truncation.; Off-by-one errors in coefficient indexing.
// - Operations on polynomials and series (array, recursion)
//   • When to use: When you need to compute the product of two polynomials or formal power series, often represented by their coefficient arrays. This is useful for combining algebraic expressions or solving recurrence relations.
//   • Idea: This involves computing the coefficients of the product polynomial by convolving the coefficients of the input polynomials. Algorithms like Karatsuba's use a divide-and-conquer recursive approach to achieve better than naive quadratic time complexity.
//   • Invariants: Each recursive call correctly computes the product of its two input sub-polynomials; The base case for recursion (e.g., constant polynomials) is handled correctly
//   • Tips: Represent polynomials as arrays of coefficients; Pad shorter polynomials with zeros to match degrees
//   • Pitfalls: Forgetting to handle zero coefficients or different polynomial degrees; Naive O(N^2) multiplication can be too slow for large inputs
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** basicCalculatorIV(char* expression, char** evalvars, int evalvarsSize, int* evalints, int evalintsSize, int* returnSize) {
            
    // Implement a recursive function to parse the expression and evaluate it according to the order of operations
    // Use a hash map to substitute variables with their values from evalvars and evalints
    // Use a data structure (e.g., struct) to represent terms in the expression, including their coefficient and variable components
    // Perform simplification by combining like terms and sorting them according to the specified format
    *returnSize = 0; // Placeholder return size
    return NULL; // Placeholder return value
}
