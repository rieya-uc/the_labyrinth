;; Exercise 1.23.  
;; The smallest-divisor procedure shown at the start of this section does 
;; lots of needless testing: After it checks to see if the number is 
;; divisible by 2 there is no point in checking to see if it is divisible 
;; by any larger even numbers. This suggests that the values used for
;; test-divisor should not be 2, 3, 4, 5, 6, ..., but 
;; rather 2, 3, 5, 7, 9, .... To implement this change, define a procedure 
;; next that returns 3 if its input is equal to 2 and otherwise returns its 
;; input plus 2. Modify the smallest-divisor procedure to use 
;; (next test-divisor) instead of (+ test-divisor 1). With timed-prime-test 
;; incorporating this modified version of smallest-divisor, run the test for 
;; each of the 12 primes found in exercise 1.22. Since this modification 
;; halves the number of test steps, you should expect it to run about twice
;; as fast. Is this expectation confirmed? If not, what is the observed ratio 
;; of the speeds of the two algorithms, and how do you explain the fact that 
;; it is different from 2? 

(define (timed-prime-test n)
  (start-prime-test n (runtime)))
(define (start-prime-test n start-time)
  (if (prime? n)
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
        (else (find-divisor n (next test-divisor)))))
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

(define (next test-divisor)
  (if (= test-divisor 2)
      3
      (+ test-divisor 2)))

#|
**** original ****
> (search-for-primes 100000000000 3) 
100000000003 *** 789000
100000000019 *** 751000
100000000057 *** 749000#t
                total time = 2289000

> (search-for-primes 100000000000 3) 
100000000003 *** 823000
100000000019 *** 737000
100000000057 *** 749000#t
                total time = 2039000

> (search-for-primes 100000000000 3)
100000000003 *** 802000
100000000019 *** 856000
100000000057 *** 742000#t   
                total time = 2400000



**** with (next test-divisor) ****
> (search-for-primes 100000000000 3)
100000000003 *** 472000
100000000019 *** 336000
100000000057 *** 374000#t
                total time = 1182000

> (search-for-primes 100000000000 3) 
100000000003 *** 318000
100000000019 *** 399000
100000000057 *** 320000#t
                total time = 1037000

> (search-for-primes 100000000000 3) 
100000000003 *** 399000
100000000019 *** 421000
100000000057 *** 342000#t          
                total time = 1162000
|#

;; So yes, the time taken is appromixately halved