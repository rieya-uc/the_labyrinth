;; Exercise 2.39.   
;; Complete the following definitions of reverse (exercise 2.18) in terms 
;; of fold-right and fold-left from exercise 2.38

; The version of Scheme I'm using doesn't have fold-right/left
(define (fold-right op init seq)
  (if (null? seq)
      init
      (op (car seq) (fold-right op init (cdr seq)))))

(define (fold-left op init seq)
  (define (iter result rest)
    (if (null? rest)
        result
        (iter (op result (car rest))
              (cdr rest))))
  (iter init seq))

(define nil '())
                   

(define (reverse-r sequence)
  (fold-right (lambda (x y)
                (append y (list x)))
              nil sequence))

(define (reverse-l sequence)
  (fold-left (lambda (x y) (cons y x)) nil sequence))


(define x '(1 2 3 4 5 6))
(reverse-r x)
(reverse-l x)
