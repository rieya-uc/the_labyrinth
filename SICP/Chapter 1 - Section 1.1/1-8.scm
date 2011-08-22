;; Exercise 1.8.  
;; Newton's method for cube roots is based on the fact that if y is an 
;; approximation to the cube root of x, then a better approximation is 
;; given by the value 
;;           [omitted - check the sicp online text]

;; Use this formula to implement a cube-root procedure analogous to the 
;; square-root procedure.


(define (square x)
  (* x x))

(define (cube x)
  (* x x x))

(define (improve-guess guess x)
  (/ (+ (/ x (square guess)) 
        (* 2 guess))
     3))

(define (perc n x)
  (* (/ n x) 100))

(define (good-enough? guess x)
  (< (perc (abs (- (cube guess) x)) guess) 0.001))

(define (cube-root x)
  (cube-root-iter 1.0 x))

(define (cube-root-iter guess x)
  (if (good-enough? guess x)
    guess
    (cube-root-iter (improve-guess guess x) x)))



