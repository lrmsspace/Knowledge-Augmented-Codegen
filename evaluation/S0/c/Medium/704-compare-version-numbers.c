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

int compareVersion(char* version1, char* version2) {
    int v1 = 0, v2 = 0;
    char *p1 = version1, *p2 = version2;

    while (*p1 != '\0' || *p2 != '\0') {
        v1 = 0;
        v2 = 0;

        while (*p1 != '\0' && *p1 != '.') {
            v1 = v1 * 10 + (*p1 - '0');
            p1++;
        }

        while (*p2 != '\0' && *p2 != '.') {
            v2 = v2 * 10 + (*p2 - '0');
            p2++;
        }

        if (v1 < v2) {
            return -1;
        } else if (v1 > v2) {
            return 1;
        }

        if (*p1 == '.') {
            p1++;
        }
        if (*p2 == '.') {
            p2++;
        }
    }

    return 0;       
}
