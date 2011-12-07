;; Exercise 2.48.  
;; A directed line segment in the plane can be represented as a pair 
;; of vectors -- the vector running from the origin to the start-point of
;; the segment, and the vector running from the origin to the end-point of
;; the segment. Use your vector representation from exercise 2.46 to define 
;; a representation for segments with a constructor make-segment and 
;; selectors start-segment and end-segment. 

(define (make-segment start-seg end-seg)
  (cons start-seg end-seg))
(define (start-segment s)
  (car s))
(define (end-segment s)
  (cdr s))

(define (make-vect x y)
  (cons x y))
(define (xcor-vect v)
  (car v))
(define (ycor-vect v)
  (cdr v))

(define (segments->painter segment-list)
  (lambda (frame)
    (for-each
     (lambda (segment)
       (draw-line
        ((frame-coord-map frame) (start-segment segment))
        ((frame-coord-map frame) (end-segment segment))))
     segment-list)))
