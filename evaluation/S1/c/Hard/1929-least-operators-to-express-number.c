// Source: https://leetcode.com/problems/least-operators-to-express-number/   |   Difficulty: Hard
//
// Problem Description:
// Given a single positive integer x, we will write an expression of the form x (op1) x (op2) x (op3) x ... where each operator op1, op2, etc. is either addition, subtraction, multiplication, or division (+, -, *, or /). For example, with x = 3, we might write 3 * 3 / 3 + 3 - 3 which is a value of 3.
//
// When writing such an expression, we adhere to the following conventions:
//
//
// 	The division operator (/) returns rational numbers.
// 	There are no parentheses placed anywhere.
// 	We use the usual order of operations: multiplication and division happen before addition and subtraction.
// 	It is not allowed to use the unary negation operator (-). For example, "x - x" is a valid expression as it only uses subtraction, but "-x + x" is not because it uses negation.
//
//
// We would like to write an expression with the least number of operators such that the expression equals the given target. Return the least number of operators used.
//
// Example:
// Input: x = 3, target = 19
// Output: 5
// Explanation: 3 * 3 + 3 * 3 + 3 / 3.
// The expression contains 5 operations.
//
// Constraints:
// 2 <= x <= 100
// 	1 <= target <= 2 * 108
//
// Helpful references (internal KB):
// - Breadth-first search (graph, queue, array, bfs)
//   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes level by level. It is also suitable for problems requiring traversal of all nodes at a specific distance from a source.
//   • Idea: Breadth-first search systematically explores a graph level by level, ensuring that all nodes at distance k are visited before any nodes at distance k+1. It finds the shortest path in terms of number of edges for unweighted graphs in O(V + E) time.
//   • Invariants: All nodes currently in the queue have been discovered and marked, but their adjacent nodes have not yet been fully explored.; For any node v marked as visited, distTo[v] stores the shortest path length from the source s to v.
//   • Tips: Use a queue to manage nodes to visit.; Mark nodes as visited to prevent cycles and redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect paths.; Not handling disconnected graphs correctly.
// - Arbitrary-Precision Arithmetic (number, gcd)
//   • When to use: When standard integer types cannot hold the magnitude of numbers required for calculations, or when exact results for very large numbers are necessary.
//   • Idea: A technique to represent and operate on integers of arbitrary size, exceeding built-in data type limits, often by storing numbers as sequences of digits or in modular form. Operations are implemented manually, typically with complexity proportional to the number of digits.
//   • Invariants: The stored representation accurately reflects the numerical value.; Each digit or modular component is within its valid range for the chosen base/modulus.
//   • Tips: Choose a suitable base for digit representation (e.g., powers of 10 or 2^k) to balance memory and computation.; Implement basic arithmetic operations (add, subtract, multiply, divide) carefully, handling carries/borrows.
//   • Pitfalls: Inefficient implementation of basic operations can lead to Time Limit Exceeded for large inputs.; Off-by-one errors or incorrect carry/borrow handling are common during manual arithmetic.
// - Minimum stack / Minimum queue (queue, stack, simulation)
//   • When to use: Use when needing to efficiently query the minimum element of a stack or queue in O(1) average time. Also applicable for finding minimums in all fixed-length subarrays using a sliding window.
//   • Idea: This technique augments a stack or queue to support O(1) average time retrieval of its minimum element, typically by storing minimums alongside data or using auxiliary structures. It achieves amortized constant time for all operations.
//   • Invariants: For a minimum stack, the auxiliary minimum stack's top element is always the minimum of all elements currently in the main stack.; For a minimum queue implemented with two stacks, the output stack is only refilled from the input stack when the output stack becomes empty.
//   • Tips: For a minimum stack, use an auxiliary stack to store minimums encountered so far.; Only push to the auxiliary minimum stack if the new element is less than or equal to its current top.
//   • Pitfalls: Forgetting to pop from the auxiliary minimum stack when the main stack's top is removed.; Incorrectly handling the transfer logic between the two stacks for a minimum queue.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int leastOpsExpressTarget(int x, int target) {
    if (target == 0) return 0;
    if (target < x) return target == 1 ? 1 : target * 2 - 1;

    int ops = 0;
    int power = 1;
    while (power < target) {
        power *= x;
        ops++;
    }
    if (power == target) return ops - 1;

    int over = ops + leastOpsExpressTarget(x, power - target);
    int under = (ops - 1) + leastOpsExpressTarget(x, target - power / x);
    return under < over ? under : over;     
}
