#lang sicp

(define (id x) x)
(define (sum f list)
  (if (eq? list nil)
      0
      (+ (f (car list)) (sum f (cdr list)))))

(define (inverse x) (/ 1.0 x))

(define (parallel-reg lst)
  (inverse (sum inverse lst)))

(define (iter-regs lst value)
  (if (eq? lst nil)
      0
      (begin
        (display (parallel-reg (list (car lst) value)))
        (display "\n")
        (iter-regs (cdr lst) value))))

(iter-regs '(47 68 100 220 470 680 1000) 1000)