// Source: https://leetcode.com/problems/number-of-pairs-of-interchangeable-rectangles/   |   Difficulty: Medium
//
// Problem Description:
// You are given n rectangles represented by a 0-indexed 2D integer array rectangles, where rectangles[i] = [widthi, heighti] denotes the width and height of the ith rectangle.
//
// Two rectangles i and j (i < j) are considered interchangeable if they have the same width-to-height ratio. More formally, two rectangles are interchangeable if widthi/heighti == widthj/heightj (using decimal division, not integer division).
//
// Return the number of pairs of interchangeable rectangles in rectangles.
//
// Example:
// Input: rectangles = [[4,8],[3,6],[10,20],[15,30]]
// Output: 6
// Explanation: The following are the interchangeable pairs of rectangles by index (0-indexed):
// - Rectangle 0 with rectangle 1: 4/8 == 3/6.
// - Rectangle 0 with rectangle 2: 4/8 == 10/20.
// - Rectangle 0 with rectangle 3: 4/8 == 15/30.
// - Rectangle 1 with rectangle 2: 3/6 == 10/20.
// - Rectangle 1 with rectangle 3: 3/6 == 15/30.
// - Rectangle 2 with rectangle 3: 10/20 == 15/30.
//
// Constraints:
// n == rectangles.length
// 	1 <= n <= 105
// 	rectangles[i].length == 2
// 	1 <= widthi, heighti <= 105
//
// Helpful references (internal KB):
// - Lattice points inside non-lattice polygon (number, recursion, counting, gcd)
//   • When to use: Use when counting pairs or elements satisfying divisibility or GCD conditions. Also applicable for summing functions over pairs using number theory properties.
//   • Idea: This approach leverages number theoretic properties like GCD, LCM, and prime factorization to efficiently count elements or pairs satisfying specific criteria. It often involves iterating through divisors or multiples, achieving complexities like O(N log N) or O(sqrt N) per query.
//   • Invariants: All numbers processed so far have their relevant number-theoretic properties (e.g., prime factors, divisors) correctly determined.; The current count or sum accurately reflects all valid combinations found up to the current iteration.
//   • Tips: Precompute primes or divisors using a sieve for efficiency.; Utilize properties of GCD and LCM, such as gcd(a,b) * lcm(a,b) = a * b.
//   • Pitfalls: Overcounting or undercounting when using inclusion-exclusion.; Integer overflow with large products or sums.
// - Euler's totient function
//  (array, number, enumeration)
//   • When to use: Use when needing to count positive integers up to n that are relatively prime to n. It is also efficient for computing totient values for all numbers in a given range.
//   • Idea: Euler's totient function, φ(n), counts positive integers less than or equal to n that are relatively prime to n. It can be computed for a single n in O(sqrt(n)) using prime factorization, or for all numbers up to N in O(N log log N) using a sieve-like algorithm.
//   • Invariants: phi[i] stores the current totient value for i, which is i initially, then updated by (1 - 1/p) for each prime p dividing i.; After iterating through all primes p up to sqrt(N), phi[i] holds the correct totient value for all i <= N.
//   • Tips: For a single n, compute φ(n) using its prime factorization.; For all φ(i) up to N, use a sieve approach similar to Sieve of Eratosthenes.
//   • Pitfalls: Confusing 'relatively prime' with 'prime number'.; Applying the multiplicative property incorrectly when numbers share common factors.
// - Finding the equation of a line for a segment (number, geometry, gcd)
//   • When to use: Use this method when you need to represent a line segment's equation using integer coefficients, especially to avoid floating-point inaccuracies in geometric computations.
//   • Idea: This method derives the general form of a line equation (Ax + By + C = 0) from two points, ensuring integer coefficients if input coordinates are integers. It then normalizes these coefficients using GCD to achieve a unique representation, typically in O(log(max(|A|,|B|,|C|))) time due to GCD.
//   • Invariants: The calculated coefficients A, B, C always satisfy A*Px + B*Py + C = 0 for point P(Px, Py).; After GCD division, the absolute values of A, B, C are coprime (unless all are zero).
//   • Tips: Always compute A, B, C using the given formulas for P(Px, Py) and Q(Qx, Qy).; Use absolute values of A, B, C when calculating their greatest common divisor.
//   • Pitfalls: Forgetting to normalize coefficients leads to non-unique representations for the same line.; Incorrectly handling signs during the final normalization step can result in inconsistent forms.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long interchangeableRectangles(int** rectangles, int rectanglesSize, int* rectanglesColSize) {
    // We will use a hash map to count the frequency of each unique width-to-height ratio.
    // The key will be the reduced form of the ratio (width/gcd, height/gcd).
    // The value will be the count of rectangles with that ratio.

    // Define a structure for the hash map entries.
    typedef struct {
        int width;
        int height;
        long long count;
    } RatioEntry;

    // We will use a simple hash function and linear probing for collision resolution.
    #define HASH_SIZE 100003
    RatioEntry hashMap[HASH_SIZE];
    
    // Initialize the hash map.
    for (int i = 0; i < HASH_SIZE; i++) {
        hashMap[i].width = -1; // Indicates an empty slot.
        hashMap[i].height = -1;
        hashMap[i].count = 0;
    }

    long long result = 0;

    for (int i = 0; i < rectanglesSize; i++) {
        int width = rectangles[i][0];
        int height = rectangles[i][1];

        // Compute the GCD of width and height to reduce the ratio.
        int gcdValue = gcd(width, height);
        int reducedWidth = width / gcdValue;
        int reducedHeight = height / gcdValue;

        // Compute the hash index for this ratio.
        int hashIndex = ((long long)reducedWidth * 31 + reducedHeight) % HASH_SIZE;

        // Linear probing to find the correct slot in the hash map.
        while (hashMap[hashIndex].width != -1) {
            if (hashMap[hashIndex].width == reducedWidth && hashMap[hashIndex].height == reducedHeight) {
                // Found the same ratio, increment the count and update result.
                result += hashMap[hashIndex].count; // Each existing rectangle with this ratio forms a pair with the current rectangle.
                hashMap[hashIndex].count++; // Increment count for this ratio.
                break;
            }
            hashIndex = (hashIndex + 1) % HASH_SIZE; // Move to the next slot.
        }

        if (hashMap[hashIndex].width == -1) {
            // This is a new ratio, add it to the hash map.
            hashMap[hashIndex].width = reducedWidth;
            hashMap[hashIndex].height = reducedHeight;      
            hashMap[hashIndex].count = 1; // First rectangle with this ratio.
        }
        
    }
    return result;
}
