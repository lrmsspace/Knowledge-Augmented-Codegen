// Source: https://leetcode.com/problems/maximum-square-area-by-removing-fences-from-a-field/   |   Difficulty: Medium
//
// Problem Description:
// There is a large (m - 1) x (n - 1) rectangular field with corners at (1, 1) and (m, n) containing some horizontal and vertical fences given in arrays hFences and vFences respectively.
//
// Horizontal fences are from the coordinates (hFences[i], 1) to (hFences[i], n) and vertical fences are from the coordinates (1, vFences[i]) to (m, vFences[i]).
//
// Return the maximum area of a square field that can be formed by removing some fences (possibly none) or -1 if it is impossible to make a square field.
//
// Since the answer may be large, return it modulo 109 + 7.
//
// Note: The field is surrounded by two horizontal fences from the coordinates (1, 1) to (1, n) and (m, 1) to (m, n) and two vertical fences from the coordinates (1, 1) to (m, 1) and (1, n) to (m, n). These fences cannot be removed.
//
// Example:
// Input: m = 4, n = 3, hFences = [2,3], vFences = [2]
// Output: 4
// Explanation: Removing the horizontal fence at 2 and the vertical fence at 2 will give a square field of area 4.
//
// Constraints:
// 3 <= m, n <= 109
// 	1 <= hFences.length, vFences.length <= 600
// 	1 < hFences[i] < m
// 	1 < vFences[i] < n
// 	hFences and vFences are unique.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int maximizeSquareArea(int m, int n, int[] hFences, int[] vFences) {
        int mod = 1_000_000_007;
        int maxHGap = getMaxGap(hFences, m);
        int maxVGap = getMaxGap(vFences, n);
        long area = (long) maxHGap * maxVGap;
        return (int) (area % mod);          
    }
}
