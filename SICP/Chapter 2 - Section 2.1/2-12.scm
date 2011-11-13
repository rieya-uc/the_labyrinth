;; Exercise 2.12.  
;; Define a constructor make-center-percent that takes a center and a 
;; percentage tolerance and produces the desired interval. You must 
;; also define a selector percent that produces the percentage tolerance 
;; for a given interval. The center selector is the same as the one shown above. 

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

(define (div-interval x y)
  (if (and (< (lower-bound y) 0) (> (upper-bound y) 0))
      (error "Denumerator interval spans zero")
      (mul-interval x 
                    (make-interval (/ 1.0 (upper-bound y))
                                   (/ 1.0 (lower-bound y))))))

(define (mul-interval x y)
  (let ((p1 (* (lower-bound x) (lower-bound y)))
        (p2 (* (lower-bound x) (upper-bound y)))
        (p3 (* (upper-bound x) (lower-bound y)))
        (p4 (* (upper-bound x) (upper-bound y))))
    (make-interval (min p1 p2 p3 p4)
                   (max p1 p2 p3 p4))))


(define (make-center-width c w)
  (make-interval (- c w) (+ c w)))
(define (center i)
  (/ (+ (lower-bound i) (upper-bound i)) 2))
(define (width i)
  (/ (- (upper-bound i) (lower-bound i)) 2))

(define (make-center-percent c p)
  (let ((percent (* (/ c 100) p)))
    (make-interval (- c percent) (+ c percent))))
(define (percent c)
  (let ((mid (center c))
        (upper (upper-bound c)))
    (/ (* 100.0 (- upper mid)) mid)))
    
  
