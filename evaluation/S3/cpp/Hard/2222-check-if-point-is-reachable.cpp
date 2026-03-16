// Source: https://leetcode.com/problems/check-if-point-is-reachable/   |   Difficulty: Hard
//
// Problem Description:
// There exists an infinitely large grid. You are currently at point (1, 1), and you need to reach the point (targetX, targetY) using a finite number of steps.
//
// In one step, you can move from point (x, y) to any one of the following points:
//
//
// 	(x, y - x)
// 	(x - y, y)
// 	(2 * x, y)
// 	(x, 2 * y)
//
//
// Given two integers targetX and targetY representing the X-coordinate and Y-coordinate of your final position, return true if you can reach the point from (1, 1) using some number of steps, and false otherwise.
//
// Example:
// Input: targetX = 6, targetY = 9
// Output: false
// Explanation: It is impossible to reach (6,9) from (1,1) using any sequence of moves, so false is returned.
//
// Constraints:
// 1 <= targetX, targetY <= 109
//
// Helpful references (internal KB):
// - Integer factorization (number, randomized, gcd, two-pointers)
//   • When to use: Used to find non-trivial factors of a large composite number, especially when trial division is too slow. It's effective for numbers with relatively small prime factors or factors whose predecessors are powersmooth.
//   • Idea: Integer factorization algorithms like Pollard's p-1 and Pollard's Rho probabilistically find factors of composite numbers. Pollard's p-1 leverages modular exponentiation and GCD, while Pollard's Rho uses cycle detection on a pseudo-random sequence.
//   • Invariants: For Pollard's p-1, a^M mod p remains 1 for any prime factor p where p-1 divides M.; For Pollard's p-1, M is always a multiple of lcm(1, 2, ..., B) for the current B.
//   • Tips: Pollard's p-1 is effective when p-1 is B-powersmooth for a factor p.; Pollard's Rho is generally more robust for arbitrary composite numbers.
//   • Pitfalls: Algorithms are probabilistic; no guarantee of finding a factor.; May return n (the number itself) or 1, requiring retry with different parameters.
// - Finding the equation of a line for a segment (number, geometry, gcd)
//   • When to use: Use this method when you need to represent a line segment's equation using integer coefficients, especially to avoid floating-point inaccuracies in geometric computations.
//   • Idea: This method derives the general form of a line equation (Ax + By + C = 0) from two points, ensuring integer coefficients if input coordinates are integers. It then normalizes these coefficients using GCD to achieve a unique representation, typically in O(log(max(|A|,|B|,|C|))) time due to GCD.
//   • Invariants: The calculated coefficients A, B, C always satisfy A*Px + B*Py + C = 0 for point P(Px, Py).; After GCD division, the absolute values of A, B, C are coprime (unless all are zero).
//   • Tips: Always compute A, B, C using the given formulas for P(Px, Py) and Q(Qx, Qy).; Use absolute values of A, B, C when calculating their greatest common divisor.
//   • Pitfalls: Forgetting to normalize coefficients leads to non-unique representations for the same line.; Incorrectly handling signs during the final normalization step can result in inconsistent forms.
// - Lattice points inside non-lattice polygon (number, recursion, counting, gcd)
//   • When to use: Use when counting pairs or elements satisfying divisibility or GCD conditions. Also applicable for summing functions over pairs using number theory properties.
//   • Idea: This approach leverages number theoretic properties like GCD, LCM, and prime factorization to efficiently count elements or pairs satisfying specific criteria. It often involves iterating through divisors or multiples, achieving complexities like O(N log N) or O(sqrt N) per query.
//   • Invariants: All numbers processed so far have their relevant number-theoretic properties (e.g., prime factors, divisors) correctly determined.; The current count or sum accurately reflects all valid combinations found up to the current iteration.
//   • Tips: Precompute primes or divisors using a sieve for efficiency.; Utilize properties of GCD and LCM, such as gcd(a,b) * lcm(a,b) = a * b.
//   • Pitfalls: Overcounting or undercounting when using inclusion-exclusion.; Integer overflow with large products or sums.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    bool isReachable(int targetX, int targetY) {
        while (targetX > 1 || targetY > 1) {
            if (targetX == targetY) {
                return false;
            }
            if (targetX > targetY) {
                if (targetY == 1) {
                    return true;
                }
                if (targetX % 2 == 0 && targetX / 2 >= targetY) {
                    targetX /= 2;
                } else {
                    targetX -= targetY;
                }
            } else {
                if (targetX == 1) {
                    return true;
                }
                if (targetY % 2 == 0 && targetY / 2 >= targetX) {
                    targetY /= 2;
                } else {
                    targetY -= targetX;
                }
            }
        }
        return true;            
    }
};
