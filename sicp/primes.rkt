#lang sicp

(define (mdc a b)
  (if (= b 0)
      a
      (mdc b (remainder a b))))

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

(define (prime? n)
  (= (smallest-divisor n) n))

(define (expmod base exp m)
  (cond ((= exp 0) 1)
        ((even? exp)
         (remainder (square (expmod base (/ exp 2) m)) m))
        (else (remainder (* base (expmod base (- exp 1) m)) m))))

(define (fermat-test n)
  (define (try-it a)
    (= (expmod a n n) a))
  (try-it (+ 1 (random (- n 1)))))

(define (fast-prime? n times)
  (cond ((= times 0) true)
        ((fermat-test n) (fast-prime? n (- times 1)))
        (else false)))

(define (display-line n)
  (display n)
  (display "\n"))

(define (find-primes n is-prime?)
  (cond ((< 1 n) (cond ((is-prime? n) nil))
                 (find-primes (- n 1) is-prime?))))

(define (time f)
  (define start (runtime))
  (f)
  (define end (runtime))
  (- end start))