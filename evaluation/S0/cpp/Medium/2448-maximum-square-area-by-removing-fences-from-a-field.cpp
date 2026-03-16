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

class Solution {
public:
    int maximizeSquareArea(int m, int n, vector<int>& hFences, vector<int>& vFences) {
        const int MOD = 1e9 + 7;

        hFences.push_back(1);
        hFences.push_back(m);
        vFences.push_back(1);
        vFences.push_back(n);

        sort(hFences.begin(), hFences.end());
        sort(vFences.begin(), vFences.end());

        int maxHGap = 0;
        for (int i = 1; i < hFences.size(); ++i) {
            maxHGap = max(maxHGap, hFences[i] - hFences[i - 1]);
        }

        int maxVGap = 0;
        for (int i = 1; i < vFences.size(); ++i) {
            maxVGap = max(maxVGap, vFences[i] - vFences[i - 1]);
        }

        long long side = min(maxHGap - 1, maxVGap - 1);
        if (side <= 0) {
            return -1;
        }
        return side * side % MOD;           
    }
};
