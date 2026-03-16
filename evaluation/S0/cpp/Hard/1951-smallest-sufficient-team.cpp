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
public:
    vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people) {
        int n = req_skills.size();
        int m = people.size();
        unordered_map<string, int> skillIndex;
        for (int i = 0; i < n; i++) {
            skillIndex[req_skills[i]] = i;
        }
        
        vector<int> personSkills(m, 0);
        for (int i = 0; i < m; i++) {
            for (const string& skill : people[i]) {
                if (skillIndex.count(skill)) {
                    personSkills[i] |= (1 << skillIndex[skill]);
                }
            }
        }
        
        vector<vector<int>> dp(1 << n, vector<int>());
        dp[0] = {};
        
        for (int i = 0; i < m; i++) {
            int pSkill = personSkills[i];
            if (pSkill == 0) continue;
            
            for (int skillSet = 0; skillSet < (1 << n); skillSet++) {
                if (dp[skillSet].empty() && skillSet != 0) continue;
                
                int newSkillSet = skillSet | pSkill;
                if (dp[newSkillSet].empty() || dp[newSkillSet].size() > dp[skillSet].size() + 1) {
                    dp[newSkillSet] = dp[skillSet];
                    dp[newSkillSet].push_back(i);
                }
            }
        }
        
        return dp[(1 << n) - 1];            
    }
};
