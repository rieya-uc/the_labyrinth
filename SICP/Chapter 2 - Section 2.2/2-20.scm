;; Exercise 2.20.  
;; The procedures +, *, and list take arbitrary numbers of arguments. 
;; One way to define such procedures is to use define with dotted-tail 
;; notation. In a procedure definition, a parameter list that has a dot
;; before the last parameter name indicates that, when the procedure is 
;; called, the initial parameters (if any) will have as values the initial
;; arguments, as usual, but the final parameter's value will be a list of 
;; any remaining arguments.
;; [...]
;; Use this notation to write a procedure same-parity that takes one or more
;; integers and returns a list of all the arguments that have the same even-odd
;; parity as the first argument. 

(define (same-parity x . y)
  (let ((parity (remainder x 2)))
    (define (same-parity-iter result items)
      (cond ((null? items) result)
            ((= parity (remainder (car items) 2))
             (same-parity-iter (append result (list (car items))) (cdr items)))
            (else
             (same-parity-iter result (cdr items)))))
    (same-parity-iter (list x) y)))

(same-parity 1 2 3 4 5 6 7)
(same-parity 2 3 4 5 6 7)
