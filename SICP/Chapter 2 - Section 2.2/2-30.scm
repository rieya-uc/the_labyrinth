;; Exercise 2.30.  
;; Define a procedure square-tree analogous to the square-list procedure of 
;; exercise 2.21. That is, square-list should behave as follows:

;; (square-tree
;;  (list 1
;;       (list 2 (list 3 4) 5)
;;       (list 6 7)))
;; (1 (4 (9 16) 25) (36 49))

;; Define square-tree both directly (i.e., without using any higher-order 
;; procedures) and also by using map and recursion.

(define (square x) (* x x))
(define l (list 1 (list 2 (list 3 4) 5) (list 6 7)))

(define (square-tree-r l)
  (cond ((null? l) l)
        ((not (pair? l)) (square l))
        (else
         (cons (square-tree-r (car l)) (square-tree-r (cdr l))))))
           
(square-tree-r l)

(define (square-tree-m l)
  (map (lambda (sub-tree)
         (if (pair? sub-tree)
             (square-tree-m sub-tree)
             (square sub-tree)))
       l))

(square-tree-m l)