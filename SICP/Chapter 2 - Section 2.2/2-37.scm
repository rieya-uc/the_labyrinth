;; Exercise 2.37
;; [Matrix info omitted]
;; We can define the dot product as

(define (dot-product v w)
  (accumulate + 0 (map * v w)))

;; Fill in the missing expressions in the following procedures for computing 
;; the other matrix operations.

(define (accumulate op init seqs)
  (if (null? seqs)
      init
      (op (car seqs)
          (accumulate op init (cdr seqs)))))

(define (accumulate-n op init seqs)
  (if (null? (car seqs))
      '()
      (cons (accumulate op init (map car seqs))
            (accumulate-n op init (map cdr seqs)))))

; Returns vector t, where ti = sum of mij*vj 
(define (matrix-*-vector m v)
  (map (lambda (x)
         (accumulate + 0 (map * x v)))  ; I can replace this with dot-product
       m))

; Returns the matrix n, where nij = mji
(define (transpose mat)
  (accumulate-n cons '() mat))

; Returns the matrix p, where pij = sum(mik*nkj)
(define (matrix-*-matrix m n)
  (let ((cols (transpose n)))
    (map (lambda (x) (matrix-*-vector cols x)) m)))

(define m '((1 2 3 4) (4 5 6 6) (6 7 8 9)))
(define n '((12 2 4) (1 8 3) (5 2 5) (7 5 6)))
(define v (car m))
(define w (car (cdr m)))

(matrix-*-matrix m n)

; Reference
; matrix-*-vector
; [(A B C)]   [P]     [AP+BQ+CR]
; [(D E F)] * [Q]  =  [DP+EQ+FR]
; [(G H I)]   [R]     [GP+HQ+IR]
; ----m----   -v-     ----t-----

; transpose
; [(A B C)]     [(A D G)]
; [(D E F)]  =  [(B E H)]
; [(G H I)]     [(C F I)]

; matrix-*-matrix
; [(A B C)]     [(R S T)]   [(AR+BU+CX) (AS+DV+GY) (AT+DW+GZ)]
; [(D E F)]  *  [(U V W)] = [(BR+EU+HY) (BS+EV+HY) (BT+EW+HZ)]
; [(G H I)]     [(X Y Z)]   [(CR+FU+IX) (CS+FV+IY) (CT+FW+IZ)]