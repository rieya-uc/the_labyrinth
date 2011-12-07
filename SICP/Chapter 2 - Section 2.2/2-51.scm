#lang scheme
(require (planet "sicp.ss" ("soegaard" "sicp.plt" 2 1)))

;; Exercise 2.51. 
;; Define the below operation for painters. Below takes two painters as 
;; arguments. The resulting painter, given a frame, draws with the first 
;; painter in the bottom of the frame and with the second painter in the
;; top. Define below in two different ways -- first by writing a procedure
;; that is analogous to the beside procedure given above, and again in 
;; terms of beside and suitable rotation operations (from exercise 2.50). 

;; Note: The picture language library I'm using is slightly different to the 
;; book's. Transform-painter takes 3 arguments and painter as optional.

(define wave einstein)

(define (below1 p1 p2)
  (let ((split-point (make-vect 0.0 0.5)))
    (let ((paint-bottom
           ((transform-painter (make-vect 0.0 0.0)
                               (make-vect 1.0 0.0)
                               split-point)
            p1))
          (paint-top
           ((transform-painter split-point
                               (make-vect 1.0 0.5)
                               (make-vect 0.0 1.0))
            p2)))
      (lambda (frame)
        (paint-bottom frame)
        (paint-top frame)))))

(define (below2 p1 p2)
  (rotate90 (beside (rotate270 p1) (rotate270 p2))))
  
  
(paint (below1 wave wave))
(paint (below2 wave wave))
                              
                              
  
   

