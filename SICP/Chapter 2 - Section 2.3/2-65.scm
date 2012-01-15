;; Exercise 2.65. 
;; Use the results of exercises 2.63 and  2.64 to give O(n) implementations of 
;; union-set and intersection-set for sets implemented as (balanced) binary
;; trees.

(define (entry tree) (car tree))
(define (left-branch tree) (cadr tree))
(define (right-branch tree) (caddr tree))
(define (make-tree entry left right)
  (list entry left right))
      
;; Union - Contains all elements from both sets
(define (union-tree tree1 tree2)
  (let ((set1 (tree->list tree1))
        (set2 (tree->list tree2)))
    (list->tree (union-set set1 set2))))

(define (union-set set1 set2)
  (cond ((null? set1) set2)
        ((null? set2) set1)
        ((= (car set1) (car set2))
         (cons (car set1) (union-set (cdr set1) (cdr set2))))
        ((> (car set1) (car set2))
         (cons (car set2) (union-set (cdr set1) (cdr set2))))
        (else
         (cons (car set1) (union-set (cdr set1) set2)))))

; Intersection - Elements that appear in both sets
(define (intersection-tree tree1 tree2)
  (let ((set1 (tree->list tree1))
        (set2 (tree->list tree2)))
    (list->tree (intersection-set set1 set2))))
        
(define (intersection-set set1 set2)
  (if (or (null? set1) (null? set2))
      '()    
      (let ((x1 (car set1)) (x2 (car set2)))
        (cond ((= x1 x2)
               (cons x1
                     (intersection-set (cdr set1)
                                       (cdr set2))))
              ((< x1 x2)
               (intersection-set (cdr set1) set2))
              ((< x2 x1)
               (intersection-set set1 (cdr set2)))))))



    
(define (union-set-tree set1 set2)
  (let ((list1 (tree->list-2 set1))
        (list2 (tree->list-2 set2)))
    (list->tree (union-set list1 list2))))

(define (list->tree elements)
  (car (partial-tree elements (length elements))))

(define (partial-tree elts n)
  (if (= n 0)
      (cons '() elts)
      (let ((left-size (quotient (- n 1) 2)))
        (let ((left-result (partial-tree elts left-size)))
          (let ((left-tree (car left-result))
                (non-left-elts (cdr left-result))
                (right-size (- n (+ left-size 1))))
            (let ((this-entry (car non-left-elts))
                  (right-result (partial-tree (cdr non-left-elts)
                                              right-size)))
              (let ((right-tree (car right-result))
                    (remaining-elts (cdr right-result)))
                (cons (make-tree this-entry left-tree right-tree)
                      remaining-elts))))))))

(define (tree->list tree)
  (if (null? tree)
      '()
      (append (tree->list (left-branch tree))
              (cons (entry tree)
                    (tree->list (right-branch tree))))))

(define tree1
  (list->tree '(3 4 7 9 14 16 26 34)))
(define tree2
  (list->tree '(1 3 5 8 9 10 17 36)))

