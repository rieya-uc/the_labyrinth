;; Exercise 2.10.  
;; Ben Bitdiddle, an expert systems programmer, looks over Alyssa's shoulder
;; and comments that it is not clear what it means to divide by an interval
;; that spans zero. Modify Alyssa's code to check for this condition and 
;; to signal an error if it occurs. 

(define (div-interval x y)
  (if (and (< (lower-bound y) 0) (> (upper-bound y) 0))
      (error "Denumerator interval spans zero")
      (mul-interval x 
                    (make-interval (/ 1.0 (upper-bound y))
                                   (/ 1.0 (lower-bound y))))))


(define (make-interval a b) (cons a b))

(define (lower-bound x) 
  (car x))
(define (upper-bound x)
  (cdr x))

(define (sub-interval x y)
  (make-interval (- (lower-bound x) (lower-bound y))
                 (- (upper-bound x) (lower-bound y))))
  
(define (add-interval x y)
  (make-interval (+ (lower-bound x) (lower-bound y))
                 (+ (upper-bound x) (upper-bound y))))


(define (mul-interval x y)
  (let ((p1 (* (lower-bound x) (lower-bound y)))
        (p2 (* (lower-bound x) (upper-bound y)))
        (p3 (* (upper-bound x) (lower-bound y)))
        (p4 (* (upper-bound x) (upper-bound y))))
    (make-interval (min p1 p2 p3 p4)
                   (max p1 p2 p3 p4))))



(define intx (make-interval 3.4 5.2))
(define inty (make-interval 1.3 8.5))


