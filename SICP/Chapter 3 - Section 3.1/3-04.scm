;; Exercise 3.4.  
;; Modify the make-account procedure of exercise 3.3 by adding another local
;; state variable so that, if an account is accessed more than seven 
;; consecutive times with an incorrect password, it invokes the procedure 
;; call-the-cops. 

(define (make-account balance password)
  (let ((attempts 0))
  (define (withdraw amount)
    (if (>= balance amount)
        (begin (set! balance (- balance amount))
               balance)
        "Insufficient funds"))
  (define (deposit amount)
    (set! balance (+ balance amount))
    balance)
  (define (incorrect-password a) 
    (set! attempts (+ attempts 1))
    (if (> attempts 6) 
        "Calling the cops"
        "Incorrect password"))
  (define (dispatch p m)
    (if (eq? p password)
        (begin
          (set! attempts 0)
          (cond
            ((eq? m 'withdraw) withdraw)
            ((eq? m 'deposit) deposit)
            (else (error "Unknown request -- MAKE-ACCOUNT" m))))
        incorrect-password))
  dispatch))

(define acc (make-account 100 'secret-password))
((acc 'wrongpw 'withdraw) 100)
((acc 'wrongpw 'withdraw) 100)
((acc 'wrongpw 'withdraw) 100)
((acc 'wrongpw 'withdraw) 100)
((acc 'wrongpw 'withdraw) 100)
((acc 'wrongpw 'withdraw) 100)
((acc 'wrongpw 'withdraw) 100)
