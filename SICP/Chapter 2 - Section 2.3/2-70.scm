;; Exercise 2.70.  
;; The following eight-symbol alphabet with associated relative frequencies was 
;; designed to efficiently encode the lyrics of 1950s rock songs. (Note that 
;; the "symbols" of an "alphabet" need not be individual letters.)

;; A 	2 	NA 	16
;; BOOM 	1 	SHA 	3
;; GET 	2 	YIP 	9
;; JOB 	2 	WAH 	1

;; Use generate-huffman-tree (exercise 2.69) to generate a corresponding 
;; Huffman tree, and use encode (exercise 2.68) to encode the following message:

;; Get a job
;; Sha na na na na na na na na
;; Get a job
;; Sha na na na na na na na na
;; Wah yip yip yip yip yip yip yip yip yip
;; Sha boom

;; How many bits are required for the encoding? What is the smallest number of 
;; bits that would be needed to encode this song if we used a fixed-length code 
;; for the eight-symbol alphabet? 
       
; (1 1 1 1 1 1 1 0 0 1 1 1 1 0 1 1 1 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 0 0 1 1 1 1 0 1 1 1 0 0 0 0 0 0 0 0 0 1 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 1 1 0 1 1 0 1 1)
; 84 bits

; Eight symbols would need 3 bits per symbol. The song would need 108 bits.

(define words
  '((A 2) (NA 16) (BOOM 1) (SHA 3) (GET 2) (YIP 9) (JOB 2) (WAH 1)))

(define lyrics-tree
  (generate-huffman-tree words))

(define message
  '(Get a job
        Sha na na na na na na na na
        Get a job
        Sha na na na na na na na na
        Wah yip yip yip yip yip yip yip yip yip
        Sha boom))

(encode message lyrics-tree)
(length (encode message lyrics-tree))




;; Code from 2-69
(define (generate-huffman-tree pairs)
  (successive-merge (make-leaf-set pairs)))

(define (successive-merge set)
  (define (iter new-set)
    (cond ((null? (cdr new-set)) new-set)
          ((= (length new-set) 2) (make-code-tree (car new-set) (cadr new-set)))
          (else
           (iter (adjoin-set 
                  (make-code-tree (car new-set) (cadr new-set)) (cddr new-set))))))
  (iter set))

  
;; Code from book
(define (make-leaf symbol weight)
  (list 'leaf symbol weight))
(define (leaf? object)
  (eq? (car object) 'leaf))
(define (symbol-leaf x) (cadr x))
(define (weight-leaf x) (caddr x))

(define (make-code-tree left right)
  (list left
        right
        (append (symbols left) (symbols right))
        (+ (weight left) (weight right))))

(define (left-branch tree) (car tree))

(define (right-branch tree) (cadr tree))
(define (symbols tree)
  (if (leaf? tree)
      (list (symbol-leaf tree))
      (caddr tree)))
(define (weight tree)
  (if (leaf? tree)
      (weight-leaf tree)
      (cadddr tree)))

(define (decode bits tree)
  (define (decode-1 bits current-branch)
    (if (null? bits)
        '()
        (let ((next-branch
               (choose-branch (car bits) current-branch)))
          (if (leaf? next-branch)
              (cons (symbol-leaf next-branch)
                    (decode-1 (cdr bits) tree))
              (decode-1 (cdr bits) next-branch)))))
  (decode-1 bits tree))
(define (choose-branch bit branch)
  (cond ((= bit 0) (left-branch branch))
        ((= bit 1) (right-branch branch))
        (else (error "bad bit -- CHOOSE-BRANCH" bit))))
(define (adjoin-set x set)
  (cond ((null? set) (list x))
        ((< (weight x) (weight (car set))) (cons x set))
        (else (cons (car set)
                    (adjoin-set x (cdr set))))))
(define (make-leaf-set pairs)
  (if (null? pairs)
      '()
      (let ((pair (car pairs)))
        (adjoin-set (make-leaf (car pair)    ; symbol
                               (cadr pair))  ; frequency
                    (make-leaf-set (cdr pairs))))))

(define (encode message tree)
  (if (null? message)
      '()
      (append (encode-symbol (car message) tree)
              (encode (cdr message) tree))))

; Code from 2-68
(define (contains-symbol x symbol-list)
  (cond ((null? symbol-list) #f)
        ((eq? (car symbol-list) x) #t)
        (else
         (contains-symbol x (cdr symbol-list)))))

(define (encode-symbol symbol tree)
  (define (iter tree code)
    (cond ((and (leaf? tree) (eq? (symbol-leaf tree) symbol)) code)
          ((leaf? tree) #f)
          ((contains-symbol symbol (symbols tree))
           (or (iter (left-branch tree) (append code (list 0)))
               (iter (right-branch tree) (append code (list 1)))))
          (else #f)))
  (let ((result (iter tree '())))
    (if (eq? result #f)
        (error "ERROR - SYMBOL NOT IN TREE")
        result)))


        
