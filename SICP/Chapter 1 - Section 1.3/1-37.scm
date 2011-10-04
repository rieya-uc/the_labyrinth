;; Exercise 1.37. 
;; a. An infinite continued fraction is an expression of the form

;;       f = [N1] / [D1 + [N2 / [D2 + [N3 / [D3 + [N4 / ...

;; As an example, one can show that the infinite continued fraction expansion 
;; with the Ni and the Di all equal to 1 produces 1/phi, where is the golden ratio
;; (described in section 1.2.2). One way to approximate an infinite continued
;; fraction is to truncate the expansion after a given number of terms. Such
;; a truncation -- a so-called k-term finite continued fraction -- has the form
;; [omitted, go look on the website!]

;; Suppose that n and d are procedures of one argument (the term index i) that
;; return the Ni and Di of the terms of the continued fraction. Define a
;; procedure cont-frac such that evaluating (cont-frac n d k) computes the
;; value of the k-term finite continued fraction. Check your procedure by
;; approximating 1/phi using

;; (cont-frac (lambda (i) 1.0)
;;           (lambda (i) 1.0)
;;           k)

;; for successive values of k. How large must you make k in order to get an
;; approximation that is accurate to 4 decimal places?

;; b. If your cont-frac procedure generates a recursive process, write one
;; that generates an iterative process. If it generates an iterative process,
;; write one that generates a recursive process. 

;; 1/phi = 0.6180 (to 4 decimal places)
;; We need to calculate using 12 terms to get an accuracy of 4 decimal places.

;; Recursive version
(define (cont-frac-r n d k)
  (define (helper i)
    (if (= i k)
        (/ (n i) (d i))
        (+ (d i) (/ (n (+ i 1)) (helper (+ i 1))))))
  (/ (n 1) (helper 1)))

;; Iterative version - works through the equation backwards
(define (cont-frac-i n d k)
  (define (helper i total)
    (if (= i 1)
        (/ (n 1) total)
        (helper (- i 1) (+ (d (- i 1)) 
                           (/ (n i) total)))))
  (helper k (d k)))
    
        
(cont-frac-r (lambda (i) 1.0)
             (lambda (i) 1.0)
             12)