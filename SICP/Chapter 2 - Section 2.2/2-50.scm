#lang scheme
(require (planet "sicp.ss" ("soegaard" "sicp.plt" 2 1)))

;; Exercise 2.50.  
;; Define the transformation flip-horiz, which flips painters horizontally,
;; and transformations that rotate painters counterclockwise by 180 degrees
;; and 270 degrees

;; Note: The picture language library I'm using is slightly different to the 
;; book's. Transform-painter takes 3 arguments and painter as optional.

(define wave einstein)

(define (flip-horizx painter)
  ((transform-painter (make-vect 1 0)
                      (make-vect 0 0)
                      (make-vect 1 1))
   painter))

(define (cc180 painter)
  ((transform-painter (make-vect 1 1)
                      (make-vect 0 1)
                      (make-vect 1 0))
   painter))

(define (cc270 painter)
  ((transform-painter (make-vect 0 1)
                      (make-vect 0 0)
                      (make-vect 1 1))
   painter))

(paint (flip-horizx wave))
(paint (cc180 wave))
(paint (cc270 wave))
  
  
   

