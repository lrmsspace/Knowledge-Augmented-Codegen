// Source: https://leetcode.com/problems/number-of-steps-to-reduce-a-number-to-zero/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer num, return the number of steps to reduce it to zero.
//
// In one step, if the current number is even, you have to divide it by 2, otherwise, you have to subtract 1 from it.
//
// Example:
// Input: num = 14
// Output: 6
// Explanation: 
// Step 1) 14 is even; divide by 2 and obtain 7. 
// Step 2) 7 is odd; subtract 1 and obtain 6.
// Step 3) 6 is even; divide by 2 and obtain 3. 
// Step 4) 3 is odd; subtract 1 and obtain 2. 
// Step 5) 2 is even; divide by 2 and obtain 1. 
// Step 6) 1 is odd; subtract 1 and obtain 0.
//
// Constraints:
// 0 <= num <= 106
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
// - Binary Exponentiation by Factoring (number, counting, mod-exp)
//   • When to use: Use when performing modular exponentiation for an odd base modulo a power of two, especially when dealing with specific logarithmic-like functions or inverses in this modulus.
//   • Idea: This technique computes modular exponentiation for an odd base modulo a power of two by factoring the exponent or its inverse into a product of terms like (2^n+1). It leverages bit manipulation to efficiently find this factorization, allowing for O(d) or O(d log d) complexity where d is the exponent of the modulus.
//   • Invariants: During the iterative process to find $x^{-1} \pmod{2^d}$, the current value of $x$ is always odd.; After processing bit $n$, the $n$-th bit of the current $x$ (for $x^{-1}$ calculation) is zero, and lower bits are unchanged.
//   • Tips: Precompute $4L(2^n+1)$ values for efficiency.; Leverage bitwise operations for multiplying by $2^n+1$ (e.g., x = x + (x << n)).
//   • Pitfalls: This method is specific to odd bases and moduli of the form $2^d$; it's not a general modular exponentiation.; Careful handling of negative results from $4L(x^{-1})$ when working with modular arithmetic.
// - 0-1 BFS (graph, array, dijkstra, bfs)
//   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently determines minimum costs without a full priority queue.
//   • Idea: A specialized Breadth-First Search variant that finds shortest paths in graphs with only 0 or 1 edge weights. It uses a deque to process 0-weight edges before 1-weight edges, achieving O(V+E) time complexity.
//   • Invariants: All nodes currently in the deque have a distance value of either `k` or `k+1` for some integer `k`.; Nodes pushed to the front of the deque always have a distance equal to the current node's distance.
//   • Tips: Utilize a deque to maintain the order of processing nodes.; Add nodes reached via 0-weight edges to the front of the deque.
//   • Pitfalls: Incorrectly using a standard queue instead of a deque.; Failing to initialize distances to infinity for all nodes except the source.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int numberOfSteps(int num) {
    int steps = 0;
    while (num > 0) {
        if (num % 2 == 0) {
            num /= 2; // If even, divide by 2
        } else {
            num -= 1; // If odd, subtract 1
        }
        steps++; // Increment the step count
    }
    return steps;       
}
