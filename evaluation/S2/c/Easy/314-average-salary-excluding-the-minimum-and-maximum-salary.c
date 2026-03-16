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
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

double average(int* salary, int salarySize) {
    if (salarySize < 3) {
        return 0.0; // Not enough employees to calculate average
    }

    int minSalary = salary[0];
    int maxSalary = salary[0];
    int sum = 0;

    for (int i = 0; i < salarySize; i++) {
        if (salary[i] < minSalary) {
            minSalary = salary[i];
        }
        if (salary[i] > maxSalary) {
            maxSalary = salary[i];
        }
        sum += salary[i];
    }

    // Exclude min and max salaries from the sum and calculate the average
    return (double)(sum - minSalary - maxSalary) / (salarySize - 2);        
}
