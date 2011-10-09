;; Exercise 1.40.  
;; Define a procedure cubic that can be used together with the newtons-method
;; procedure in expressions of the form

;; (newtons-method (cubic a b c) 1)

;; to approximate zeros of the cubic x^3 + ax^2 + bx + c.

;; Newton's Method
;; If we have a function f(x) and its derivative f'(x) then
;; we can find roots by repeated by firstly guessing with a 
;; value x0, then improving the guess by applying 
;; x(n+1) = xn - [f(xn) / f'(xn)] ('n' meant to be subscript...)

(define (cubic a b c)
  (lambda (x)
    (+ (cube x) (* a (square x)) (* b x) c)))

;; To put it another way, if we have the equation
;; 0 = x^3 + ax^2 + bx + c
;; e.g. 0 = x^3 + 2x^2 + 3x - 6
;; what is the value of x?
;;(In this case, x is 1)

;; > (newtons-method (cubic 2 3 -6) 1)
;; > 1

(define tolerance 0.00001)
(define (fixed-point f first-guess)
  (define (close-enough? v1 v2)
    (< (abs (- v1 v2)) tolerance))
  (define (try guess)
    (let ((next (f guess)))
      (if (close-enough? guess next)
          next
          (try next))))
  (try first-guess))
(define (close-enough? x y)
  (< (abs (- x y)) 0.001))

(define dx 0.000001)
(define (deriv g)
  (lambda (x)
    (/ (- (g (+ x dx)) (g x))
       dx)))

(define (newton-transform g)
  (lambda (x)
    (- x (/ (g x) ((deriv g) x)))))
(define (newtons-method g guess)
  (fixed-point (newton-transform g) guess))

(define (cube x)
  (* x x x))

(define (square x)
  (* x x))


