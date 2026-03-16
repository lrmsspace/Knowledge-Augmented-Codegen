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
    public List<Integer> topStudents(String[] positive_feedback, String[] negative_feedback, String[] report, int[] student_id, int k) {
        Set<String> positiveSet = new HashSet<>(Arrays.asList(positive_feedback));
        Set<String> negativeSet = new HashSet<>(Arrays.asList(negative_feedback));

        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> {
            if (a[1] != b[1]) {
                return Integer.compare(b[1], a[1]); // Higher score first
            } else {
                return Integer.compare(a[0], b[0]); // Lower ID first
            }
        });

        for (int i = 0; i < report.length; i++) {
            String[] words = report[i].split(" ");
            int score = 0;

            for (String word : words) {
                if (positiveSet.contains(word)) {
                    score += 3;
                } else if (negativeSet.contains(word)) {
                    score -= 1;
                }
            }

            pq.offer(new int[]{student_id[i], score});
        }

        List<Integer> result = new ArrayList<>();
        for (int i = 0; i < k; i++) {
            result.add(pq.poll()[0]);
        }

        return result;          
    }
}
