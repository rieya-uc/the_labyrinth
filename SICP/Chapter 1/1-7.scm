;; Exercise 1.7.  
;; The good-enough? test used in computing square roots will not be very 
;; effective for finding the square roots of very small numbers. Also, in 
;; real computers, arithmetic operations are almost always performed with 
;; limited precision. This makes our test inadequate for very large numbers.
;; Explain these statements, with examples showing how the test fails for
;; small and large numbers. An alternative strategy for implementing 
;; good-enough? is to watch how guess changes from one iteration to the next 
;; and to stop when the change is a very small fraction of the guess.
;; Design a square-root procedure that uses this kind of end test.
;; Does this work better for small and large numbers? 
;;

(define (square x)
  (* x x))

(define (sqrt-iter guess x)
  (if (good-enough? guess x)
      guess
      (sqrt-iter (improve guess x)
                 x)))

(define (improve guess x)
  (average guess (/ x guess)))

(define (average x y)
  (/ (+ x y) 2))

(define (good-enough? guess x)
  (< (abs (- (square guess) x)) 0.001))

(define (sqrt x)
  (sqrt-iter 1.0 x))

;; Let's have a look at what's happening with small numbers e.g (sqrt 0.0000001)
;; (improve ... ) will keep improving the guess until the guess gets to 
;; approximately 0.0625, after which good-enough will return true. However, as 
;; 0.001 (from good-enough?) is so much bigger than 0.0000001, we are still quite 
;; far from the true square root. We therefore need a value in good-enough? that's
;; relative to the size of x.

;; And for very large numbers, because computers use limited precision, 
;; improve guess can only do so much, and will never reach the 0.001 difference 
;; as specified in good-enough?.

;; Here's a (good-enough?) that takes into consideration the size of x.

(define (good-enough?? guess x)
  ()


