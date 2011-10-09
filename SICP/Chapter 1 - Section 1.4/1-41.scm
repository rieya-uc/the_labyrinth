;; Exercise 1.41.  
;; Define a procedure double that takes a procedure of one argument as 
;; argument and returns a procedure that applies the original procedure
;; twice. For example, if inc is a procedure that adds 1 to its argument,
;; then (double inc) should be a procedure that adds 2. What value is 
;; returned by

;; (((double (double double)) inc) 5)

(define (inc n) (+ n 1))

(define (double f)
  (lambda (x)
    (f (f x))))

;; Before running it through Scheme, lets see if I can work out
;; what (((double (double double)) inc) 5) does.

(((double (double double)) inc) 5)

double applies the function twice, so (double (double double)) would
apply (double double) twice. That gives us 
      ((((double double) (double double)) inc) 5)
           16      8        4      2       1
i.e. 5 + 16 = 21.

Not convinced? Longer explanation below...

Ok, this bit (double double) returns 
      (lambda (x)
        (double (double x)))
(I'm going to call this g for now)

Which means (double (double double)) returns
      (double g)
      (lambda (x)
        (g (g x)))

Therefore, ((double (double double)) inc)
      ((double g) inc)
      (lambda (inc)
        (g (g inc)))
      
That is, ((double (double double)) inc) returns the function
     (g (g inc)) 
where g is the function
     (double (double x))
     
If I unravel it:
    ((g (g inc)) 5)
    ((g (double (double inc))) 5)   <----- note the replacement of x with inc
    ((double (double (double (double inc)))) 5)
    ((double (double (double (inc (inc x))))) 5)
    ((double (double (inc (inc (inc (inc x)))))) 5)
    ...
    ((inc (inc (inc (inc (inc (inc (inc (inc (inc (inc (inc (inc (inc (inc (inc (inc x)))))))))))))))) 5)
    (inc (inc (inc (inc (inc (inc (inc (inc (inc (inc (inc (inc (inc (inc (inc (inc 5))))))))))))))))
    ...
    21

Which is the same answer Scheme prints out (yay!).
    
    


   
    
     
       
  
 
 

