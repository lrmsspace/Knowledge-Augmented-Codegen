// Source: https://leetcode.com/problems/reward-top-k-students/   |   Difficulty: Medium
//
// Problem Description:
// You are given two string arrays positive_feedback and negative_feedback, containing the words denoting positive and negative feedback, respectively. Note that no word is both positive and negative.
//
// Initially every student has 0 points. Each positive word in a feedback report increases the points of a student by 3, whereas each negative word decreases the points by 1.
//
// You are given n feedback reports, represented by a 0-indexed string array report and a 0-indexed integer array student_id, where student_id[i] represents the ID of the student who has received the feedback report report[i]. The ID of each student is unique.
//
// Given an integer k, return the top k students after ranking them in non-increasing order by their points. In case more than one student has the same points, the one with the lower ID ranks higher.
//
// Example:
// Input: positive_feedback = ["smart","brilliant","studious"], negative_feedback = ["not"], report = ["this student is studious","the student is smart"], student_id = [1,2], k = 2
// Output: [1,2]
// Explanation: 
// Both the students have 1 positive feedback and 3 points but since student 1 has a lower ID he ranks higher.
//
// Constraints:
// 1 <= positive_feedback.length, negative_feedback.length <= 104
// 	1 <= positive_feedback[i].length, negative_feedback[j].length <= 100
// 	Both positive_feedback[i] and negative_feedback[j] consists of lowercase English letters.
// 	No word is present in both positive_feedback and negative_feedback.
// 	n == report.length == student_id.length
// 	1 <= n <= 104
// 	report[i] consists of lowercase English letters and spaces ' '.
// 	There is a single space between consecutive words of report[i].
// 	1 <= report[i].length <= 100
// 	1 <= student_id[i] <= 109
// 	All the values of student_id[i] are unique.
// 	1 <= k <= n
//

class Solution {
public:
    vector<int> topStudents(vector<string>& positive_feedback, vector<string>& negative_feedback, vector<string>& report, vector<int>& student_id, int k) {
        unordered_set<string> posSet(positive_feedback.begin(), positive_feedback.end());
        unordered_set<string> negSet(negative_feedback.begin(), negative_feedback.end());

        vector<pair<int, int>> scores; // (score, student_id)

        for (int i = 0; i < report.size(); ++i) {
            istringstream iss(report[i]);
            string word;
            int score = 0;

            while (iss >> word) {
                if (posSet.count(word)) {
                    score += 3;
                } else if (negSet.count(word)) {
                    score -= 1;
                }
            }

            scores.emplace_back(score, student_id[i]);
        }

        sort(scores.begin(), scores.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            if (a.first != b.first) {
                return a.first > b.first; // Higher score first
            }
            return a.second < b.second; // Lower student_id first
        });

        vector<int> result;
        for (int i = 0; i < k; ++i) {
            result.push_back(scores[i].second);
        }

        return result;          
    }
};
