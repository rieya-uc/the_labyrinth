;; Exercise 1.27.  
;; Demonstrate that the Carmichael numbers listed in footnote 47 
;; really do fool the Fermat test. That is, write a procedure that
;; takes an integer n and tests whether an is congruent to a modulo n 
;; for every a<n, and try your procedure on the given Carmichael numbers. 

;; Reminder: the Fermat test.
;; Fermat's Little Theorem: If n is a prime number and a is any positive
;; integer less than n, then a raised to the nth power is congruent to a 
;; modulo n.

;; Carmichael numbers: Numbers that fool Fermat's test.
;; The smallest few are 561, 1105, 1729, 2465, 2821, and 6601.


;; I could probably start testing at n/2
(define (fermat-test n)
  (define (fermat-test-all a)
    (cond 
      ((= a 0) #t)
      ((= a (expmod a n n)) (fermat-test-all (- a 1)))
      (else #f)))
  (fermat-test-all (- n 1)))

(define (expmod base exp m)
  (cond ((= exp 0) 1)
        ((even? exp)
         (remainder (square (expmod base (/ exp 2) m))
                    m))
        (else
         (remainder (* base (expmod base (- exp 1) m))
                    m)))) 

(define (square n)
  (* n n))
