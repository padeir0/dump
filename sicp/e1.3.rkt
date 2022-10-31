#lang sicp

(define (apply-two-biggest f a b c)
  (cond ((> a b)
         (cond ((> b c) (f a b))
               (else (f a c))))
        (else
         (cond ((> a c) (f a b))
               (else (f b c))))
        ))

(define (square x)
  (* x x))

(define (sum-of-squares a b)
  (+ (square a) (square b)))

(define (answer a b c)
  (apply-two-biggest sum-of-squares a b c))