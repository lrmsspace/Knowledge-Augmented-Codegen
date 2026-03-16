// Source: https://leetcode.com/problems/calculate-score-after-performing-instructions/   |   Difficulty: Medium
//
// Problem Description:
// You are given two arrays, instructions and values, both of size n.
//
// You need to simulate a process based on the following rules:
//
//
// 	You start at the first instruction at index i = 0 with an initial score of 0.
// 	If instructions[i] is "add":
// 	
// 		Add values[i] to your score.
// 		Move to the next instruction (i + 1).
// 	
// 	
// 	If instructions[i] is "jump":
// 	
// 		Move to the instruction at index (i + values[i]) without modifying your score.
// 	
// 	
//
//
// The process ends when you either:
//
//
// 	Go out of bounds (i.e., i < 0 or i >= n), or
// 	Attempt to revisit an instruction that has been previously executed. The revisited instruction is not executed.
//
//
// Return your score at the end of the process.
//
// Example:
// Input: instructions = ["jump","add","add","jump","add","jump"], values = [2,1,3,1,-2,-3]
//
// Output: 1
//
// Explanation:
//
// Simulate the process starting at instruction 0:
//
//
// 	At index 0: Instruction is "jump", move to index 0 + 2 = 2.
// 	At index 2: Instruction is "add", add values[2] = 3 to your score and move to index 3. Your score becomes 3.
// 	At index 3: Instruction is "jump", move to index 3 + 1 = 4.
// 	At index 4: Instruction is "add", add values[4] = -2 to your score and move to index 5. Your score becomes 1.
// 	At index 5: Instruction is "jump", move to index 5 + (-3) = 2.
// 	At index 2: Already visited. The process ends.
//
// Constraints:
// n == instructions.length == values.length
// 	1 <= n <= 105
// 	instructions[i] is either "add" or "jump".
// 	-105 <= values[i] <= 105
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Simulated Annealing (array, number, randomized, simulation)
//   • When to use: Use when seeking a near-optimal solution for complex optimization problems with many local optima, especially when exact solutions are computationally infeasible or too slow.
//   • Idea: Simulated Annealing is a probabilistic metaheuristic for global optimization, inspired by the annealing process in metallurgy. It explores the search space by accepting worse solutions with a probability that decreases over time, aiming to escape local optima.
//   • Invariants: The `s_best` state always represents the lowest energy found across all iterations so far.; The temperature `T` is always non-negative and decreases monotonically with each iteration.
//   • Tips: Start with a sufficiently high initial temperature to allow broad exploration.; Choose a slow cooling schedule (decay rate) for better solution quality, at the cost of longer runtime.
//   • Pitfalls: Getting stuck in local minima if the cooling schedule is too fast.; Excessive runtime if the cooling schedule is too slow or initial temperature is too high.
// - Expression parsing (stack, simulation)
//   • When to use: Use this algorithm to evaluate an arithmetic expression given in infix notation, respecting operator precedence and parentheses. It is suitable for expressions with binary, left-associative operators.
//   • Idea: This algorithm evaluates an infix arithmetic expression using two stacks: one for operands and one for operators. It processes the expression from left to right, applying operator precedence and associativity rules to achieve an O(N) time complexity.
//   • Invariants: The operand stack always contains valid numerical values or intermediate results.; The operator stack maintains operators such that operators with higher or equal precedence are processed before lower precedence ones.
//   • Tips: Clearly define operator precedence and associativity rules for all operators.; Use a separate stack for operands (numbers) and operators (including parentheses).
//   • Pitfalls: Misinterpreting operator precedence or associativity rules can lead to incorrect results.; Failure to handle mismatched or unbalanced parentheses can cause runtime errors.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long calculateScore(char** instructions, int instructionsSize, int* values, int valuesSize) {
    long long score = 0;
    int visited[instructionsSize];
    for (int i = 0; i < instructionsSize; i++) {
        visited[i] = 0;
    }

    int index = 0;
    while (index >= 0 && index < instructionsSize && !visited[index]) {
        visited[index] = 1;
        if (instructions[index][0] == 'a') { // "add"
            score += values[index];
            index++;
        } else { // "jump"
            index += values[index];
        }
    }

    return score;       
}
