;; Exercise 1.19.   
;; There is a clever algorithm for computing the Fibonacci numbers in a 
;; logarithmic number of steps ...

For T(a,b), a <- bq + aq + ap
            b <- bp + aq
For T(a',b'), where a' = bq + ap + ap
                    b' = bp + aq
                    
            a' <- (bp + aq)q + (bq + aq + ap)q + (bq + aq + ap)p = 2bpq + 2aq^2 + bq^2 + ap^2 + 2pq
            b' <- (bp + aq)p + (bq + aq + ap)q = bp^2 + 2apq + bq^2 + aq^2
            
Looking at b' (because it's the less complicated looking one), 

b' <- bp^2 + 2apq + bq^2 + aq^2

But we want it in the form b <- bp + aq
So with a little rearranging
b' <- b(q^2 + p^2) + a(2pq + q^2)

Therefore:
    p' = (q^2 + p^2)
    q' = (2pq + q^2)
            
    
    
(define (square x)
  (* x x))

(define (fib n)
  (fib-iter 1 0 0 1 n))

(define (fib-iter a b p q count)
  (cond ((= count 0) b)
        ((even? count)
         (fib-iter a
                   b
                   (+ (square p) (square q))
                   (+ (* 2 p q) (square q))
                   (/ count 2)))
        (else (fib-iter (+ (* b q) (* a q) (* a p))
                        (+ (* b p) (* a q))
                        p
                        q
                        (- count 1)))))
