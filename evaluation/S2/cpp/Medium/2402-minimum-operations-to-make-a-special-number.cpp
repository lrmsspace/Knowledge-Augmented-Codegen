// Source: https://leetcode.com/problems/minimum-operations-to-make-a-special-number/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed string num representing a non-negative integer.
//
// In one operation, you can pick any digit of num and delete it. Note that if you delete all the digits of num, num becomes 0.
//
// Return the minimum number of operations required to make num special.
//
// An integer x is considered special if it is divisible by 25.
//
// Example:
// Input: num = "2245047"
// Output: 2
// Explanation: Delete digits num[5] and num[6]. The resulting number is "22450" which is special since it is divisible by 25.
// It can be shown that 2 is the minimum number of operations required to get a special number.
//
// Constraints:
// 1 <= num.length <= 100
// 	num only consists of digits '0' through '9'.
// 	num does not contain any leading zeros.
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// - String Hashing (string, number, hashing)
//   • When to use: Use when needing to compare strings or substrings quickly, reducing comparison time from linear to constant. It is ideal for problems requiring frequent string equality checks or pattern matching across large texts.
//   • Idea: String hashing maps a string to an integer hash value, allowing for O(1) equality checks between strings or substrings. This technique relies on a hash function where equal strings must produce equal hashes, though the reverse is not guaranteed.
//   • Invariants: The hash of any prefix s[0...i] is correctly computed based on s[0...i-1] and s[i].; All characters processed up to the current index i contribute to the current hash value.
//   • Tips: Use a polynomial rolling hash function with a prime base and a large prime modulus.; Employ double hashing (two different bases/moduli) to significantly reduce collision probability.
//   • Pitfalls: Hash collisions: Different strings can produce the same hash, leading to false positives if not handled.; Poor choice of base or modulus can lead to more frequent collisions.
// - 0-1 BFS (graph, deque, 01-bfs, bfs)
//   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently computes single-source shortest paths, outperforming Dijkstra's for this specific weight constraint.
//   • Idea: 0-1 BFS is a graph traversal algorithm that finds the single-source shortest paths in a graph where all edge weights are restricted to 0 or 1. It uses a deque to process nodes, achieving an optimal time complexity of O(V + E).
//   • Invariants: When a node 'u' is extracted from the front of the deque, 'dist[u]' is its shortest path from the source.; The deque always contains nodes whose distances are either 'D' or 'D+1', where 'D' is the distance of the last node extracted.
//   • Tips: Always push 0-weight edges to the front of the deque.; Push 1-weight edges to the back of the deque.
//   • Pitfalls: Pushing 0-weight edges to the back or 1-weight edges to the front of the deque.; Not correctly initializing distances or the source node.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minimumOperations(string num) {
        int n = num.size();
        int ans = n; // Initialize with the maximum possible operations (deleting all digits)

        // Check for the special numbers that are multiples of 25: "00", "25", "50", "75"
        vector<string> targets = {"00", "25", "50", "75"};

        for (const string& target : targets) {
            int t1 = target[0], t2 = target[1];
            int count = 0;
            bool found_t2 = false;

            // Traverse the number from the end to find the target digits
            for (int i = n - 1; i >= 0; --i) {
                if (!found_t2 && num[i] == t2) {
                    found_t2 = true; // Found the second digit of the target
                } else if (found_t2 && num[i] == t1) {
                    // Found the first digit of the target after finding the second
                    ans = min(ans, count); // Update the minimum operations
                    break;
                } else {
                    count++; // Increment count for each digit that needs to be deleted
                }
            }
        }

        return ans;         
    }
};
