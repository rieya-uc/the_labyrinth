;; Exercise 1.33. 
;; You can obtain an even more general version of accumulate (exercise 1.32)
;; by introducing the notion of a filter on the terms to be combined. That is,
;; combine only those terms derived from values in the range that satisfy a 
;; specified condition. The resulting filtered-accumulate abstraction takes 
;; the same arguments as accumulate, together with an additional predicate 
;; of one argument that specifies the filter. Write filtered-accumulate as 
;; a procedure. Show how to express the following using filtered-accumulate:

;; a. the sum of the squares of the prime numbers in the interval a to b 
;; (assuming that you have a prime? predicate already written)

;; b. the product of all the positive integers less than n that are relatively 
;; prime to n (i.e., all positive integers i < n such that GCD(i,n) = 1). 

(define (filtered-accumulate filter combiner null-value term a next b)
  (if (> a b)
      null-value
      (if (predicate a)
          (combiner (term a)
                    (filtered-accumulate combiner null-value term (next a) next b))
          (filtered-accumulate combiner null-value term (next a) next b))))

(define (sum-prime-squares a b)
  (define (square n) (* n n))
  (define (inc n) (+ n 1))
  (filtered-accumulate prime? + 0 square a inc b))

(define (product-prime n)
  (define (identity n) n)
  (define (inc n) (+ 1 n))
  (filtered-accumulate prime? * 1 identity 1 inc n))
