// Source: https://leetcode.com/problems/average-salary-excluding-the-minimum-and-maximum-salary/   |   Difficulty: Easy
//
// Problem Description:
// You are given an array of unique integers salary where salary[i] is the salary of the ith employee.
//
// Return the average salary of employees excluding the minimum and maximum salary. Answers within 10-5 of the actual answer will be accepted.
//
// Example:
// Input: salary = [4000,3000,1000,2000]
// Output: 2500.00000
// Explanation: Minimum salary and maximum salary are 1000 and 4000 respectively.
// Average salary excluding minimum and maximum salary is (2000+3000) / 2 = 2500
//
// Constraints:
// 3 <= salary.length <= 100
// 	1000 <= salary[i] <= 106
// 	All the integers of salary are unique.
//

class Solution {
public:
    double average(vector<int>& salary) {
        int minSalary = INT_MAX;
        int maxSalary = INT_MIN;
        int totalSalary = 0;

        for (int s : salary) {
            minSalary = min(minSalary, s);
            maxSalary = max(maxSalary, s);
            totalSalary += s;
        }

        totalSalary -= (minSalary + maxSalary);
        double averageSalary = static_cast<double>(totalSalary) / (salary.size() - 2);

        return averageSalary;           
    }
};
