#lang scheme
(require (planet "sicp.ss" ("soegaard" "sicp.plt" 2 1)))

;; Exercise 2.52.  
;; Make changes to the square limit of wave shown in figure 2.9 by working
;; at each of the levels described above. In particular:

;; a.  Add some segments to the primitive wave painter of exercise  2.49 
;;    (to add a smile, for example).

;; b.  Change the pattern constructed by corner-split (for example, by using 
;;     only one copy of the up-split and right-split images instead of two).

;; c.  Modify the version of square-limit that uses square-of-four so as to 
;;     assemble the corners in a different pattern. (For example, you might 
;;     make the big Mr. Rogers look outward from each corner of the square.) 

;; Note: The picture language library I'm using is slightly different to the 
;; book's. Transform-painter takes 3 arguments and painter as optional.

; a. wave with a smile
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
                      (make-segment (make-vect 0.16 0.6) (make-vect 0 0.84))
                      (make-segment (make-vect 0.46 0.74) (make-vect 0.48 0.72))
                      (make-segment (make-vect 0.48 0.72) (make-vect 0.52 0.72))
                      (make-segment (make-vect 0.52 0.72) (make-vect 0.54 0.74)))))
                                   

; b. corner-split variation
(define (right-split painter n)
  (if (= n 0)
      painter
      (let ((smaller (right-split painter (- n 1))))
        (beside painter (below smaller smaller)))))
(define (up-split painter n)
  (if (= n 0)
      painter
      (let ((smaller (up-split painter (- n 1))))
        (below painter (beside smaller smaller)))))
(define (corner-split painter n)
  (if (= n 0)
      painter
      (let ((up (up-split painter (- n 1)))
            (right (right-split painter (- n 1)))
            (corner (corner-split painter (- n 1))))
;        (let ((top-left (beside up up))
;              (bottom-right (below right right))
;              (corner (corner-split painter (- n 1))))
          (beside (below painter up)
                  (below right corner)))))

; c. square limit variation
(define (square-of-four tl tr bl br)
  (lambda (painter)
    (let ((top (beside (tl painter) (tr painter)))
          (bottom (beside (bl painter) (br painter))))
      (below bottom top))))

(define (flipped-pairs painter)
  (let ((combine4 (square-of-four identity flip-vert
                                  identity flip-vert)))
    (combine4 painter)))

(define (square-limit painter n)
  (let ((combine4 (square-of-four flip-vert rotate180
                                  identity flip-horiz)))
    (combine4 (corner-split painter n))))

                              
  
   

