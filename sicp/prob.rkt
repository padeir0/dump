#lang sicp

(define data '((0 25)
               (1 20)
               (2 3)
               (3 1)
               (4 1)))

(define value car)
(define abs-freq cadr)

(define (sum f list)
  (if (eq? list nil)
      0
      (+ (f (car list)) (sum f (cdr list)))))

(define (ponderar-item item)
  (* (abs-freq item) (value item)))

(define n (sum abs-freq data))
(define media (/ (sum ponderar-item data) n))

(define (desvio-item item)
  (* (abs-freq item) (abs (- (value item) media))))

(define (square x) (* x x))

(define (vari-item item)
  (* (abs-freq item) (square (- (value item) media))))

(define desvio-medio (/ (sum desvio-item data) n))
(define variancia (/ (sum vari-item data) n))
(define desvio-padrao (sqrt variancia))

(display "n = ")
(display n)
(newline)

(display "media = ")
(display media)
(display " = ")
(display (exact->inexact media))
(newline)

(display "desvio medio = ")
(display desvio-medio)
(display " = ")
(display (exact->inexact desvio-medio))
(newline)

(display "variancia = ")
(display variancia)
(display " = ")
(display (exact->inexact variancia))
(newline)

(display "desvio padrao = ")
(display desvio-padrao)
(newline)