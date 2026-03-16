// Source: https://leetcode.com/problems/number-of-atoms/   |   Difficulty: Hard
//
// Problem Description:
// Given a string formula representing a chemical formula, return the count of each atom.
//
// The atomic element always starts with an uppercase character, then zero or more lowercase letters, representing the name.
//
// One or more digits representing that element's count may follow if the count is greater than 1. If the count is 1, no digits will follow.
//
//
// 	For example, "H2O" and "H2O2" are possible, but "H1O2" is impossible.
//
//
// Two formulas are concatenated together to produce another formula.
//
//
// 	For example, "H2O2He3Mg4" is also a formula.
//
//
// A formula placed in parentheses, and a count (optionally added) is also a formula.
//
//
// 	For example, "(H2O2)" and "(H2O2)3" are formulas.
//
//
// Return the count of all elements as a string in the following form: the first name (in sorted order), followed by its count (if that count is more than 1), followed by the second name (in sorted order), followed by its count (if that count is more than 1), and so on.
//
// The test cases are generated so that all the values in the output fit in a 32-bit integer.
//
// Example:
// Input: formula = "H2O"
// Output: "H2O"
// Explanation: The count of elements are {'H': 2, 'O': 1}.
//
// Constraints:
// 1 <= formula.length <= 1000
// 	formula consists of English letters, digits, '(', and ')'.
// 	formula is always valid.
//
// Helpful references (internal KB):
// - String Sorts (array, string, number, radix-sort, counting-sort)
//   • When to use: Use when sorting a large collection of fixed-length strings or integers, especially when the key range (alphabet size) is small. It is efficient for data with uniform key lengths.
//   • Idea: LSD Radix Sort sorts elements by processing digits or characters from the least significant to the most significant, using a stable counting sort for each position. It achieves a time complexity of O(W * (N + R)), where W is the key length, N is the number of items, and R is the radix.
//   • Invariants: After each pass 'd' (from 'w-1' down to '0'), the array 'a' is stably sorted based on characters from position 'd' to 'w-1'.; The 'count' array accurately reflects the frequency of each character at the current digit 'd' before cumulation.
//   • Tips: Utilize counting sort as the stable inner sorting algorithm for each digit pass.; Process characters or digits from right to left (least significant to most significant).
//   • Pitfalls: Inefficient for variable-length strings without proper padding or specialized handling.; Can be slower than comparison sorts for small input sizes or very large radix (R).
// - Balanced bracket sequences (number, counting)
//   • When to use: Use this when verifying if a sequence of delimiters is correctly nested and balanced. It is also applicable for counting or generating all possible valid sequences of a given length.
//   • Idea: This algorithm involves checking if a sequence of opening and closing delimiters is properly matched and nested, or enumerating such sequences. Validation typically uses a stack in O(N) time, while generation often involves backtracking with O(Catalan(N)) complexity.
//   • Invariants: The stack contains only opening delimiters that are yet to be matched.; The balance counter (open - close) is never negative at any point during traversal.
//   • Tips: Use a stack to track unmatched opening delimiters for validation.; Maintain a balance counter (increment for open, decrement for close) for a simpler check.
//   • Pitfalls: Forgetting to check if the stack is empty after processing the entire sequence.; Allowing a closing delimiter when no matching opening delimiter is available (empty stack or mismatch).
// - Generating all K-combinations (bitset, enumeration)
//   • When to use: When all subsets of a fixed size K need to be generated, either in lexicographical order or such that successive combinations differ by exactly one element.
//   • Idea: This algorithm enumerates all K-combinations from a set, either in lexicographical order or using a Gray code approach where adjacent combinations differ by a single element. It typically runs in O(N choose K) time, generating each combination in O(K) or O(1) amortized time.
//   • Invariants: Each generated combination contains exactly K distinct elements.; All elements within a combination are unique and from the original set.
//   • Tips: For lexicographical generation, find the rightmost element that can be incremented without exceeding its maximum possible value.; After incrementing an element, set all subsequent elements to their minimum valid values.
//   • Pitfalls: Incorrectly handling boundary conditions for the rightmost element or its maximum value.; Off-by-one errors when assigning subsequent elements after an increment.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} formula
 * @return {string}
 */
var countOfAtoms = function(formula) {
    const stack = [];
    let i = 0;

    while (i < formula.length) {
        if (formula[i] === '(') {
            stack.push('(');
            i++;
        } else if (formula[i] === ')') {
            let top = stack.pop();
            const tempMap = new Map();

            while (top !== '(') {
                for (const [key, value] of top) {
                    tempMap.set(key, (tempMap.get(key) || 0) + value);
                }
                top = stack.pop();
            }

            let count = 0;
            while (i < formula.length && isDigit(formula[i])) {
                count = count * 10 + parseInt(formula[i]);
                i++;
            }
            count = count || 1;

            for (const [key, value] of tempMap) {
                tempMap.set(key, value * count);
            }
            stack.push(tempMap);
        } else {
            let name = formula[i];
            i++;
            while (i < formula.length && isLowerCase(formula[i])) {
                name += formula[i];
                i++;
            }

            let count = 0;
            while (i < formula.length && isDigit(formula[i])) {
                count = count * 10 + parseInt(formula[i]);
                i++;
            }
            count = count || 1;

            const map = new Map();
            map.set(name, count);
            stack.push(map);
        }
    }

    const finalMap = new Map();
    while (stack.length > 0) {
        const top = stack.pop();
        for (const [key, value] of top) {
            finalMap.set(key, (finalMap.get(key) || 0) + value);
        }
    }

    const sortedKeys = Array.from(finalMap.keys()).sort();
    let result = '';
    for (const key of sortedKeys) {
        result += key + (finalMap.get(key) > 1 ? finalMap.get(key) : '');
    }

    return result;
};
