// Source: https://leetcode.com/problems/maximum-good-people-based-on-statements/   |   Difficulty: Hard
//
// Problem Description:
// There are two types of persons:
//
//
// 	The good person: The person who always tells the truth.
// 	The bad person: The person who might tell the truth and might lie.
//
//
// You are given a 0-indexed 2D integer array statements of size n x n that represents the statements made by n people about each other. More specifically, statements[i][j] could be one of the following:
//
//
// 	0 which represents a statement made by person i that person j is a bad person.
// 	1 which represents a statement made by person i that person j is a good person.
// 	2 represents that no statement is made by person i about person j.
//
//
// Additionally, no person ever makes a statement about themselves. Formally, we have that statements[i][i] = 2 for all 0 <= i < n.
//
// Return the maximum number of people who can be good based on the statements made by the n people.
//
// Example:
// Input: statements = [[2,1,2],[1,2,2],[2,0,2]]
// Output: 2
// Explanation: Each person makes a single statement.
// - Person 0 states that person 1 is good.
// - Person 1 states that person 0 is good.
// - Person 2 states that person 1 is bad.
// Let's take person 2 as the key.
// - Assuming that person 2 is a good person:
//     - Based on the statement made by person 2, person 1 is a bad person.
//     - Now we know for sure that person 1 is bad and person 2 is good.
//     - Based on the statement made by person 1, and since person 1 is bad, they could be:
//         - telling the truth. There will be a contradiction in this case and this assumption is invalid.
//         - lying. In this case, person 0 is also a bad person and lied in their statement.
//     - Following that person 2 is a good person, there will be only one good person in the group.
// - Assuming that person 2 is a bad person:
//     - Based on the statement made by person 2, and since person 2 is bad, they could be:
//         - telling the truth. Following this scenario, person 0 and 1 are both bad as explained before.
//             - Following that person 2 is bad but told the truth, there will be no good persons in the group.
//         - lying. In this case person 1 is a good person.
//             - Since person 1 is a good person, person 0 is also a good person.
//             - Following that person 2 is bad and lied, there will be two good persons in the group.
// We can see that at most 2 persons are good in the best case, so we return 2.
// Note that there is more than one way to arrive at this conclusion.
//
// Constraints:
// n == statements.length == statements[i].length
// 	2 <= n <= 15
// 	statements[i][j] is either 0, 1, or 2.
// 	statements[i][i] == 2
//
// Helpful references (internal KB):
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
// - Generating all K-combinations (bitset, enumeration)
//   • When to use: When all subsets of a fixed size K need to be generated, either in lexicographical order or such that successive combinations differ by exactly one element.
//   • Idea: This algorithm enumerates all K-combinations from a set, either in lexicographical order or using a Gray code approach where adjacent combinations differ by a single element. It typically runs in O(N choose K) time, generating each combination in O(K) or O(1) amortized time.
//   • Invariants: Each generated combination contains exactly K distinct elements.; All elements within a combination are unique and from the original set.
//   • Tips: For lexicographical generation, find the rightmost element that can be incremented without exceeding its maximum possible value.; After incrementing an element, set all subsequent elements to their minimum valid values.
//   • Pitfalls: Incorrectly handling boundary conditions for the rightmost element or its maximum value.; Off-by-one errors when assigning subsequent elements after an increment.
// - Generating all K-combinations (bitset, recursion, enumeration)
//   • When to use: Use when an exhaustive list of all subsets of a specific size K from a set of N items is required. It's suitable for problems needing to explore every possible configuration of K elements.
//   • Idea: This algorithm systematically generates all unique subsets of size K from a set of N distinct elements, commonly employing recursion or bit manipulation. The typical time complexity is O(N choose K * K) for construction or O(N choose K) if just iterating.
//   • Invariants: The current partial combination always contains unique elements.; The number of elements chosen so far does not exceed K.
//   • Tips: Employ backtracking or recursion for a straightforward implementation.; Utilize bitmasks for efficient representation and generation, especially for smaller N.
//   • Pitfalls: Accidentally generating duplicate combinations if elements are not handled uniquely.; Failing to correctly define base cases or termination conditions for recursive calls.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maximumGood(int** statements, int statementsSize, int* statementsColSize) {
    int n = statementsSize;
    int maxGood = 0;

    // Iterate through all possible combinations of good and bad people using a bitmask
    for (int mask = 0; mask < (1 << n); mask++) {
        int goodCount = 0;
        int isValid = 1; // Assume the current combination is valid until proven otherwise

        for (int i = 0; i < n && isValid; i++) {
            if (mask & (1 << i)) { // If person i is considered good
                goodCount++;
                for (int j = 0; j < n; j++) {
                    if (statements[i][j] == 2) continue; // No statement about person j
                    if ((statements[i][j] == 1 && !(mask & (1 << j))) || // Person i says j is good but j is bad
                        (statements[i][j] == 0 && (mask & (1 << j)))) { // Person i says j is bad but j is good
                        isValid = 0; // Contradiction found, mark as invalid
                        break;
                    }
                }
            }
        }

        if (isValid) {
            maxGood = goodCount > maxGood ? goodCount : maxGood; // Update maxGood if current combination is valid and has more good people
        }
    }

    return maxGood;     
}
