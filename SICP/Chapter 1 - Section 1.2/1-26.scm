;; Exercise 1.26.  
;; Louis Reasoner is having great difficulty doing exercise 1.24. 
;; His fast-prime? test seems to run more slowly than his prime? test. 
;; Louis calls his friend Eva Lu Ator over to help. When they examine 
;; Louis's code, they find that he has rewritten the expmod procedure 
;; to use an explicit multiplication, rather than calling square:

(define (expmod base exp m)
  (cond ((= exp 0) 1)
        ((even? exp)
         (remainder (* (expmod base (/ exp 2) m)
                       (expmod base (/ exp 2) m))
                    m))
        (else
         (remainder (* base (expmod base (- exp 1) m))
                    m))))

;; "I don't see what difference that could make," says Louis. 
;; "I do." says Eva. "By writing the procedure like that, you have 
;; transformed the (log n) process into a (n) process." Explain. 

Here's a snippet of the original expmod:
    ((even? exp)
        (remainder (square (expmod base (/ exp 2) m))
            m))
    
Every time exp is even we call expmod and halve exp, until exp reaches one.
That is, this line calls expmod logN times.

Louis changes the line to this:
    ((even? exp)
        (remainder (* (expmod base (/ exp 2) m)
                      (expmod base (/ exp 2) m))
            m))

We're still dividing exp by two each time, but negating any advantage this 
has by calling expmod twice. (It reminds me a little of the fibonacci procedure
mentioned earlier, as both wastefully repeat calculations.)

Exp is even logN times. Each time, the number of expmod calls is squared.
For example, we start of with one expmod, which calls expmod twice. Both 
those branches call expmod twice, so now we have four calls, then eight...
(If this is confusing, try drawing a tree diagram).
That is, this happens logN^2 times, which equals N.







