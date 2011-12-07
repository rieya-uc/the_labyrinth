#lang scheme
(require (planet "sicp.ss" ("soegaard" "sicp.plt" 2 1)))

;; Exercise 2.49.  
;; Use segments->painter to define the following primitive painters:
;; a.  The painter that draws the outline of the designated frame.
;; b.  The painter that draws an ``X'' by connecting opposite corners of 
;; the frame.
;; c.  The painter that draws a diamond shape by connecting the midpoints
;; of the sides of the frame.
;; d.  The wave painter. 

; Some preliminary defines to make things less cluttered

; It doesn't specify in the book that edge1 is always the line running
; from the origin to the bottom-right corner, and edge2 is the line 
; running upwards
(define (connecting-corner f) 
  (if (> (vector-xcor (frame-edge1 f)) (vector-xcor (frame-edge2 f)))
      (make-vect (vector-xcor (frame-edge1 f))
                 (vector-ycor (frame-edge2 f)))
      (make-vect (vector-xcor (frame-edge2 f))
                 (vector-ycor (frame-edge1 f)))))

; a - outline
(define (frame-outline f)
  (let ((o (frame-origin f))
        (e1 (frame-edge1 f))
        (e2 (frame-edge2 f))
        (c (connecting-corner f)))
    (segments->painter (list
                        (make-segment o e1)
                        (make-segment o e2)
                        (make-segment e1 c)
                        (make-segment e2 c)))))

; b - X
(define (frame-X f)
  (let ((o (frame-origin f))
        (e1 (frame-edge1 f))
        (e2 (frame-edge2 f))
        (c (connecting-corner f)))
    (segments->painter (list
                        (make-segment o c)
                        (make-segment e1 e2)))))

; c - diamond
(define (frame-diamond f)
  (let ((o (frame-origin f))
        (c (connecting-corner f)))
    (let ((mid1 (make-vect (/ (vector-xcor c) 2) (vector-ycor o)))
          (mid2 (make-vect (vector-xcor o) (/ (vector-ycor c) 2)))
          (mid3 (make-vect (/ (vector-xcor c) 2) (vector-ycor c)))
          (mid4 (make-vect (vector-xcor c) (/ (vector-ycor c) 2))))
      (segments->painter (list
                          (make-segment mid1 mid2)
                          (make-segment mid2 mid3)
                          (make-segment mid3 mid4)
                          (make-segment mid4 mid1))))))


; d - wave
(define wave
  (segments->painter (list
                      (make-segment (make-vect 0.26 0) (make-vect 0.39 0.5))
                      (make-segment (make-vect 0.39 0.5) (make-vect 0.3 0.6))
                      (make-segment (make-vect 0.3 0.6) (make-vect 0.16 0.4))
                      (make-segment (make-vect 0.16 0.4) (make-vect 0 0.64))
                      (make-segment (make-vect 0.4 0) (make-vect 0.5 0.3))
                      (make-segment (make-vect 0.5 0.3) (make-vect 0.6 0))
                      (make-segment (make-vect 0.74 0) (make-vect 0.6 0.44))
                      (make-segment (make-vect 0.6 0.44) (make-vect 0.99 0.16))
                      (make-segment (make-vect 0.99 0.36) (make-vect 0.74 0.64))
                      (make-segment (make-vect 0.74 0.64) (make-vect 0.6 0.64))
                      (make-segment (make-vect 0.6 0.64) (make-vect 0.64 0.84))
                      (make-segment (make-vect 0.64 0.84) (make-vect 0.6 0.99))
                      (make-segment (make-vect 0.4 0.99) (make-vect 0.36 0.84))
                      (make-segment (make-vect 0.36 0.84) (make-vect 0.4 0.64))
                      (make-segment (make-vect 0.4 0.64) (make-vect 0.3 0.64))
                      (make-segment (make-vect 0.3 0.64) (make-vect 0.16 0.6))
                      (make-segment (make-vect 0.16 0.6) (make-vect 0 0.84)))))
                      

(define mf (make-frame (make-vect 0 0) (make-vect 0.99 0) (make-vect 0 0.99)))
(define mf2 (make-frame (make-vect 0 0) (make-vect 0 0.99) (make-vect 0.99 0)))

;(paint (frame-outline mf))
;(paint (frame-outline mf2))
;(paint (frame-X mf))
;(paint (frame-X mf2))
;(paint (frame-diamond mf))
;(paint (frame-diamond mf2))
(paint wave)
       


