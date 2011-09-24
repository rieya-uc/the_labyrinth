;; Exercise 1.28
;; ... Modify the expmod procedure to signal if it discovers a nontrivial 
;; square root of 1, and use this to implement the Miller-Rabin test with 
;; a procedure analogous to fermat-test. Check your procedure by testing 
;; various known primes and non-primes...

;; Miller-Rabin Test
;; If n is a prime number and a is any positive integer less than n, 
;; then a raised to the (n - 1)st power is congruent to 1 modulo n. 

;; Runs miller-rabin-test a specified number of times
(define (fast-prime? n times)
  (cond ((= times 0) true)
        ((miller-rabin-test n) (fast-prime? n (- times 1)))
        (else false)))

(define (miller-rabin-test n)
  (define (try-it a)
    (= (expmod a (- n 1) n) 1))
    ;;(display (expmod a (- n 1) n)))
  (try-it (+ 1 (random (- n 1)))))
    
(define (expmod base exp m)
  (cond ((= exp 0) 1)
        ((even? exp)
         (non-trivial-root (expmod base (/ exp 2) m) m)) 
        (else
         (remainder (* base (expmod base (- exp 1) m))
                    m))))

(define (non-trivial-root a n)
  (if (and (not (= 1 a))
           (not (= a (- n 1)))
           (= (remainder (square a) n) 1))
      0
      (remainder (square a) n)))

(define (square n)
  (* n n))

