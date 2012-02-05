;; Exercise 2.73.  

;; Section 2.3.2 described a program that performs symbolic differentiation:

; (define (deriv exp var)
;  (cond ((number? exp) 0)
;        ((variable? exp) (if (same-variable? exp var) 1 0))
;        ((sum? exp)
;         (make-sum (deriv (addend exp) var)
;                   (deriv (augend exp) var)))
;        ((product? exp)
;         (make-sum
;           (make-product (multiplier exp)
;                         (deriv (multiplicand exp) var))
;           (make-product (deriv (multiplier exp) var)
;                         (multiplicand exp))))
;        <more rules can be added here>
;        (else (error "unknown expression type -- DERIV" exp))))

;; We can regard this program as performing a dispatch on the type of the 
;; expression to be differentiated. In this situation the "type tag" of 
;; the datum is the algebraic operator symbol (such as +) and the 
;; operation being performed is deriv. We can transform this program
;; into data-directed style by rewriting the basic derivative procedure as

; (define (deriv exp var)
;    (cond ((number? exp) 0)
;          ((variable? exp) (if (same-variable? exp var) 1 0))
;          (else ((get 'deriv (operator exp)) (operands exp)
;                                             var))))
; (define (operator exp) (car exp))
; (define (operands exp) (cdr exp))

;; a.  Explain what was done above. Why can't we assimilate the
;;     predicates number? and same-variable? into the data-directed dispatch?

      ; deriv now looks up the correct derivation procedure in the table.
      ; We can't assimilate number? and same-variable? as there's no type-tag
      ; (e.g. operator) to look up.

;; b.  Write the procedures for derivatives of sums and products, and 
;;     the auxiliary code required to install them in the table used by the
;;     program above.

(define (deriv-sum exp var)
  (make-sum (deriv (addend exp) var)
            (deriv (augend exp) var)))
(define (deriv-product exp var)
  (make-sum
   (make-product (multiplier exp)
                 (deriv (multiplicand exp) var))
   (make-product (deriv (multiplier exp) var)
                 (multiplicand exp))))
(define (install-sum)
  (put 'deriv '+ deriv-sum))
(define (install-product)
  (put 'deriv '* deriv-product))
   

        

;; c.  Choose any additional differentiation rule that you like, such as 
;;     the one for exponents (exercise 2.56), and install it in this 
;;     data-directed system.

(define (deriv-exponent base exponent)
  (make-product
   (make-product (exponent exp)
                 (make-exponentiation (base exp)
                                      (make-sub (exponent exp) 1)))
   (deriv (base exp) var)))
  
(define (make-exponentiation base exponent)
  (cond ((=number? exponent 0) 1)
        ((=number? exponent 1) base)
        (else
         (list '** base exponent))))

(define (install-expt)
  (put 'deriv '** deriv-exponent))

;; d.  In this simple algebraic manipulator the type of an expression 
;;     is the algebraic operator that binds it together. Suppose, however, 
;;     we indexed the procedures in the opposite way, so that the dispatch
;;     line in deriv looked like

; ((get (operator exp) 'deriv) (operands exp) var)

;;     What corresponding changes to the derivative system are required? 

; We need to change the way we install the procedures
(put '+ 'deriv deriv-sum)
(put '* 'deriv deriv-product)
(put '** 'deriv deriv exponent)
