#lang sicp

(define (make-list n f)
  (if (= n 0)
      nil
      (cons (f n) (make-list (- n 1) f))))

(define (sum f list)
  (if (eq? list nil)
      0
      (+ (f (car list)) (sum f (cdr list)))))

(define (inv x) (/ 1 x))
(define (id x) x)