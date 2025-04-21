#lang sicp

(define (id x) x)
(define (sq x) (* x x))
(define (pow x y)
  (cond ((= y 0) 1)
        (else (* x (pow x (- y 1))))))
(define (term k)
  (* (/ 1 (pow 16 k))
     (+ (/ 4 (+ (* 8 k) 1))
        (/ -2 (+ (* 8 k) 4))
        (/ -1 (+ (* 8 k) 5))
        (/ -1 (+ (* 8 k) 6)))))
(define (sum f i n)
  (cond ((= i n) (f i))
        (else (+ (f i) (sum f (+ i 1) n)))))

(define pi (sum term 0 90))