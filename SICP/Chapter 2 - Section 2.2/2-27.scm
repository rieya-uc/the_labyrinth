;; Exercise 2.27.  
;; Modify your reverse procedure of exercise 2.18 to produce a deep-reverse
;; procedure that takes a list as argument and returns as its value the list 
;; with its elements reversed and with all sublists deep-reversed as well. 
;; For example,

;; (define x (list (list 1 2) (list 3 4)))

;; x
;; ((1 2) (3 4))

;; (reverse x)
;; ((3 4) (1 2))

;; (deep-reverse x)
;; ((4 3) (2 1))

(define (atom? x) (not (pair? x)))

(define (deep-reverse x)
  (cond ((null? x) '())
        ((atom? x) x)
        (else
         (append (deep-reverse (cdr x)) (list (deep-reverse (car x)))))))
           
(deep-reverse '((1 2) (3 4)))
(deep-reverse '((1) ((2 3)) (4 (5 6) (7))))
(deep-reverse '(1 2 3 4))