#lang sicp

(define (mult a b)
  (if (= b 0)
      0
      (+ a (mult a (- b 1)))))

(define (mult-iter a b)
  (define (iter a b out)
    (cond ((= b 0) out)
          (else (iter a (- b 1) (+ a out)))))
  (iter a b 0))

(define (even? a)
  (= (remainder a 2) 0))

(define (double a)
  (+ a a))

(define (half a)
  (if (even? a)
      (/ a 2)
      (nil)))

(define (fast-mult a b)
  (cond ((= b 0) 0)
        ((even? b) (double (fast-mult a (half b))))
        (else (+ a (fast-mult a (- b 1))))))

(define (fast-mult-iter a b)
  (define (iter a b out)
    (cond ((= b 0) out)
          ((even? b) (iter (double a) (half b) out))
          (else (iter a (- b 1) (+ a out)))))
  (iter a b 0))

(define (square a)
  (fast-mult-iter a a))

(define (custom-exp-iter p n)
  (define (iter p n out)
    (cond ((= n 0) out)
          ((even? n) (iter (square p) (half n) out))
          (else (iter p (- n 1) (fast-mult-iter out p)))))
  (iter p n 1))

(define (fast-exp-iter p n)
  (define (iter p n out)
    (cond ((= n 0) out)
          ((even? n) (iter (* p p) (/ n 2) out))
          (else (iter p (- n 1) (* out p)))))
  (iter p n 1))

(define (time f)
  (define start (runtime))
  (f)
  (define end (runtime))
  (- end start))