#lang sicp

(define (accumulate filter combiner null-value term a next b)
  (if (< b a)
      null-value
      (combiner (accumulate filter combiner null-value term (next a) next b)
                (if (filter a)
                    (term a)
                    null-value))))

(define (accumulate-iter filter combiner null-value term a next b)
  (define (iter a result)
    (if (< b a)
        result
        (if (filter a)
            (iter (next a) (combiner result (term a)))
            (iter (next a) result))))
  (iter a null-value))

(define (id x) x)
(define (inc x) (+ x 1))

(define (prime? n)
  (define (divides? a b)
    (= (remainder b a) 0))
  (define (square a)
    (* a a))
  (define (smallest-divisor n)
    (define (find-divisor n test-divisor)
      (cond ((> (square test-divisor) n) n)
            ((divides? test-divisor n) test-divisor)
            (else (find-divisor n (+ test-divisor 1)))))
    (find-divisor n 2))
  (if (< 1 n)
      (= (smallest-divisor n) n)
      #f))

(define (sum-primes a b)
  (accumulate prime? + 0 id a inc b))

(define (sum-primes-iter a b)
  (accumulate-iter prime? + 0 id a inc b))

(define (test f a b)
  (if (< b a)
      #t
      (if (f a)
          (test f (inc a) b)
          #f)))

(test (lambda (x) (= (sum-primes 0 x) (sum-primes-iter 0 x))) 0 100)

(define (gcd a b)
  (if (= b 0)
      a
      (gcd b (remainder a b))))

(define (relative-prime a b)
  (= (gcd a b) 1))

(define (relative-prime-product a)
  (define (filter x)
    (relative-prime a x))
  (accumulate-iter filter * 1 id 0 inc a))