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

class Solution {
    public int[] smallestSufficientTeam(String[] req_skills, List<List<String>> people) {
        int n = req_skills.length;
        int m = people.size();

        Map<String, Integer> skillIndex = new HashMap<>();
        for (int i = 0; i < n; i++) {
            skillIndex.put(req_skills[i], i);
        }

        int[] personSkills = new int[m];
        for (int i = 0; i < m; i++) {
            for (String skill : people.get(i)) {
                if (skillIndex.containsKey(skill)) {
                    personSkills[i] |= (1 << skillIndex.get(skill));
                }
            }
        }

        int fullSkillSet = (1 << n) - 1;
        int[][] dp = new int[1 << n][];
        dp[0] = new int[0];

        for (int skillSet = 0; skillSet <= fullSkillSet; skillSet++) {
            if (dp[skillSet] == null) continue;

            for (int i = 0; i < m; i++) {
                int newSkillSet = skillSet | personSkills[i];
                if (newSkillSet == skillSet) continue;

                if (dp[newSkillSet] == null || dp[newSkillSet].length > dp[skillSet].length + 1) {
                    dp[newSkillSet] = Arrays.copyOf(dp[skillSet], dp[skillSet].length + 1);
                    dp[newSkillSet][dp[skillSet].length] = i;
                }
            }
        }

        return dp[fullSkillSet];                    
    }
}
