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

class Solution {
    public List<String> findHighAccessEmployees(List<List<String>> access_times) {
        Map<String, List<Integer>> accessMap = new HashMap<>();
        Set<String> resultSet = new HashSet<>();

        // Convert access times to minutes and group by employee name
        for (List<String> entry : access_times) {
            String name = entry.get(0);
            String timeStr = entry.get(1);
            int hours = Integer.parseInt(timeStr.substring(0, 2));
            int minutes = Integer.parseInt(timeStr.substring(2, 4));
            int totalMinutes = hours * 60 + minutes;

            accessMap.putIfAbsent(name, new ArrayList<>());
            accessMap.get(name).add(totalMinutes);
        }

        // Check each employee's access times for high-access criteria
        for (Map.Entry<String, List<Integer>> entry : accessMap.entrySet()) {
            String name = entry.getKey();
            List<Integer> times = entry.getValue();
            Collections.sort(times);

            for (int i = 0; i <= times.size() - 3; i++) {
                if (times.get(i + 2) - times.get(i) < 60) {
                    resultSet.add(name);
                    break;
                }
            }
        }

        return new ArrayList<>(resultSet);          
    }
}
