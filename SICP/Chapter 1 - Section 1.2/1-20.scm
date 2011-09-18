;; Exercise 1.20.  
;; The process that a procedure generates is of course dependent on the rules 
;; used by the interpreter. As an example, consider the iterative gcd 
;; procedure given above. Suppose we were to interpret this procedure using 
;; normal-order evaluation, as discussed in section 1.1.5. 
;; (The normal-order-evaluation rule for if is described in exercise 1.5.) 
;; Using the substitution method (for normal order), illustrate the process 
;; generated in evaluating (gcd 206 40) and indicate the remainder operations 
;; that are actually performed. How many remainder operations are actually 
;; performed in the normal-order evaluation of (gcd 206 40)? 
;; In the applicative-order evaluation? 

(define (gcd a b)
  (if (= b 0)
      a
      (gcd b (remainder a b))))

;; Applicative order first, because it's shorter
(gcd 206 40)
(gcd 40 (remainder 206 40))
(gcd 40 6)
(gcd 6 (remainder 40 6))
(gcd 6 4)
(gcd 4 (remainder 6 4))
(gcd 4 2)
(gcd 2 (remainder 4 2))
(gcd 2 0)
2

Total remainders: 4


;; Normal order
Using the shorthand:
   r to equal the number of times remainder has been called 
   in the current iteration
   t to equal total number of times remainder has been called
Note that the remainders are called during the "if (= b 0)" part of the
procedure.

(gcd 206 40) 
[a=206, b=40, remainders called=0, total remainders=0]

(gcd 40 (remainder 206 40))
[a=40, b=6, r=1, t=1]

(gcd (remainder 206 40)
     (remainder 40 (remainder 206 40)))
[b=4, r=2, t=3]

(gcd (remainder 40 (remainder 206 40))
     (remainder (remainder 206 40) (remainder 40 (remainder 206 40))))
[b=2, r=4, t=7]

(gcd  (remainder (remainder 206 40) (remainder 40 (remainder 206 40)
      (remainder (remainder 40 (remainder 206 40))                            
                 (remainder (remainder 206 40) (remainder 40 (remainder 206 40)
                                                          ))))))
[b=0 (finally!), r=7, t=14]

(remainder (remainder 206 40) (remainder 40 (remainder 206 40)
(remainder (remainder 206 40) (remainder 40 6))
(remainder (remainder 206 40) 4)
(remainder 6 4)
2

Total remainders: 18

