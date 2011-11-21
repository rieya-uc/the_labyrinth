;; Exercise 2.33.  
;; Fill in the missing expressions to complete the following definitions of
;; some basic list-manipulation operations as accumulations:

(define nil '())
(define (accumulate op initial sequence)
  (if (null? sequence)
      initial
      (op (car sequence)
          (accumulate op initial (cdr sequence)))))
(define (filter predicate sequence)
  (cond ((null? sequence) nil)
        ((predicate (car sequence))
         (cons (car sequence) (filter predicate (cdr sequence))))
        (else
         (filter predicate (cdr sequence)))))

(define (mapx p sequence)
  (accumulate (lambda (x y) (cons (p x) y)) nil sequence))
(define (appendx seq1 seq2)
  (accumulate cons seq2 seq1))
(define (lengthx sequence)
  (accumulate (lambda (x y) (+ 1 y)) 0 sequence))
