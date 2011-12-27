;; Exercise 2.55.  
;; Eva Lu Ator types to the interpreter the expression

;; (car ''abracadabra)

;; To her surprise, the interpreter prints back quote. Explain. 

; Footnote 34 says that 'a is short for (quote a).
; Therefore ''abra is short for (quote (quote abra)) 
; and (car ''abra) is short for (car (quote (quote abra))).
; (car (quote (quote abra))) will therefore return quote.

