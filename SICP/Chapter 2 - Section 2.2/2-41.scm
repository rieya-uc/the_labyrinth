;; Exercise 2.41. 
;; Write a procedure to find all ordered triples of distinct positive 
;; integers i, j, and k less than or equal to a given integer n that 
;; sum to a given integer s.

(define (ordered-triples n)
  (flatmap (lambda (i)
             (flatmap (lambda (j)
                        (map (lambda (k) (list i j k))
                             (enumerate-interval 1 (- j 1))))
                        (enumerate-interval 1 (- i 1))))
           (enumerate-interval 1 n)))

(define (ordered-triples-sum n s)
  (filter (lambda (t) 
            (= (+ (car t) (cadr t) (cadr (cdr t))) s))
          (ordered-triples n)))



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


 (ordered-triples 6)
 (ordered-triples-sum 6 10)

                        
             
                    
  
  