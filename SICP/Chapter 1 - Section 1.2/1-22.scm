;; Exercise 1.22.  
;; Most Lisp implementations include a primitive called runtime that returns 
;; an integer that specifies the amount of time the system has been running 
;; (measured, for example, in microseconds). 
;; The following timed-prime-test procedure, when called with an integer n,
;; prints n and checks to see if n is prime. If n is prime, the procedure 
;; prints three asterisks followed by the amount of time used in performing 
;; the test.

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

;; Using this procedure, write a procedure search-for-primes that checks 
;; the primality of consecutive odd integers in a specified range. Use your
;; procedure to find the three smallest primes larger than 1000; larger than 
;; 10,000; larger than 100,000; larger than 1,000,000. Note the time needed 
;; to test each prime. Since the testing algorithm has order of growth of (n),
;; you should expect that testing for primes around 10,000 should take about
;; 10 times as long as testing for primes around 1000. Do your timing data bear
;; this out? How well do the data for 100,000 and 1,000,000 support the n 
;; prediction? Is your result compatible with the notion that programs on 
;; your machine run in time proportional to the number of steps required for 
;; the computation? 

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

;; Running it for 1,000,000,000, I get an average of 60,000ms
;; Running if for 10,000,000,000, I get an average of 100,000ms
;; And for 1,000,000, an average of 470,000.
;; Um.... this doesn't tell me anything


