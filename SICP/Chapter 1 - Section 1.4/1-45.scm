;; Exercise 1.45. 
;; We saw in section 1.3.3 that attempting to compute square roots by naively
;; finding a fixed point of y->x/y does not converge, and that this can be
;; fixed by average damping. The same method works for finding cube roots as
;; fixed points of the average-damped y->x/y2. Unfortunately, the process
;; does not work for fourth roots -- a single average damp is not enough 
;; to make a fixed-point search for y->x/y3 converge. On the other hand, if
;; we average damp twice (i.e., use the average damp of the average damp of
;; y->x/y3) the fixed-point search does converge. Do some experiments to 
;; determine how many average damps are required to compute nth roots as a
;; fixed-point search based upon repeated average damping of y->x/yn-1. 
;; Use this to implement a simple procedure for computing nth roots using
;; fixed-point, average-damp, and the repeated procedure of exercise 1.43.
;; Assume that any arithmetic operations you need are available as primitives. 

;; RESULTS
;; Root    4  5  6  7  8  9  10  11  12  13  14  15  16
;; Damping 2  2  1  1  3  3  3   3   3   3   3   3   4

;; Root    17  18  22  25  30  32  50  63  64
;; Damping 4   4   4   4   4   5   5   4   6

;; Apart from a few anomalies (???) it looks like the number of times 
;; average damping needs to be called goes up by one every power of 
;; two.
;; I.e. if n is the root and a is the number of average damping, 
;; 2^n = a, so 2^4 = 16 and 2^5 = 32, between 16th and 31st root damping is
;; 4, then at 32nd root it goes up to 5.
;; So to work out how many times we need to call damping for the nth root, 
;; floor(logn) = a

(define (repeated f n)
    (define (helper g i)
      (if (= i n)
          g
          (helper (compose f g)  (+ i 1))))
    (helper f 1))
(define (compose f g)
  (lambda (x)
    (f (g x))))

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

(define (square n)
  (* n n))

(define (^ b n)
  (cond ((= n 0) 1)
        ((even? n) (square (^ b (/ n 2))))
        (else (* b (^ b (- n 1))))))

(define (average a b)
  (/ (+ a b) 2))
(define (average-damp f)
  (lambda (x) (average x (f x))))

(define (sqrt x)
  (fixed-point (average-damp (lambda (y) (/ x y)))
               1.0))

(define (cube-root x)
  (fixed-point (average-damp (lambda (y) (/ x (square y))))
               1.0))

(define (nth-root x n r)
  (fixed-point ((repeated average-damp r) (lambda (y) 
                                                  (/ x (^ y (- n 1)))))
               1.0))

(define (root n t)
  (define x (^ 3 n))
  (nth-root x n t))

