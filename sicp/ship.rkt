#lang sicp

(define (I a) a)
(define (K a b) a)
(define (KI a b) ((K I a) b))
(define (ship . args)
  (cond ((= (length args) 2)
         (K (car args)
            (cadr args)))
        ((= (length args) 1)
         (I (car args)))
        (else (KI (car args)
                  (apply ship (cdr args))))))
(ship (ship (ship (ship ship) (ship (ship (ship (ship ship))) (ship (ship ship))(ship (ship (ship ship)))))))
