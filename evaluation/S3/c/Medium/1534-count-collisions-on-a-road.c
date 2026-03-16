// Source: https://leetcode.com/problems/count-collisions-on-a-road/   |   Difficulty: Medium
//
// Problem Description:
// There are n cars on an infinitely long road. The cars are numbered from 0 to n - 1 from left to right and each car is present at a unique point.
//
// You are given a 0-indexed string directions of length n. directions[i] can be either 'L', 'R', or 'S' denoting whether the ith car is moving towards the left, towards the right, or staying at its current point respectively. Each moving car has the same speed.
//
// The number of collisions can be calculated as follows:
//
//
// 	When two cars moving in opposite directions collide with each other, the number of collisions increases by 2.
// 	When a moving car collides with a stationary car, the number of collisions increases by 1.
//
//
// After a collision, the cars involved can no longer move and will stay at the point where they collided. Other than that, cars cannot change their state or direction of motion.
//
// Return the total number of collisions that will happen on the road.
//
// Example:
// Input: directions = "RLRSLL"
// Output: 5
// Explanation:
// The collisions that will happen on the road are:
// - Cars 0 and 1 will collide with each other. Since they are moving in opposite directions, the number of collisions becomes 0 + 2 = 2.
// - Cars 2 and 3 will collide with each other. Since car 3 is stationary, the number of collisions becomes 2 + 1 = 3.
// - Cars 3 and 4 will collide with each other. Since car 3 is stationary, the number of collisions becomes 3 + 1 = 4.
// - Cars 4 and 5 will collide with each other. After car 4 collides with car 3, it will stay at the point of collision and get hit by car 5. The number of collisions becomes 4 + 1 = 5.
// Thus, the total number of collisions that will happen on the road is 5.
//
// Constraints:
// 1 <= directions.length <= 105
// 	directions[i] is either 'L', 'R', or 'S'.
//
// Helpful references (internal KB):
// - Suffix Array (array, string, simulation, two-pointers)
//   • When to use: Use when needing to efficiently compare substrings, find all occurrences of a pattern, or determine lexicographical order among suffixes within a string.
//   • Idea: A Suffix Array stores sorted suffixes of a string, enabling fast substring comparisons and pattern searching. Construction typically takes O(N log N) time, with comparisons often O(1) after preprocessing.
//   • Invariants: The suffix array `p` contains all suffixes of the string `s` sorted lexicographically.; During construction, equivalence classes `c` correctly group suffixes that are identical up to a certain length `2^k`.
//   • Tips: Precompute log values for efficient block length calculation.; Utilize equivalence classes for O(1) comparison of power-of-two length substrings.
//   • Pitfalls: Complexity of suffix array construction can be tricky (e.g., O(N log N) vs O(N)).; Off-by-one errors when calculating block indices or lengths.
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Linked-list implementations of collections (linked-list, stack, simulation)
//   • When to use: Use when a Last-In, First-Out (LIFO) data structure is required, and dynamic size with efficient O(1) push and pop operations is crucial, especially without a fixed capacity.
//   • Idea: This describes implementing a stack using a singly linked list, where elements are added and removed from the head of the list. Both push and pop operations achieve O(1) time complexity.
//   • Invariants: The 'first' pointer always points to the top element of the stack, or is null if the stack is empty.; Each node's 'next' pointer correctly links to the subsequent element in the stack, maintaining the LIFO order.
//   • Tips: Maintain a 'first' pointer to the head of the linked list, representing the stack's top.; Push operation involves creating a new node, linking it to the current 'first', then updating 'first'.
//   • Pitfalls: Forgetting to handle the empty stack case for pop, leading to `NoSuchElementException`.; Incorrectly updating the 'first' pointer during push or pop, which can break the list structure.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int countCollisions(char* directions) {
    int collisions = 0;
    int n = strlen(directions);
    int leftCollisions = 0; // Count of cars moving left that will collide
    int rightCollisions = 0; // Count of cars moving right that will collide

    for (int i = 0; i < n; i++) {
        if (directions[i] == 'R') {
            rightCollisions++; // A car moving right may collide with future cars
        } else if (directions[i] == 'L') {
            if (rightCollisions > 0) {
                collisions += 2; // Collision between a right-moving and a left-moving car
                rightCollisions--; // One right-moving car is now stationary after collision
            } else {
                leftCollisions++; // A car moving left may collide with future cars
            }
        } else { // directions[i] == 'S'
            if (rightCollisions > 0) {
                collisions += rightCollisions; // All right-moving cars will collide with this stationary car
                rightCollisions = 0; // All right-moving cars are now stationary after collision
            }
            if (leftCollisions > 0) {
                collisions += leftCollisions; // All left-moving cars will collide with this stationary car
                leftCollisions = 0; // All left-moving cars are now stationary after collision
            }
        }
    }

    return collisions;      
}
