;; Exercise 2.29.  
;; A binary mobile consists of two branches, a left branch and a right branch. 
;; Each branch is a rod of a certain length, from which hangs either a weight 
;; or another binary mobile. We can represent a binary mobile using compound 
;; data by constructing it from two branches (for example, using list):

(define (make-mobile left right)
  (list left right))

;; A branch is constructed from a length (which must be a number) together with
;; a structure, which may be either a number (representing a simple weight) or 
;; another mobile:

(define (make-branch length structure)
  (list length structure))

;; a.  Write the corresponding selectors left-branch and right-branch, which
;;     return the branches of a mobile, and branch-length and branch-structure,
;;     which return the components of a branch.

(define (left-branch mobile)
  (car mobile))
(define (right-branch mobile)
  (car (cdr mobile)))
(define (branch-length branch)
  (car branch))
(define (branch-structure branch)
  (car (cdr branch)))

;; b.  Using your selectors, define a procedure total-weight that returns the 
;;     total weight of a mobile.
 
(define (total-weight mobile)
  (define (isWeight? x) (not (pair? x)))
  (define (mobile-weight m)
    (+ (branch-weight (left-branch m))
       (branch-weight (right-branch m))))
  (define (branch-weight b)
    (if (isWeight? (branch-structure b))
        (branch-structure b)
        (mobile-weight (branch-structure b))))
  (mobile-weight mobile))

(define b1 (make-branch 1 1))
(define m1 (make-mobile b1 b1))
(define b2 (make-branch 2 m1))
(define b3 (make-branch 3 2))
(define m2 (make-mobile b3 b2))
(define b4 (make-branch 4 1))
(define b5 (make-branch 5 m2))
(define m3 (make-mobile b5 b4))
(total-weight m3)    ; Should get the answer 5

;; c.  A mobile is said to be balanced if the torque applied by its top-left
;;     branch is equal to that applied by its top-right branch (that is, if the
;;     length of the left rod multiplied by the weight hanging from that rod is
;;     equal to the corresponding product for the right side) and if each of 
;;     the submobiles hanging off its branches is balanced. Design a predicate 
;;     that tests whether a binary mobile is balanced.

(define (isBalanced? mobile)
  (define (torque b)
    (if (not (pair? (branch-structure b)))
        (* (branch-length b) (branch-structure b))
        (* (total-weight (branch-structure b))
           (branch-length b))))
  (= (torque (left-branch mobile)) (torque (right-branch mobile))))

(isBalanced? m3) ; Should return #f
(isBalanced? m1) ; Should return #t

;; d.  Suppose we change the representation of mobiles so that the constructors
;;     are

(define (make-mobile left right)
  (cons left right))
(define (make-branch length structure)
  (cons length structure))

;;    How much do you need to change your programs to convert to the new 
;;    representation?

;; Hopefully, all I should need to change are the selectors

(define (left-branch m) ; No change needed
  (car m))
(define (right-branch m)
  (cdr m))
(define (branch-length m) ; No change needed
  (car m))
(define (branch-structure m)
  (cdr m))
