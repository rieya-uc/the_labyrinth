;; Exercise 2.9.  
;; The width of an interval is half of the difference between its upper and
;; lower bounds. The width is a measure of the uncertainty of the number 
;; specified by the interval. For some arithmetic operations the width of 
;; the result of combining two intervals is a function only of the widths 
;; of the argument intervals, whereas for others the width of the combination
;; is not a function of the widths of the argument intervals. Show that the
;; width of the sum (or difference) of two intervals is a function only of the
;; widths of the intervals being added (or subtracted). Give examples to show
;; that this is not true for multiplication or division. 


If we have two pairs, x = (lx, ux) and y = (ly, uy):-

(a). The result of combining two intervals and taking its width:
(width (add-interval x y))
(width (make-interval (+ (lower-bound x) (lower-bound y))
                      (+ (upper-bound x) (upper-bound y))))
(width (make-interval (+ lx ly)
                      (+ ux uy)))
(width (cons (+ lx ly) (+ ux uy)))
(width ((+ lx ly) (+ ux uy))) --> we have a new pair v=((+ lx ly) (+ ux uy))
                              --> where (+ lx ly)=lower-bound and
                              --> (+ ux uy)=upper-bound
(/ (- (upper-bound v) (lower-bound v)) 2)
(/ (- (+ ux uy) (+ lx ly)) 2)

In non-Scheme notation:
       [(ux + uy) - (lx + ly)] / 2

(b). The result of individually taking the widths of two intervals
and adding the widths

(+ (width x) (width y))
(+ (/ (- (upper-bound x) (lower-bound x)) 2)
   (/ (- (upper-bound y) (lower-bound y)) 2))
(+ (/ (- ux lx) 2)
   (/ (- uy ly) 2))

Rearranging:
((- ux lx)/2 + (- uy ly)/2)
[(ux - lx) + (uy - ly)] /2
[(ux + uy) - lx - ly] /2
[(ux + uy) - (lx + ly)] /2  --> which is the same result we get in (a)

I.e. the width of the sum of two intervals can be computed by taking the 
individual widths of the two intervals.

However this doesn't hold for multiplication or division.

(c). Multiplying the widths of x and y
(* (width x) (width y))
(* (/ (- (upper-bound x) (lower-bound x)) 2)
   (/ (- (upper-bound y) (lower-bound y)) 2))
(* (/ (- ux lx) 2)
   (/ (- uy ly) 2))

Which is:
((ux - lx)/2 * (uy - ly)/2)
[(ux - lx) * (uy - ly)]/2

(d). Multiplying x and y and taking the resultant's width
(width (mul-interval x y))
(width (make-interval (min (* lx ly)
                           (* lx uy)   
                           (* ux ly)
                           (* ux uy))
                      (max (* lx ly)
                           (* lx uy)
                           (* ux ly)
                           (* ux uy))))

As we need to use min and max, finding the multiple (and division) isn't 
solely a function of the widths.



(define (width x)
  (/ (- (upper-bound x) (lower-bound x))
     2))

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

(define (div-interval x y)
  (mul-interval x 
                (make-interval (/ 1.0 (upper-bound y))
                               (/ 1.0 (lower-bound y)))))


(define intx (make-interval 3.4 5.2)) 
(define inty (make-interval 1.3 8.5))

(width (add-interval intx inty))
(+ (width intx) (width inty))
