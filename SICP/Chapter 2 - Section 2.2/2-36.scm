;; Exercise 2.36.  
;; The procedure accumulate-n is similar to accumulate except that it takes
;; as its third argument a sequence of sequences, which are all assumed to
;; have the same number of elements. It applies the designated accumulation
;; procedure to combine all the first elements of the sequences, all the
;; second elements of the sequences, and so on, and returns a sequence of the
;; results. For instance, if s is a sequence containing four sequences, 
;; ((1 2 3) (4 5 6) (7 8 9) (10 11 12)), then the value of (accumulate-n + 0 s)
;; should be the sequence (22 26 30). Fill in the missing expressions in the 
;; following definition of accumulate-n:

(define nil '())
(define (accumulate op init seqs)
  (if (null? seqs)
      init
      (op (car seqs) (accumulate op init (cdr seqs)))))

(define (get-first seqs)
  (if (null? seqs)
      '()
      (cons (car (car seqs))
            (get-first (cdr seqs)))))

(define (remove-first seqs)
  (if (null? seqs)
      '()
      (cons (cdr (car seqs))
            (remove-first (cdr seqs)))))

(define (accumulate-nx op init seqs)
  (if (null? (car seqs))
      nil
      (cons (accumulate op init (get-first seqs))
            (accumulate-n op init (remove-first seqs)))))


; Better version
(define (accumulate-n op init seqs)
  (if (null? (car seqs))
      nil
      (cons (accumulate op init (map car seqs))
            (accumulate-n op init (map cdr seqs)))))
             
(accumulate-n + 0 '((1 2 3) (4 5 6) (7 8 9) (10 11 12)))

