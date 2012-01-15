;; Exercise 2.66. 
;; Implement the lookup procedure for the case where the set of records is 
;; structured as a binary tree, ordered by the numerical values of the keys. 

; For reference
(define (entry tree) (car tree))
(define (left-branch tree) (cadr tree))
(define (right-branch tree) (caddr tree))
(define (make-tree entry left right)
  (list entry left right))


(define (tree-lookup given-key set-of-records)
  (if (null? set-of-records)
      #f
      (let ((cur-key (key (entry set-of-records))))
        (cond ((equal? given-key cur-key) cur-key)
              ((< given-key cur-key) 
               (tree-lookup given-key (left-branch set-of-records)))
              (else
               (tree-lookup given-key (right-branch set-of-records)))))))
               
