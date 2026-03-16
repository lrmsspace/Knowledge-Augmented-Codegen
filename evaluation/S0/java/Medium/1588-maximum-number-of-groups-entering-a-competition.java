// Source: https://leetcode.com/problems/maximum-number-of-groups-entering-a-competition/   |   Difficulty: Medium
//
// Problem Description:
// You are given a positive integer array grades which represents the grades of students in a university. You would like to enter all these students into a competition in ordered non-empty groups, such that the ordering meets the following conditions:
//
//
// 	The sum of the grades of students in the ith group is less than the sum of the grades of students in the (i + 1)th group, for all groups (except the last).
// 	The total number of students in the ith group is less than the total number of students in the (i + 1)th group, for all groups (except the last).
//
//
// Return the maximum number of groups that can be formed.
//
// Example:
// Input: grades = [10,6,12,7,3,5]
// Output: 3
// Explanation: The following is a possible way to form 3 groups of students:
// - 1st group has the students with grades = [12]. Sum of grades: 12. Student count: 1
// - 2nd group has the students with grades = [6,7]. Sum of grades: 6 + 7 = 13. Student count: 2
// - 3rd group has the students with grades = [10,3,5]. Sum of grades: 10 + 3 + 5 = 18. Student count: 3
// It can be shown that it is not possible to form more than 3 groups.
//
// Constraints:
// 1 <= grades.length <= 105
// 	1 <= grades[i] <= 105
//

class Solution {
    public int maximumGroups(int[] grades) {
        int n = grades.length;
        int groups = 0;
        int studentsInCurrentGroup = 0;

        while (n >= studentsInCurrentGroup + 1) {
            studentsInCurrentGroup++;
            groups++;
            n -= studentsInCurrentGroup;
        }

        return groups;          
    }
}
