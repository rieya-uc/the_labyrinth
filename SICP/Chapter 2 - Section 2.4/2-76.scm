;; Exercise 2.76.  
;; As a large system with generic operations evolves, new types of data objects
;; or new operations may be needed. For each of the three strategies -- generic
;; operations with explicit dispatch, data-directed style, and 
;; message-passing-style -- describe the changes that must be made to a system 
;; in order to add new types or new operations. Which organization would be 
;; most appropriate for a system in which new types must often be added? Which
;; would be most appropriate for a system in which new operations must often be
;; added? 

; Generic operations
; Each group of procedures would need be in charge of making sure the correct
; procedures for their type is called.

; Data-directed style
; An overall table would need to be kept, and each group of operations would
; add themselves to the table.

; Message-passing style
; The operations would need to keep a dispatch procedure which sorts out
; its own type.

; New operations - data-directed
; New types - message-passing