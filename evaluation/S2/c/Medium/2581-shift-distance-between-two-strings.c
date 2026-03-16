// Source: https://leetcode.com/problems/shift-distance-between-two-strings/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings s and t of the same length, and two integer arrays nextCost and previousCost.
//
// In one operation, you can pick any index i of s, and perform either one of the following actions:
//
//
// 	Shift s[i] to the next letter in the alphabet. If s[i] == 'z', you should replace it with 'a'. This operation costs nextCost[j] where j is the index of s[i] in the alphabet.
// 	Shift s[i] to the previous letter in the alphabet. If s[i] == 'a', you should replace it with 'z'. This operation costs previousCost[j] where j is the index of s[i] in the alphabet.
//
//
// The shift distance is the minimum total cost of operations required to transform s into t.
//
// Return the shift distance from s to t.
//
// Example:
// Input: s = "abab", t = "baba", nextCost = [100,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0], previousCost = [1,100,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
//
// Output: 2
//
// Explanation:
//
//
// 	We choose index i = 0 and shift s[0] 25 times to the previous character for a total cost of 1.
// 	We choose index i = 1 and shift s[1] 25 times to the next character for a total cost of 0.
// 	We choose index i = 2 and shift s[2] 25 times to the previous character for a total cost of 1.
// 	We choose index i = 3 and shift s[3] 25 times to the next character for a total cost of 0.
//
// Constraints:
// 1 <= s.length == t.length <= 105
// 	s and t consist only of lowercase English letters.
// 	nextCost.length == previousCost.length == 26
// 	0 <= nextCost[i], previousCost[i] <= 109
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long shiftDistance(char* s, char* t, int* nextCost, int nextCostSize, int* previousCost, int previousCostSize) {
    long long totalCost = 0;
    int i = 0;
    
    while (s[i] != '\0') {
        char sChar = s[i];
        char tChar = t[i];
        
        if (sChar != tChar) {
            int sIndex = sChar - 'a';
            int tIndex = tChar - 'a';
            
            // Calculate the cost of shifting forward
            int forwardShifts = (tIndex - sIndex + 26) % 26;
            long long forwardCost = (long long)forwardShifts * nextCost[sIndex];
            
            // Calculate the cost of shifting backward
            int backwardShifts = (sIndex - tIndex + 26) % 26;
            long long backwardCost = (long long)backwardShifts * previousCost[sIndex];
            
            // Add the minimum of the two costs to the total cost
            totalCost += forwardCost < backwardCost ? forwardCost : backwardCost;
        }
        
        i++;
    }
    
    return totalCost;       
}
