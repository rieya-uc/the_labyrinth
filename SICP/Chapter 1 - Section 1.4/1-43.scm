;; Exercise 1.43.  
;; If f is a numerical function and n is a positive integer, then we can form 
;; the nth repeated application of f, which is defined to be the function 
;; whose value at x is f(f(...(f(x))...)). For example, if f is the 
;; function x->x + 1, then the nth repeated application of f is the 
;; function x->x + n. If f is the operation of squaring a number, then the 
;; nth repeated application of f is the function that raises its argument 
;; to the 2^nth power. Write a procedure that takes as inputs a procedure 
;; that computes f and a positive integer n and returns the procedure that
;; computes the nth repeated application of f. Your procedure should be able
;; to be used as follows:

;; ((repeated square 2) 5)
;; 625

;; Hint: You may find it convenient to use compose from exercise 1.42. 

(define (compose f g)
  (lambda (x)
    (f (g x))))

(define (repeated f n)
    (define (helper g i)
      (if (= i n)
          g
          (helper (compose f g)  (+ i 1))))
    (helper f 1))

(define (square n)
  (* n n))

((repeated square 2) 5)