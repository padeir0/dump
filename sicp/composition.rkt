#lang sicp

(define (!= a b)
  (not (= a b)))

(define (iter f times)
  (define (iter-help f n)
    (f n)
    (cond ((!= (+ n 1) times) (iter-help f (+ n 1)))))
  (iter-help f 0))

(define (disp n)
  (display n)
  (display " ")
  n)

(define (compose a b)
  (lambda (x) (b (a x))))

(define (tree-apply f . args)
  (if (= (length args) 2)
      (f (car args) (cadr args))
      (begin
        (f (car args)
           (apply tree-apply f (cdr args))))))

(define (square n)
  (* n n))

(define (tree-compose . args) (apply tree-apply compose args))

(define (dec n)
  (- n 1))

(define (inc n)
  (+ n 1))

