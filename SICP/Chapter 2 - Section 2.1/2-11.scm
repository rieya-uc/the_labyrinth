;; Exercise 2.11.  
;; In passing, Ben also cryptically comments: 
;; "By testing the signs of the endpoints of the intervals, it is possible to 
;; break mul-interval into nine cases, only one of which requires more than 
;; two multiplications." Rewrite this procedure using Ben's suggestion. 


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

(define (mul-interval-old x y)
  (let ((p1 (* (lower-bound x) (lower-bound y)))
        (p2 (* (lower-bound x) (upper-bound y)))
        (p3 (* (upper-bound x) (lower-bound y)))
        (p4 (* (upper-bound x) (upper-bound y))))
    (make-interval (min p1 p2 p3 p4)
                   (max p1 p2 p3 p4))))

; Seriously? Why do this???
(define (mul-interval x y)
  (define (neg? n)
    (or (< n 0) (= n 0)))
  (define (pos? n)
    (> n 0))
  (let ((lx (lower-bound x))
        (ux (upper-bound x))
        (ly (lower-bound y))
        (uy (upper-bound y))
        (p1 (* (lower-bound x) (lower-bound y)))
        (p2 (* (lower-bound x) (upper-bound y)))
        (p3 (* (upper-bound x) (lower-bound y)))
        (p4 (* (upper-bound x) (upper-bound y))))
    (cond ((and (pos? lx) (pos? ux) (pos? ly) (pos? uy))
           (make-interval p1 p4))
          ((and (pos? lx) (pos? ux) (neg? ly) (pos? uy))
           (make-interval p3 p4))
          ((and (pos? lx) (pos? ux) (neg? ly) (neg? uy))
           (make-interval p3 p2))
          ((and (neg? lx) (pos? ux) (pos? ly) (pos? uy))
           (make-interval p2 p4))
          ((and (neg? lx) (pos? ux) (neg? ly) (pos? uy))
           (make-interval (min p2 p3) (max p1 p4)))
          ((and (neg? lx) (pos? ux) (neg? ly) (neg? uy))
           (make-interval p3 p1))
          ((and (neg? lx) (neg? ux) (pos? ly) (pos? uy))
           (make-interval p2 p3))
          ((and (neg? lx) (neg? ux) (neg? ly) (pos? uy))
           (make-interval p2 p1))
          ((and (neg? lx) (neg? ux) (neg? ly) (neg? uy))
           (make-interval p4 p1)))))

(define (findmin x y)
  (let ((p1 (* (lower-bound x) (lower-bound y)))
        (p2 (* (lower-bound x) (upper-bound y)))
        (p3 (* (upper-bound x) (lower-bound y)))
        (p4 (* (upper-bound x) (upper-bound y))))
    (cond ((= (min p1 p2 p3 p4) p1) (display "np1"))
          ((= (min p1 p2 p3 p4) p2) (display "np2"))
          ((= (min p1 p2 p3 p4) p3) (display "np3"))
          ((= (min p1 p2 p3 p4) p4) (display "np4")))))
(define (findmax x y)
  (let ((p1 (* (lower-bound x) (lower-bound y)))
        (p2 (* (lower-bound x) (upper-bound y)))
        (p3 (* (upper-bound x) (lower-bound y)))
        (p4 (* (upper-bound x) (upper-bound y))))
    (cond ((= (max p1 p2 p3 p4) p1) (display "xp1"))
          ((= (max p1 p2 p3 p4) p2) (display "xp2"))
          ((= (max p1 p2 p3 p4) p3) (display "xp3"))
          ((= (max p1 p2 p3 p4) p4) (display "xp4")))))
(define (test x y)
  (findmin x y)
  (findmax x y))

(define (testx a b c d)
  (findmin (make-interval a b) (make-interval c d))
  (findmax (make-interval a b) (make-interval c d)))



    
  