;; Exercise 1.18.  
;; Using the results of exercises 1.16 and 1.17, devise a procedure that 
;; generates an iterative process for multiplying two integers in terms 
;; of adding, doubling, and halving and uses a logarithmic number of steps

(define (double n)
  (* 2 n))

(define (halve n)
  (/ n 2))

(define (even? n)
  (= (remainder n 2) 0))

;; iterative version
(define (fast-* a b)
  (fast-*-h a b 0))

(define (fast-*-h a b x)
  (cond ((= b 0) x)
        ((even? b) (fast-*-h (double a) (halve b) x))
        (else (fast-*-h a (- b 1) (+ x a)))))
