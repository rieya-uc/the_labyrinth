;; Exercise 2.44. 
;; Define the procedure up-split used by corner-split. It is similar to
;; right-split, except that it switches the roles of below and beside. 

; The version of scheme I'm using doesn't have wave, using einstein instead.
; NB: use (paint wave) to display wave (or some other picture)
(define wave einstein)

(define (up-split painter n)
  (if (= n 0)
      painter
      (let ((horiz-split (up-split painter (- n 1))))
        (below painter (beside horiz-split horiz-split)))))
      
(define (right-split painter n)
  (if (= n 0)
      painter
      (let ((smaller (right-split painter (- n 1))))
        (beside painter (below smaller smaller)))))

(define (corner-split painter n)
  (if (= n 0)
      painter
      (let ((up (up-split painter (- n 1)))
            (right (right-split painter (- n 1))))
        (let ((top-left (beside up up))
              (bottom-right (below right right))
              (corner (corner-split painter (- n 1))))
          (beside (below painter top-left)
                  (below bottom-right corner))))))

(paint (corner-split wave 4))

