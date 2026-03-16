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

double average(int* salary, int salarySize) {
    int min = salary[0];
    int max = salary[0];
    int sum = 0;
    
    for (int i = 0; i < salarySize; i++) {
        if (salary[i] < min) {
            min = salary[i];
        }
        if (salary[i] > max) {
            max = salary[i];
        }
        sum += salary[i];
    }
    
    sum -= (min + max);
    
    return (double)sum / (salarySize - 2);      
}
