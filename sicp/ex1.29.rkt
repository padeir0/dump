#lang sicp

(define (inc x) (+ x 1))

(define (sum f a next b)
  (if (> a b)
      0
      (+ (f a) (sum f (next a) next b))))

(define (integral f a b dx)
  (define (add-dx x) (+ x dx))
  (* (sum f (+ a (/ dx 2.0)) add-dx b)
     dx))

(define (square x) (* x x))

(define (half-circle x)
  (sqrt (- 1 (square x))))

(define (pi-one) (* 2 (integral half-circle -1 1 0.0005)))

(define (other-integral f a b n)
  (define h (/ (- b a) n))
  (define (next v) (+ v h))
  (* h (+ (f a) (f b) (sum f (+ a h) next (- b h)))))

(define (pi-two) (* 2 (other-integral half-circle -1 1 1000)))

(define (better-integral f a b n)
  (define h (/ (- b a) n))
  (define (y k) (f (+ a (* k h))))
  (define (term k)
    (cond ((even? k) (* 2 (y k)))
          (else (* 4 (y k)))))
  (* (/ h 3) (+ (f a) (f b) (sum term 1 inc (- n 1)))))

(define (pi-three) (* 2 (better-integral half-circle -1 1 1000)))

(define (time f)
  (define start (runtime))
  (f)
  (define end (runtime))
  (- end start))

(define (avg f n)
  (/ (sum f 0 inc n) n))

(define (dist a b)
  (abs (- a b)))

(define pi 3.14159265358979323846264)

(display "precision (%):\n")
(* (/ (dist (pi-one) pi) pi) 100)
(* (/ (dist (pi-two) pi) pi) 100)
(* (/ (dist (pi-three) pi) pi) 100)