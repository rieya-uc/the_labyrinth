;; Exercise 2.35.  
;; Redefine count-leaves from section 2.2.2 as an accumulation:

(define (atom? x) (not (pair? x)))

(define (accumulate op initial sequence)
  (if (null? sequence)
      initial
      (op (car sequence) (accumulate op initial (cdr sequence)))))

(define (count-leaves t)
  (accumulate + 0 (map (lambda (x)
                            (cond ((null? x) 0)
                                  ((atom? x) 1)
                                  (else (count-leaves x))))
                       t)))


(count-leaves '(1 (2 3) (4 (5 6) 7) ((8))))
(count-leaves '((((1)))))
(count-leaves '())
