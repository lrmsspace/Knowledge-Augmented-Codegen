// Source: https://leetcode.com/problems/compare-version-numbers/   |   Difficulty: Medium
//
// Problem Description:
// Given two version strings, version1 and version2, compare them. A version string consists of revisions separated by dots '.'. The value of the revision is its integer conversion ignoring leading zeros.
//
// To compare version strings, compare their revision values in left-to-right order. If one of the version strings has fewer revisions, treat the missing revision values as 0.
//
// Return the following:
//
//
// 	If version1 < version2, return -1.
// 	If version1 > version2, return 1.
// 	Otherwise, return 0.
//
// Example:
// Input: version1 = "1.2", version2 = "1.10"
//
// Output: -1
//
// Explanation:
//
// version1's second revision is "2" and version2's second revision is "10": 2 < 10, so version1 < version2.
//
// Constraints:
// 1 <= version1.length, version2.length <= 500
// 	version1 and version2 only contain digits and '.'.
// 	version1 and version2 are valid version numbers.
// 	All the given revisions in version1 and version2 can be stored in a 32-bit integer.
//

class Solution {
public:
    int compareVersion(string version1, string version2) {
        int n1 = version1.size();
        int n2 = version2.size();
        int i = 0, j = 0;

        while (i < n1 || j < n2) {
            long rev1 = 0;
            while (i < n1 && version1[i] != '.') {
                rev1 = rev1 * 10 + (version1[i] - '0');
                i++;
            }
            i++; // skip the dot

            long rev2 = 0;
            while (j < n2 && version2[j] != '.') {
                rev2 = rev2 * 10 + (version2[j] - '0');
                j++;
            }
            j++; // skip the dot

            if (rev1 < rev2) return -1;
            if (rev1 > rev2) return 1;
        }

        return 0;           
    }
};
