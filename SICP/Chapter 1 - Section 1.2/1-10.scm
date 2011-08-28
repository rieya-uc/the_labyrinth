;; Exercise 1.10.  
;; The following procedure computes a mathematical function called 
;; Ackermann's function.

(define (A x y)
  (cond ((= y 0) 0)
        ((= x 0) (* 2 y))
        ((= y 1) 2)
        (else (A (- x 1)
                 (A x (- y 1))))))

;; What are the values of the following expressions?

(A 1 10)
> 1024

(A 2 4)
> 65536

(A 3 3)
> 65536

Consider the following procedures, where A is the procedure defined above:

(define (f n) (A 0 n))
(define (g n) (A 1 n))
(define (h n) (A 2 n))
(define (k n) (* 5 n n))

Give concise mathematical definitions for the functions computed by the 
procedures f, g, and h for positive integer values of n. 
For example, (k n) computes 5n2. 

(define (f n) (A 0 n))
This computes 2n

(define (g n) (A 1 n))
This computes 2^n

(define (h n) (A 2 n))
This computes 2^2^...^2 for n number of 2s. 
E.g. (A 2 5) = 2^2^2^2^2

