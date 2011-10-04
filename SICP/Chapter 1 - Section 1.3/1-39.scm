;; Exercise 1.39.  
;; A continued fraction representation of the tangent function was published 
;; in 1770 by the German mathematician J.H. Lambert:
   ;; [omitted]
;; where x is in radians. Define a procedure (tan-cf x k) that computes an 
;; approximation to the tangent function based on Lambert's formula. 
;; K specifies the number of terms to compute, as in exercise 1.37.

(define (cont-frac n d k)
  (define (helper i)
    (if (= i k)
        (/ (n i) (d i))
        (+ (d i) (/ (n (+ i 1)) (helper (+ i 1))))))
  (/ (n 1) (helper 1)))

(define (tan-cf x k)
  (define (n i)
    (if (= i 1)
        x
        (-(* x x))))
  (define (d i)
    (- (* i 2) 1))
  (cont-frac n d k))
  