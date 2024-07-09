#lang sicp

(define (exp p n)
  (cond ((= n 0) 1)
        (else (* p (exp p (- n 1))))))

(define (exp-iter p n)
  (define (iter p n out)
    (cond ((= n 0) out)
          (else (iter p (- n 1) (* out p)))))
  (iter p n 1))

(define (even? x)
  (= (remainder x 2) 0))

(define (square x)
  (* x x))

(define (fast-exp p n)
  (cond ((= n 0) 1)
        ((even? n) (square (fast-exp p (/ n 2))))
        (else (* p (fast-exp p (- n 1))))))

(define (time f)
  (define start (runtime))
  (f)
  (define end (runtime))
  (- end start))

(define (display-line a)
  (display a)
  (display "\n"))

(define (fast-exp-iter p n)
  (define (iter p n out)
    (cond ((= n 0) out)
          ((even? n) (iter (square p) (/ n 2) out))
          (else (iter p (- n 1) (* out p)))))
  (iter p n 1))