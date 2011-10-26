;; Exercise 2.5.  
;; Show that we can represent pairs of nonnegative integers using only 
;; numbers and arithmetic operations if we represent the pair a and b
;; as the integer that is the product 2^a 3^b. Give the corresponding 
;; definitions of the procedures cons, car, and cdr.

;; (cons a b) = x
;; If a > 0 then the integer (x) returned by cons will always be even (as we're 
;; multiplying by an even number). 
;; To find out what a is (that is car of the pair), we divide the x by 2 until x
;; isn't even, and count how many times we've performed the division. This is a.
;; To find out what b is (cdr), we first perform car, then divide x by the 2^result.
;; We then divide x by 3 until x isn't a multiple of 3 and return the number of
;; times we've divided the number by.

;; E.g. (cons 3 4) = 648
;; (car 648) -> 648 can be divided by 2 exactly 3 times. (648, 324, 162, 81).
;; Therefore (car 648) = 3
;; (cdr 648) = (cdr (648 / (2 ^ (car 648)))) = 216
;; 216 can be divided by 3 exactly 4 times.
;; Therefore (cdr 648) = 4.

(define (^ b n)
  (cond ((= n 0) 1)
        ((even? n) (square (^ b (/ n 2))))
        (else (* b (^ b (- n 1))))))

(define (square x) (* x x))

(define (consx x y) 
  (* (^ 2 x) (^ 3 y)))

(define (carx z)
  (define (carx-h n count)
    (if (= (remainder n 2) 0)
        (carx-h (/ n 2) (+ count 1))
        count))
  (carx-h z 0))

;; I could just do a cube root here also
(define (cdrx z)
  (define (cdrx-h n count)
    (if (= (remainder n 3) 0)
        (cdrx-h (/ n 3) (+ count 1))
        count))
  (cdrx-h (/ z (^ 2 (carx z))) 0))

(define p (consx 3 4))
(carx p)
(cdrx p)


