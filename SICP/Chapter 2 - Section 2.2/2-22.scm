;; Exercise 2.22. 
;; Louis Reasoner tries to rewrite the first square-list procedure of
;; exercise 2.21 so that it evolves an iterative process:

(define (square-list items)
  (define (iter things answer)
    (if (null? things)
        answer
        (iter (cdr things) 
              (cons (square (car things))
                    answer))))
  (iter items nil))

;; Unfortunately, defining square-list this way produces the answer list
;; in the reverse order of the one desired. Why?

Because we are cons-ing in this order -> (cons int list), e.g. (cons '3 '(1 2)),
which creates the new list (3 1 2)

;; Louis then tries to fix his bug by interchanging the arguments to cons:

(define (square-list items)
  (define (iter things answer)
    (if (null? things)
        answer
        (iter (cdr things)
              (cons answer
                    (square (car things))))))
  (iter items nil))

;; This doesn't work either. Explain. 

Now we're cons-ing by "appending" (for want of a better word) an integer onto a list, 
i.e. (cons list int). So if we try (cons '(3) '4) we end up with ((3).4). If we change
> (cons answer (square (car things)))
to
> (append answer (list (square (car things))))
then we end up with a list.

