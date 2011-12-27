;; Exercise 2.60. 
;; We specified that a set would be represented as a list with no duplicates. 
;; Now suppose we allow duplicates. For instance, the set {1,2,3} could be 
;; represented as the list (2 3 2 1 3 2 2). 
;; Design procedures element-of-set?, adjoin-set, union-set, and 
;; intersection-set that operate on this representation. How does the efficiency 
;; of each compare with the corresponding procedure for the non-duplicate
;; representation? Are there applications for which you would use this 
;; representation in preference to the non-duplicate one? 

; No change
(define (element-of-set? x set)
  (cond ((null? set) #f)
        ((eq? (car set) x) #t)
        (else (element-of-set? (cdr set) x))))

; O(1)
(define (adjoin-set set x)
  (cons x set))

; No change
(define (intersection-set set1 set2)
  (cond ((or (null? set1) (null? set2)) '())
        ((element-of-set? set2 (car set1)) 
         (cons (car set1) (intersection-set set2 (cdr set1))))
        (else
         (intersection-set set2 (cdr set1)))))

; However long it takes to append one set onto another
; O(n) I'd guess
(define (union-set set1 set2)
  (append set1 set2))
  