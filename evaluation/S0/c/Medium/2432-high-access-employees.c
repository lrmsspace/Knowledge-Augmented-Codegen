// Source: https://leetcode.com/problems/high-access-employees/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D 0-indexed array of strings, access_times, with size n. For each i where 0 <= i <= n - 1, access_times[i][0] represents the name of an employee, and access_times[i][1] represents the access time of that employee. All entries in access_times are within the same day.
//
// The access time is represented as four digits using a 24-hour time format, for example, "0800" or "2250".
//
// An employee is said to be high-access if he has accessed the system three or more times within a one-hour period.
//
// Times with exactly one hour of difference are not considered part of the same one-hour period. For example, "0815" and "0915" are not part of the same one-hour period.
//
// Access times at the start and end of the day are not counted within the same one-hour period. For example, "0005" and "2350" are not part of the same one-hour period.
//
// Return a list that contains the names of high-access employees with any order you want.
//
// Example:
// Input: access_times = [["a","0549"],["b","0457"],["a","0532"],["a","0621"],["b","0540"]]
// Output: ["a"]
// Explanation: "a" has three access times in the one-hour period of [05:32, 06:31] which are 05:32, 05:49, and 06:21.
// But "b" does not have more than two access times at all.
// So the answer is ["a"].
//
// Constraints:
// 1 <= access_times.length <= 100
// 	access_times[i].length == 2
// 	1 <= access_times[i][0].length <= 10
// 	access_times[i][0] consists only of English small letters.
// 	access_times[i][1].length == 4
// 	access_times[i][1] is in 24-hour time format.
// 	access_times[i][1] consists only of '0' to '9'.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** findHighAccessEmployees(char*** access_times, int access_timesSize, int* access_timesColSize, int* returnSize) {
    #define MAX_EMPLOYEES 100
    #define MAX_TIMES 100

    typedef struct {
        char* name;
        int times[MAX_TIMES];
        int timeCount;
    } Employee;

    Employee employees[MAX_EMPLOYEES];
    int employeeCount = 0;

    // Function to convert time string to minutes
    int timeToMinutes(char* timeStr) {
        int hours = (timeStr[0] - '0') * 10 + (timeStr[1] - '0');
        int minutes = (timeStr[2] - '0') * 10 + (timeStr[3] - '0');
        return hours * 60 + minutes;
    }

    // Populate employees array
    for (int i = 0; i < access_timesSize; i++) {
        char* name = access_times[i][0];
        char* timeStr = access_times[i][1];
        int timeInMinutes = timeToMinutes(timeStr);

        // Find or add employee
        int found = 0;
        for (int j = 0; j < employeeCount; j++) {
            if (strcmp(employees[j].name, name) == 0) {
                employees[j].times[employees[j].timeCount++] = timeInMinutes;
                found = 1;
                break;
            }
        }
        if (!found) {
            employees[employeeCount].name = name;
            employees[employeeCount].times[0] = timeInMinutes;
            employees[employeeCount].timeCount = 1;
            employeeCount++;
        }
    }

    // Check for high-access employees
    char** result = (char**)malloc(MAX_EMPLOYEES * sizeof(char*));
    int count = 0;

    for (int i = 0; i < employeeCount; i++) {
        // Sort access times
        qsort(employees[i].times, employees[i].timeCount, sizeof(int), (int (*)(const void*, const void*))strcmp);

        // Check for three accesses within one hour
        for (int j = 0; j <= employees[i].timeCount - 3; j++) {
            if (employees[i].times[j + 2] - employees[i].times[j] < 60) {
                result[count++] = employees[i].name;
                break;
            }
        }

}
    *returnSize = count;
    return result;  
}