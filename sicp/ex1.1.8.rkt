#lang sicp
(define (square x)
  (* x x))

(define (cube-root x)
  (define (improve guess)
    (/ (+ (/ x (square guess)) (* 2 guess)) 3))
  (define (good-enough? old-guess new-guess)
    (< (abs (- old-guess new-guess)) 0.001))
  (define (cube-root-iter old-guess new-guess)
    (if (good-enough? old-guess new-guess)
        new-guess
        (cube-root-iter new-guess
                        (improve new-guess))))
  (cube-root-iter x 1.0))