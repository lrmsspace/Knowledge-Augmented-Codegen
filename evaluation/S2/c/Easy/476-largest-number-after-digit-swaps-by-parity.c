// Source: https://leetcode.com/problems/largest-number-after-digit-swaps-by-parity/   |   Difficulty: Easy
//
// Problem Description:
// You are given a positive integer num. You may swap any two digits of num that have the same parity (i.e. both odd digits or both even digits).
//
// Return the largest possible value of num after any number of swaps.
//
// Example:
// Input: num = 1234
// Output: 3412
// Explanation: Swap the digit 3 with the digit 1, this results in the number 3214.
// Swap the digit 2 with the digit 4, this results in the number 3412.
// Note that there may be other sequences of swaps but it can be shown that 3412 is the largest possible number.
// Also note that we may not swap the digit 4 with the digit 1 since they are of different parities.
//
// Constraints:
// 1 <= num <= 109
//
// Helpful references (internal KB):
// - String Sorts (array, string, number, radix-sort, counting-sort)
//   • When to use: Use when sorting a large collection of fixed-length strings or integers, especially when the key range (alphabet size) is small. It is efficient for data with uniform key lengths.
//   • Idea: LSD Radix Sort sorts elements by processing digits or characters from the least significant to the most significant, using a stable counting sort for each position. It achieves a time complexity of O(W * (N + R)), where W is the key length, N is the number of items, and R is the radix.
//   • Invariants: After each pass 'd' (from 'w-1' down to '0'), the array 'a' is stably sorted based on characters from position 'd' to 'w-1'.; The 'count' array accurately reflects the frequency of each character at the current digit 'd' before cumulation.
//   • Tips: Utilize counting sort as the stable inner sorting algorithm for each digit pass.; Process characters or digits from right to left (least significant to most significant).
//   • Pitfalls: Inefficient for variable-length strings without proper padding or specialized handling.; Can be slower than comparison sorts for small input sizes or very large radix (R).
// - Finding the Eulerian path in O(M) (graph, enumeration, bfs)
//   • When to use: Use when the problem requires visiting every edge in a graph exactly once, either starting and ending at the same vertex (cycle) or at two different vertices (path).
//   • Idea: An Eulerian path is a trail in a graph which visits every edge exactly once. An Eulerian cycle is an Eulerian path that starts and ends on the same vertex.
//   • Invariants: Every edge in the graph is considered exactly once for inclusion in the path.; The current path segment always forms a valid trail in the graph.
//   • Tips: Check vertex degrees to determine path/cycle existence before attempting to find it.; For an Eulerian path, start traversal from one of the two odd-degree vertices.
//   • Pitfalls: Incorrectly handling multi-edges or self-loops can lead to errors in degree calculation or traversal.; Failing to check graph connectivity can result in incomplete paths or infinite loops.
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int largestInteger(int num) {
    char str[12]; // Enough to hold the string representation of num (up to 10 digits + null terminator)
    sprintf(str, "%d", num); // Convert the integer to a string

    int odd_digits[10], even_digits[10];
    int odd_count = 0, even_count = 0;

    // Separate odd and even digits
    for (int i = 0; str[i] != '\0'; i++) {
        if ((str[i] - '0') % 2 == 0) {
            even_digits[even_count++] = str[i] - '0';
        } else {
            odd_digits[odd_count++] = str[i] - '0';
        }
    }

    // Sort odd and even digits in descending order
    for (int i = 0; i < odd_count - 1; i++) {
        for (int j = 0; j < odd_count - i - 1; j++) {
            if (odd_digits[j] < odd_digits[j + 1]) {
                int temp = odd_digits[j];
                odd_digits[j] = odd_digits[j + 1];
                odd_digits[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < even_count - 1; i++) {
        for (int j = 0; j < even_count - i - 1; j++) {
            if (even_digits[j] < even_digits[j + 1]) {
                int temp = even_digits[j];
                even_digits[j] = even_digits[j + 1];
                even_digits[j + 1] = temp;
            }
        }
    }

    // Reconstruct the largest number by swapping digits of the same parity
    int odd_index = 0, even_index = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if ((str[i] - '0') % 2 == 0) {
            str[i] = even_digits[even_index++] + '0';
        } else {
            str[i] = odd_digits[odd_index++] + '0';
        }
    }

    return atoi(str); // Convert the modified string back to an integer     
}
