;; Exercise 2.45.  
;; Right-split and up-split can be expressed as instances of a general 
;; splitting operation. Define a procedure split with the property that 
;; evaluating 
   ;; (define right-split (split beside below))
   ;; (define up-split (split below beside))
;; produces procedures right-split and up-split with the same behaviors
;; as the ones already defined.

; The version of scheme I'm using doesn't have wave, using einstein instead.
; NB: use (paint wave) to display wave (or some other picture)
(define wave einstein)

(define (split position1 position2)
  (lambda (painter)
    (position1 painter (position2 painter painter))))

(define right-split (split beside below))
(define up-split (split below beside))

(paint (right-split wave))
(paint (up-split wave))