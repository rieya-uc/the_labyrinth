;; Exercise 2.62.  
;; Give a O(n) implementation of union-set for sets represented as ordered 
;; lists. 

; The book uses let, but I prefer this...
(define (union-set set1 set2)
  (cond ((null? set1) set2)
        ((null? set2) set1)
        ((= (car set1) (car set2))
         (cons (car set1) (union-set (cdr set1) (cdr set2))))
        ((> (car set1) (car set2))
         (cons (car set2) (union-set (cdr set1) (cdr set2))))
        (else
         (union-set set1 (cdr set2)))))


(define (adjoin-set x set)
  (cond ((null? set) (list x))
        ((= x (car set)) set)
        ((< x (car set)) (cons x set))
        (else
         (cons (car set) (adjoin-set x (cdr set))))))
        
(define (element-of-set? x set)
  (cond ((null? set) false)
        ((= x (car set)) true)
        ((< x (car set)) false)
        (else (element-of-set? x (cdr set)))))

