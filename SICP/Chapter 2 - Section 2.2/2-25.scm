;; Exercise 2.25.  
;; Give combinations of cars and cdrs that will pick 7 from each of
;; the following lists:

(define x '(1 3 (5 7) 9))
(car (cdr (car  (cdr (cdr x)))))

(define y '((7)))
(car (car y))

(define z '(1 (2 (3 (4 (5 (6 7)))))))
(car (cdr (car (cdr (car (cdr (car (cdr (car (cdr (car (cdr z))))))))))))