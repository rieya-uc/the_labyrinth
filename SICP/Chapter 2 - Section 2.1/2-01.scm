;; Exercise 2.1.  
;; Define a better version of make-rat that handles both positive and 
;; negative arguments. Make-rat should normalize the sign so that if 
;; the rational number is positive, both the numerator and denominator
;; are positive, and if the rational number is negative, only the 
;; numerator is negative. 

;;(define (make-rat n d) 
;;  (if (< d 0)
;;      (cons (* -1 n) (* -1 d))
;;      (cons n d)))

(define (make-rat n d)
  (let ((g (gcd n d)))
    (if (< d 0)
        (cons (* -1 (/ n g)) (* -1 (/ d g)))
        (cons (/ n g) (/ d g)))))

(define (numer x) (car x))

(define (denom x) (cdr x))

(define (print-rat x)
  (newline)
  (display (numer x))
  (display "/")
  (display (denom x)))

(print-rat (make-rat 30 -40))
(print-rat (make-rat -3 -4))
(print-rat (make-rat 3 4))
(print-rat (make-rat -3 4))