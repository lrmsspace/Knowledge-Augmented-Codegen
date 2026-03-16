// Source: https://leetcode.com/problems/categorize-box-according-to-criteria/   |   Difficulty: Easy
//
// Problem Description:
// Given four integers length, width, height, and mass, representing the dimensions and mass of a box, respectively, return a string representing the category of the box.
//
//
// 	The box is "Bulky" if:
//
// 	
// 		Any of the dimensions of the box is greater or equal to 104.
// 		Or, the volume of the box is greater or equal to 109.
// 	
// 	
// 	If the mass of the box is greater or equal to 100, it is "Heavy".
// 	If the box is both "Bulky" and "Heavy", then its category is "Both".
// 	If the box is neither "Bulky" nor "Heavy", then its category is "Neither".
// 	If the box is "Bulky" but not "Heavy", then its category is "Bulky".
// 	If the box is "Heavy" but not "Bulky", then its category is "Heavy".
//
//
// Note that the volume of the box is the product of its length, width and height.
//
// Example:
// Input: length = 1000, width = 35, height = 700, mass = 300
// Output: "Heavy"
// Explanation: 
// None of the dimensions of the box is greater or equal to 104. 
// Its volume = 24500000 <= 109. So it cannot be categorized as "Bulky".
// However mass >= 100, so the box is "Heavy".
// Since the box is not "Bulky" but "Heavy", we return "Heavy".
//
// Constraints:
// 1 <= length, width, height <= 105
// 	1 <= mass <= 103
//
// Helpful references (internal KB):
// - Check if two segments intersect (geometry, number, simulation)
//   • When to use: Use this when determining if two line segments in a 2D plane share any common points, especially when floating-point precision issues need to be avoided.
//   • Idea: This algorithm determines if two line segments intersect by handling collinear and non-collinear cases separately, primarily using integer arithmetic to avoid precision errors. It typically runs in O(1) time.
//   • Invariants: If segments are collinear, their 1D projections on both axes must overlap for intersection.; If segments are not collinear, each segment's endpoints must lie on opposite sides of the line containing the other segment.
//   • Tips: Handle collinear segments as a distinct special case.; Utilize cross products for efficient orientation checks.
//   • Pitfalls: Failing to correctly identify and handle collinear segments.; Introducing floating-point errors by using division for slopes.
// - Basic Geometry (geometry, matrix, number, simulation)
//   • When to use: Use when solving problems involving fundamental geometric entities like points, lines, and planes, or when performing basic vector operations to determine relationships or intersections.
//   • Idea: This card covers foundational concepts in 2D and 3D geometry, including vector products and their applications in defining lines, planes, and calculating orientations or intersections. It primarily involves algebraic manipulation of vector equations, typically with O(1) complexity for basic operations on fixed-dimension vectors.
//   • Invariants: Vector operations (cross, triple products) maintain their geometric and algebraic properties.; A line defined by two points or a point and direction vector remains consistent.
//   • Tips: Understand the geometric interpretation of vector products.; Use vector equations to define lines and planes concisely.
//   • Pitfalls: Confusing pseudo-scalar product with dot product.; Incorrectly applying cross product in 2D contexts.
// - Bit manipulation (number, simulation)
//   • When to use: Use when operations on individual bits of an integer are required, for optimizing arithmetic with powers of two, or for efficient management of boolean flags.
//   • Idea: Bit manipulation involves directly operating on the binary representation of numbers using bitwise operators and shifts. These operations typically have O(1) time complexity as they are hardware-level instructions.
//   • Invariants: The total number of bits representing the integer remains constant for fixed-width types.; Applying `n & (1 << k)` isolates the k-th bit, setting all other bits to zero.
//   • Tips: Use `&` with `(1 << k)` to check if the k-th bit is set.; Use `|` with `(1 << k)` to set the k-th bit.
//   • Pitfalls: Be aware of integer overflow when performing large left shifts.; Understand the difference between arithmetic and logical right shifts, especially for signed numbers.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* categorizeBox(int length, int width, int height, int mass) {
    long long volume = (long long)length * width * height;
    int isBulky = (length >= 10000 || width >= 10000 || height >= 10000 || volume >= 1000000000);
    int isHeavy = (mass >= 100);

    if (isBulky && isHeavy) {
        return "Both";
    } else if (isBulky) {
        return "Bulky";
    } else if (isHeavy) {
        return "Heavy";
    } else {
        return "Neither";
    }       
}
