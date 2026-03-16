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
    public double average(int[] salary) {
        int min = Integer.MAX_VALUE;
        int max = Integer.MIN_VALUE;
        int sum = 0;

        for (int s : salary) {
            sum += s;
            if (s < min) {
                min = s;
            }
            if (s > max) {
                max = s;
            }
        }

        sum = sum - min - max;
        return (double) sum / (salary.length - 2);          
    }
}
