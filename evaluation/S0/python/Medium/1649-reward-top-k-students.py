# Source: https://leetcode.com/problems/reward-top-k-students/   |   Difficulty: Medium
#
# Problem Description:
# You are given two string arrays positive_feedback and negative_feedback, containing the words denoting positive and negative feedback, respectively. Note that no word is both positive and negative.
#
# Initially every student has 0 points. Each positive word in a feedback report increases the points of a student by 3, whereas each negative word decreases the points by 1.
#
# You are given n feedback reports, represented by a 0-indexed string array report and a 0-indexed integer array student_id, where student_id[i] represents the ID of the student who has received the feedback report report[i]. The ID of each student is unique.
#
# Given an integer k, return the top k students after ranking them in non-increasing order by their points. In case more than one student has the same points, the one with the lower ID ranks higher.
#
# Example:
# Input: positive_feedback = ["smart","brilliant","studious"], negative_feedback = ["not"], report = ["this student is studious","the student is smart"], student_id = [1,2], k = 2
# Output: [1,2]
# Explanation: 
# Both the students have 1 positive feedback and 3 points but since student 1 has a lower ID he ranks higher.
#
# Constraints:
# 1 <= positive_feedback.length, negative_feedback.length <= 104
# 	1 <= positive_feedback[i].length, negative_feedback[j].length <= 100
# 	Both positive_feedback[i] and negative_feedback[j] consists of lowercase English letters.
# 	No word is present in both positive_feedback and negative_feedback.
# 	n == report.length == student_id.length
# 	1 <= n <= 104
# 	report[i] consists of lowercase English letters and spaces ' '.
# 	There is a single space between consecutive words of report[i].
# 	1 <= report[i].length <= 100
# 	1 <= student_id[i] <= 109
# 	All the values of student_id[i] are unique.
# 	1 <= k <= n
#

class Solution(object):
    def topStudents(self, positive_feedback, negative_feedback, report, student_id, k):
        """
        :type positive_feedback: List[str]
        :type negative_feedback: List[str]
        :type report: List[str]
        :type student_id: List[int]
        :type k: int
        :rtype: List[int]
        """
        pos_set = set(positive_feedback)
        neg_set = set(negative_feedback)
        
        scores = {}
        
        for i in range(len(report)):
            rep = report[i].split()
            sid = student_id[i]
            score = 0
            for word in rep:
                if word in pos_set:
                    score += 3
                elif word in neg_set:
                    score -= 1
            scores[sid] = score
        
        # Sort by score (descending) and then by student_id (ascending)
        sorted_students = sorted(scores.items(), key=lambda x: (-x[1], x[0]))
        
        # Extract the top k student IDs
        top_k_students = [student[0] for student in sorted_students[:k]]
        
        return top_k_students