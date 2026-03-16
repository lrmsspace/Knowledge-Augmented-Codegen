// Source: https://leetcode.com/problems/smallest-sufficient-team/   |   Difficulty: Hard
//
// Problem Description:
// In a project, you have a list of required skills req_skills, and a list of people. The ith person people[i] contains a list of skills that the person has.
//
// Consider a sufficient team: a set of people such that for every required skill in req_skills, there is at least one person in the team who has that skill. We can represent these teams by the index of each person.
//
//
// 	For example, team = [0, 1, 3] represents the people with skills people[0], people[1], and people[3].
//
//
// Return any sufficient team of the smallest possible size, represented by the index of each person. You may return the answer in any order.
//
// It is guaranteed an answer exists.
//
// Example:
// Input: req_skills = ["java","nodejs","reactjs"], people = [["java"],["nodejs"],["nodejs","reactjs"]]
// Output: [0,2]
//
// Constraints:
// 1 <= req_skills.length <= 16
// 	1 <= req_skills[i].length <= 16
// 	req_skills[i] consists of lowercase English letters.
// 	All the strings of req_skills are unique.
// 	1 <= people.length <= 60
// 	0 <= people[i].length <= 16
// 	1 <= people[i][j].length <= 16
// 	people[i][j] consists of lowercase English letters.
// 	All the strings of people[i] are unique.
// 	Every skill in people[i] is a skill in req_skills.
// 	It is guaranteed a sufficient team exists.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int[] smallestSufficientTeam(String[] req_skills, List<List<String>> people) {
        int m = req_skills.length, n = people.size();
        Map<String, Integer> skillIndex = new HashMap<>();
        for (int i = 0; i < m; i++) {
            skillIndex.put(req_skills[i], i);
        }

        int[] dp = new int[1 << m];
        Arrays.fill(dp, -1);
        dp[0] = 0;

        for (int i = 0; i < n; i++) {
            int skillMask = 0;
            for (String skill : people.get(i)) {
                if (skillIndex.containsKey(skill)) {
                    skillMask |= 1 << skillIndex.get(skill);
                }
            }

            for (int j = 0; j < (1 << m); j++) {
                if (dp[j] == -1) continue;
                int newMask = j | skillMask;
                if (dp[newMask] == -1 || Integer.bitCount(dp[newMask]) > Integer.bitCount(dp[j]) + 1) {
                    dp[newMask] = dp[j] | (1 << i);
                }
            }
        }

        int teamMask = dp[(1 << m) - 1];
        List<Integer> team = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            if ((teamMask & (1 << i)) != 0) {
                team.add(i);
            }
        }

        return team.stream().mapToInt(i -> i).toArray();            
    }
}
