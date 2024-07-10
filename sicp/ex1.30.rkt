#lang sicp

(define (sum term a next b)
  (define (iter a result)
    (if (< b a)
        result
        (iter (next a) (+ result (term a)))))
  (iter a 0))

(define (inc x) (+ x 1))
(define (id x) x)