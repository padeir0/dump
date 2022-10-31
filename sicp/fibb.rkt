#lang sicp

(define (fibb n)
  (cond ((= n 0) 0)
        ((= n 1) 1)
        (else (+ (fibb (- n 1))
                 (fibb (- n 2))))))

(define (fibb2 n)
  (define (fibb-iter a b count)
    (if (= count 0)
        b
        (fibb-iter (+ a b) a (- count 1))))
  (fibb-iter 1 0 n))
