#lang sicp

(define (prod f a next b)
  (if (> a b)
      1
      (* (f a) (prod f (next a) next b))))

(define (inc x) (+ x 1))
(define (id x) x)

(define (fact x)
  (prod id 1 inc x))

(define (pi)
  (define (only-even k)
    (if (even? k)
        k
        (+ k 1)))
  (define (only-odd k)
    (if (even? k)
        (+ k 1)
        k))
  (define (term k)
    (/ (only-even k) (only-odd k)))
  (* 2 (prod term 1.0 inc 1000000)))