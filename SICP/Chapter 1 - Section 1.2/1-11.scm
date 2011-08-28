;; Exercise 1.11.  
;; A function f is defined by the rule that 
;; f(n) = n if n<3 and f(n) = f(n - 1) + 2f(n - 2) + 3f(n - 3) if n> 3. 
;; Write a procedure that computes f by means of a recursive process.
;; Write a procedure that computes f by means of an iterative process. 

;; Recursive
(define (f-recur n)
  (cond ((< n 3) n)
        (else (+ (f-recur (- n 1))
                 (* 2 (f-recur (- n 2)))
                 (* 3 (f-recur (- n 3)))))))


;; Iterative
(define (f-iter n)
  (f-iter-helper 2 1 0 n))

(define (f-iter-helper a b c count)
  (if (< count 3)
       a 
      (f-iter-helper (+ a (* 2 b) (* 3 c))
                     a
                     b
                     (- count 1))))
					 
Here's a tip for working out an iterative solution; start from the base case
and move up the sequence. Work out how to calculate the next number, store 
this in the variable of the newest (highest) number and don't forget to 
update the numbers when you call the next iteration.
E.g. for the above, we have 0, 1, 2, (2 + (2*1) + (3*0)), ...etc, 
Pass the calculated value as the argument a, and pass the old a and b as 
b and c.

                     
                    



        



