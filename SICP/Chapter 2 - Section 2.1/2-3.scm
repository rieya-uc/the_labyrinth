;; Exercise 2.3.  
;; Implement a representation for rectangles in a plane. 
;; (Hint: You may want to make use of exercise 2.2.) 
;; In terms of your constructors and selectors, create procedures that compute
;; the perimeter and the area of a given rectangle. Now implement a different
;; representation for rectangles. Can you design your system with suitable 
;; abstraction barriers, so that the same perimeter and area procedures will
;; work using either representation? 
   
(define (make-segment start end) (cons start end))
(define (start-segment s) (car s))
(define (end-segment s) (cdr s))

(define (make-point x y) (cons x y))
(define (x-point p) (car p))
(define (y-point p) (cdr p))

(define (print-point p)
  (newline)
  (display "(")
  (display (x-point p))
  (display ",")
  (display (y-point p))
  (display ")"))

;; Takes in two points, bottom-left and top-right
(define (make-rectangle1 bl-x bl-y tr-x tr-y)
  (make-segment
   (make-point bl-x bl-y)
   (make-point tr-x tr-y)))

;; Takes in a bottom left point and a length and height
(define (make-rectangle2 bl length height)
  (make-segment bl (make-point (+ (x-point bl) length)
                               (+ (y-point bl) height))))
  
(define (perimeter rect)
  (let ((bl (start-segment rect))
        (tr (end-segment rect)))
    (+ (abs (* 2 (- (x-point tr) (x-point bl))))
       (abs (* 2 (- (y-point tr) (y-point bl)))))))

(define (area rect)
  (let ((bl (start-segment rect))
        (tr (end-segment rect)))
    (* (abs (- (x-point tr) (x-point bl)))
       (abs (- (y-point tr) (y-point bl))))))



(define rect (make-rectangle1 0 0 10 -10))
(perimeter rect)
(area rect)
(newline)
(define rect (make-rectangle2 (make-point 0 0) 10 10))
(perimeter rect)
(area rect)


  
             


