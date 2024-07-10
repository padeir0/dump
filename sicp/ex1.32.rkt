#lang sicp

(define (accumulate combiner null-value term a next b)
  (if (< b a)
      null-value
      (combiner (term a) (accumulate combiner null-value term (next a) next b))))

(define (sum term a next b)
  (accumulate + 0 term a next b))

(define (inc x) (+ x 1))
(define (id x) x)
(define (square x) (* x x))
(define (inc2 x) (+ x 2))

(define (sum-seq term a b)
  (sum term a inc b))

(define (sum-squares a b)
  (sum square a inc b))

(define (sum-evens a b)
  (if (even? a)
      (sum id a inc2 b)
      (sum id (inc a) inc2 b)))

(define (prod term a next b)
  (accumulate * 1 term a next b))

(define (prod-seq term a b)
  (prod term a inc b))

(define (fact x)
  (prod-seq id 1 x))

(define (accumulate-iter combiner null-value term a next b)
  (define (iter a result)
    (if (< b a)
        result
        (iter (next a) (combiner result (term a)))))
  (iter a null-value))

(define (sum-iter term a next b)
  (accumulate-iter + 0 term a next b))

(define (prod-iter term a next b)
  (accumulate-iter * 1 term a next b))

(define (fact-iter x)
  (prod-iter id 1 inc x))