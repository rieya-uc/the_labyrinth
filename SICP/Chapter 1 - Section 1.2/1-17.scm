;; Exercise 1.17.  
;; The exponentiation algorithms in this section are based on performing 
;; exponentiation by means of repeated multiplication. In a similar way, 
;; one can perform integer multiplication by means of repeated addition. 
;; The following multiplication procedure (in which it is assumed that our
;; language can only add, not multiply) is analogous to the expt procedure:

;; (define (* a b)
;;   (if (= b 0)
;;       0
;;       (+ a (* a (- b 1)))))

;; This algorithm takes a number of steps that is linear in b. Now suppose 
;; we include, together with addition, operations double, which doubles an 
;; integer, and halve, which divides an (even) integer by 2. Using these, 
;; design a multiplication procedure analogous to fast-expt that uses a 
;; logarithmic number of steps. 

(define (double n)
  (* 2 n))

(define (halve n)
  (/ n 2))

(define (even? n)
  (= (remainder n 2) 0))

;; iterative version
(define (fast-* a b)
  (fast-*-h a b 0))

(define (fast-*-h a b x)
  (cond ((= b 0) x)
        ((even? b) (fast-*-h (double a) (halve b) x))
        (else (fast-*-h a (- b 1) (+ x a)))))

;; didn't read the question close enough, here's the recusive version
(define (fastr-* a b)
  (cond ((= b 0) 0)
        ((even? b) (double (fastr-* a (halve b))))
        (else (+ a (fastr-* a (- b 1))))))

