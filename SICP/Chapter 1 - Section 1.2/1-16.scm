;; Exercise 1.16.  
;; Design a procedure that evolves an iterative exponentiation process that 
;; uses successive squaring and uses a logarithmic number of steps, as 
;; does fast-expt.

(define (square x)
  (* x x))

(define (even? n)
  (= (remainder n 2) 0))
      
(define (fast-expt b n)
  (fast-expt-h b n 1))

;; doesn't do any checks for negative powers
(define (fast-expt-h b n a)
  (cond ((= n 0) a)
        ((even? n) (fast-expt-h (square b) (/ n 2) a))
        (else (fast-expt-h b (- n 1) (* b a)))))


