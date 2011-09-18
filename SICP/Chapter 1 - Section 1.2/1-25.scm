;; Exercise 1.25. 
;; Alyssa P. Hacker complains that we went to a lot of extra work in writing
;; expmod. After all, she says, since we already know how to compute 
;; exponentials, we could have simply written

(define (expmod base exp m)
  (remainder (fast-expt base exp) m))

(define (fast-expt b n)
  (cond ((= n 0) 1)
        ((even? n) (square (fast-expt b (/ n 2))))
        (else (* b (fast-expt b (- n 1))))))


;; Is she correct? Would this procedure serve as well for our fast prime tester? 
;; Explain.

;; As a reminder, here's the original expmod.

(define (expmod_old base exp m)
  (cond ((= exp 0) 1)
        ((even? exp)
         (remainder (square (expmod_old base (/ exp 2) m))
                    m))
        (else
         (remainder (* base (expmod_old base (- exp 1) m))
                    m))))

;; The problem with Alyssa's expmod is that we run into very large numbers
;; early on. 

;; First of all let's see what happens with Alyssa's expmod
(expmod 7 6 5)
(remainder (fast-expt 7 6) 5)
(remainder (square (fast-expt 7 3)) 5)
(remainder (square (* 7 (fast-expt 7 2))) 5)
(remainder (square (* 7 (square (fast-expt 7 1)))) 5)
(remainder (square (* 7 (square (* 7 (fast-expt 7 0))))) 5)
(remainder (square (* 7 (square (* 7 1)))) 5)
(remainder (square (* 7 (square 7))) 5)
(remainder (square (* 7 49) 5))
(remainder (square 343) 5)
(remainder 117649 5)
4

;; At each step, the base is either squared or multipled by its 
;; original value, until exp reaches zero.
;;
;; Compare this to the original expmod

(expmod 7 6 5)
(remainder (square (expmod 7 3 5)) 5)
(remainder (square (remainder (* 7 (expmod 7 2 5)) 5)) 5)
(remainder (square (remainder (* 7 (remainder (square (expmod 7 1 5)) 5)) 5)) 5)
(remainder (square (remainder (* 7 (remainder (square (remainder (* 7 (expmod 7 0 5)) 5)) 5)) 5)) 5)
(remainder (square (remainder (* 7 (remainder (square (remainder (* 7 1) 5)) 5)) 5)) 5)
(remainder (square (remainder (* 7 (remainder (square (remainder 7 5)) 5)) 5)) 5)
(remainder (square (remainder (* 7 (remainder (square 2) 5)) 5)) 5)
(remainder (square (remainder (* 7 (remainder 4 5)) 5)) 5)
(remainder (square (remainder (* 7 4) 5)) 5)
(remainder (square (remainder 28 5)) 5)
(remainder (square 3) 5)
(remainder 9 5)
4

;; This time, instead of squaring the base value several times then taking 
;; the remainder, we first take the remainder, then square. Although there 
;; are more steps, we avoid large numbers by doing so.

