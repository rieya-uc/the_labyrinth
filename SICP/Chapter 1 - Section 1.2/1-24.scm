;; Exercise 1.24.  
;; Modify the timed-prime-test procedure of exercise 1.22 to use fast-prime? 
;; (the Fermat method), and test each of the 12 primes you found in that 
;; exercise. Since the Fermat test has O(log n) growth, how would you expect 
;; the time to test primes near 1,000,000 to compare with the time needed to 
;; test primes near 1000? Do your data bear this out? Can you explain any 
;; discrepancy you find? 

(define (timed-prime-test n)
  (start-prime-test n (runtime)))
(define (start-prime-test n start-time)
  (if (fast-prime? n 1)
      (report-prime (- (runtime) start-time) n)
      #f))
(define (report-prime elapsed-time n)
  (newline)
  (display n)
  (display " *** ")
  (display elapsed-time)
  #t)

(define (prime? n)
  (= n (smallest-divisor n)))

(define (smallest-divisor n)
  (find-divisor n 2))
(define (find-divisor n test-divisor)
  (cond ((> (square test-divisor) n) n)
        ((divides? test-divisor n) test-divisor)
        (else (find-divisor n (+ test-divisor 1)))))
(define (divides? a b)
  (= (remainder b a) 0))
(define (square n)
  (* n n))
(define (prime? n)
  (= n (smallest-divisor n)))

(define (search-for-primes start total)
  (search-for-primes-h start total 0))
(define (search-for-primes-h start total found)
  (cond ((= found total) )
        ((= (remainder start 2) 0) (search-for-primes-h (+ start 1) total found))
        (else (if (timed-prime-test start) 
                  (search-for-primes-h (+ start 2) total (+ found 1))
                  (search-for-primes-h (+ start 2) total found)))))
(define (fermat-test n)
  (define (try-it a)
    (= (expmod a n n) a))
  (try-it (+ 1 (random (- n 1)))))
(define (fast-prime? n times)
  (cond ((= times 0) true)
        ((fermat-test n) (fast-prime? n (- times 1)))
        (else false)))
(define (expmod base exp m)
  (cond ((= exp 0) 1)
        ((even? exp)
         (remainder (square (expmod base (/ exp 2) m))
                    m))
        (else
         (remainder (* base (expmod base (- exp 1) m))
                    m))))

;; Testing with numbers < 10,000,000,000 produces results instantly,
;; but testing the numbers > 10,000,000,000 causes the RNG to give an error