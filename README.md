# Essentials of Artificial Intelligence
# Smart Exam Scheduler System Summary
- Resource : 
  - 10 exams {E1, E2, E3, …, E10}
  - 4 Time = {t1, t2, t3, t4}
  - 3 Hole = {hA, hB, hC} 

- Goal test :
  - Assign a hall and a time slot for each exam.

- Variables :
  - Time and hole for each exam.
  - Ei(T,H)  i = order of the exam = {1,2,3,….,10}

- Domains :
  - i = order of the exam = {1,2,3,….,10}
  - Time(i) = { 1, 2, 3, 4 }
  - Hole(i) = {A, B, C}

- Constraints :  
  - Constraint 1 : The 1st exam should take place before the third exam.
    - Implicit : Time(1) < Time(3)
    - Explicit : (T(1), T(3))  { (1,2), (1,3), (1,4), (2,3), (2,4), (3,4) } 

  - Constraint 2 :The 10th exam occurs after the 9th and 4th exams.
    - Implicit : Time(10) > Time(9) && Time(10) > Time(4)
    - Explicit : (T(10), T(9), T(4))  { (2,1,1), (3,1,1), (3,1,2), (3,2,1), (3,2,2), (4,1,1), (4,1,2), (4,1,3), (4,2,1), (4,2,2), (4,2,3), (4,3,1), (4,3,2), (4,3,3) }


  - Constraint 3 : The 1st, 3rd, and 4th exams should take place in 					either Hall A or Hall C.
    - Implicit : Hole(1) && Hole(3) && Hole(4) !=’B’
    - Explicit : (H(1), H(3), H(4))  { (A, A, A), (C, C, C) } 

  - Constraint 4 : The 7th, 8th, 9th, and 10th exams should be in 					either Hall A or Hall B.
    - Implicit : Hole(7) && Hole(8) && Hole(9) && Hole(10) !=’C’
    - Explicit : (H(7), H(8), H(9), H(10))  { (A, A, A, A), (B, B, B, B) } 

  - Constraint 5 : There are no two exams occur at the same place and 				time.
    - Implicit : ETH(i) != ETH(i+1)

I use backtracking search in solving CSP.
Backtracking technique :
- Filtering : 
	- cross off bad option from each exam domain.
- Ordering : 
	- variable ordering.
- Structure : 
	- I split the exams according to time constraints to 2 graphs :
		- Graph 1 : exam 1st, 3rd, 4th, 9th and 10th.
		- Graph 2 : exam 2nd, 5th, 6th, 7th and 8th.
	Each exam inserts the graph according to the minimum remaining value from domain.
  
E1 | E2 | E3 | E4 | E5 | E6 | E7 | E8 | E9 | E10  
6 | 6 | 6 | 6 | 6 | 12 | 12 | 12 | 8 | 8 
