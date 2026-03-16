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

int maximizeSquareArea(int m, int n, int* hFences, int hFencesSize, int* vFences, int vFencesSize) {
    #define MOD 1000000007
    #define MAX(a,b) ((a) > (b) ? (a) : (b))
    
    // Helper function to find the maximum gap in the fences
    int findMaxGap(int* fences, int size, int limit) {
        // Sort the fences
        qsort(fences, size, sizeof(int), (int (*)(const void*, const void*))strcmp);
        
        int maxGap = 0;
        int prev = 1; // Start from the boundary fence
        
        for (int i = 0; i < size; i++) {
            maxGap = MAX(maxGap, fences[i] - prev);
            prev = fences[i];
        }
        
        // Check the gap between the last fence and the boundary fence
        maxGap = MAX(maxGap, limit - prev);
        
        return maxGap;
    }
    
    // Find maximum gaps for horizontal and vertical fences
    int maxHGap = findMaxGap(hFences, hFencesSize, m);
    int maxVGap = findMaxGap(vFences, vFencesSize, n);
    
    // The side of the largest square is the minimum of the two maximum gaps
    long long side = (long long)MAX(maxHGap, maxVGap);
    return (int)((side * side) % MOD);
    
}
