;; Exercise 2.42
;; Complete the program to find solutions to the eight queens problem

(define (queens board-size)
  (define (queen-cols k)  
    (if (= k 0)
        (list empty-board)
        (filter
         (lambda (positions) (safe? k positions))
         (flatmap
          (lambda (rest-of-queens)
            (map (lambda (new-row)
                   (adjoin-position new-row k rest-of-queens))
                 (enumerate-interval 1 board-size)))
          (queen-cols (- k 1))))))
  (queen-cols board-size))
 
(define empty-board '())

(define (adjoin-position new-row k positions)
  (append positions (list (list new-row k))))
  
(define (safe? k positions)
    (define (equals? p1 p2)   ; are the positions p1 and p2 the same?
    (and (= (car p1) (car p2))
         (= (cadr p1) (cadr p2))))
  (define (same-row? p1 p2) ; are the positions p1 and p2 in the same row?
    (= (car p1) (car p2)))
  (define (same-col? p1 p2) ; are the positions p1 and p2 in the same column?
    (= (cadr p1) (cadr p2)))
  (define (same-diagonal? p1 p2) ; are p1 and p2 diagonal from each other?
    (or (= (+ (car p1) (cadr p1))
           (+ (car p2) (cadr p2)))
        (= (- (car p1) (cadr p1))
           (- (car p2) (cadr p2)))))
  (let ((kth-pos (list-ref positions (- k 1))))
    (define (iter pos)
      (cond ((null? pos) #t)
            ((equals? kth-pos (car pos)) (iter (cdr pos)))
            ((same-row? kth-pos (car pos)) #f)
            ((same-col? kth-pos (car pos)) #f)
            ((same-diagonal? kth-pos (car pos)) #f)
            (else
           (iter (cdr pos)))))
    (iter positions)))
  

(define nil '())
(define (accumulate op init seq)
  (if (null? seq)
      init
      (op (car seq) (accumulate op init (cdr seq)))))
(define (filter pred seq)
  (cond ((null? seq) nil)
        ((pred (car seq)) (cons (car seq) (filter pred (cdr seq))))
        (else
         (filter pred (cdr seq)))))
(define (flatmap proc seq)
  (accumulate append nil (map proc seq)))
(define (enumerate-interval low high)
  (if (> low high)
      nil
      (cons low (enumerate-interval (+ low 1) high))))

(display "queens 1")
(newline)
(queens 1)
(display "queens 3")
(newline)
(queens 3)
(display "queens 4")
(newline)
(queens 4)
             
                    
  
  