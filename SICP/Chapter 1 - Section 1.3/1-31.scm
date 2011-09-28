;; Exercise 1.31.  
;; a.  The sum procedure is only the simplest of a vast number of similar 
;; abstractions that can be captured as higher-order procedures. 
;; Write an analogous procedure called product that returns the product of 
;; the values of a function at points over a given range. Show how to define 
;; factorial in terms of product. Also use product to compute approximations 
;  to using the formula 
;;      (pi / 4) = [2.4.4.6.6.8...] / [3.3.5.5.7.7...]

;; b.  If your product procedure generates a recursive process, write one 
;; that generates an iterative process. If it generates an iterative process, 
;; write one that generates a recursive process. 

(define (pi4 k)
  (define (inc n) (+ n 1))
  (define (top n)
    (if (even? n) (+ n 2) (+ n 1)))
  (define (bottom n)
    (if (even? n) (+ n 1) (+ n 2)))
  (define (numerator n) (product-r top 1 inc n))
  ;; why can't I write this...?
  ;; (define numerator (product-r top 1 inc k)
  ;; product turns up an error if I do so.
  (define (denum n) (product-r bottom 1 inc n))
  (* 4.0 (/ (numerator k) (denum k))))

(define (factorial x)
  (define (inc n) (+ n 1))
  (define (factor n) n)
  (product-r factor 1 inc x))
  
;; Recursive version
(define (product-r term a next b)
  (if (> a b)
      1
      (* (term a)
         (product-r term (next a) next b))))

;; Iterative version
(define (product-i term a next b)
  (define (iter a result)
    (if (> a b)
        result
        (iter (next a) (* (term a) result))))
  (iter a 1))

(define (cube n)
  (* n n n))

(define (square n)
  (* n n))
  