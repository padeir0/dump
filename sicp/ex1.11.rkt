#lang sicp

(define (f n)
  (cond ((< n 3) n)
        (else (+ (f (- n 1))
                 (* 2 (f (- n 2)))
                 (* 3 (f (- n 3)))))))

(define (f-iter n)
  (define (iter n a b c)
    (cond ((= n 0) a)
          (else (iter (- n 1)
                        b
                        c
                        (+ c (* 2 b) (* 3 a))))))
  (iter n 0 1 2))

(define (ok n)
  (= (f-iter n) (f n)))

(define (test n)
  (cond ((= n 0) #t)
        ((ok n) (test (- n 1)))
        (else #f)))