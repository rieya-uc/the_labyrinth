;; Exercise 1.4 
;; Observe that our model of evaluation allows for combinations whose 
;; operators are compound expressions. Use this observation to describe
;; the behavior of the following procedure:

(define (a-plus-abs-b a b)
  ((if (> b 0) + -) a b))

;; Returns the value of the sum of a and the absolute value of b.
;; If b is a negative number, instead of adding b to a, subtracts b 
;; from a, which is the equivalent of taking its absolute value.

