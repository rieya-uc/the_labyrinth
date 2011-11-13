;; Exercise 2.28.  
;; Write a procedure fringe that takes as argument a tree (represented as a 
;; list) and returns a list whose elements are all the leaves of the tree 
;; arranged in left-to-right order. 

(define (fringe x)
  (cond ((not (pair? x)) (list x))
        ((null? (cdr x)) (fringe (car x)))
        (else
         (append (fringe (car x)) (fringe (cdr x))))))

(define x (list (list 1 2) (list 3 4)))
(fringe x)
(fringe (list x x))




