#lang sicp

(define (succ n) (+ n 1))

(define (soma m n)
  (cond ((= n 0) m)
        (else (succ (soma m (- n 1))))))

(define (bin m)
  (cond ((not (= m 0))
         (bin-digit m)
         (bin (floor (/ m 2))))))

(define (bin-digit m)
  (cond ((= (remainder m 2) 1) (display "1"))
        (else (display "0"))))

(define (msd m)
  (cond ((< (/ m 10) 1) m)
        (else (msd (floor (/ m 10))))))

(define (pow n p)
  (cond ((= p 0) 1)
        (else (* n (pow n (- p 1))))))

(define (sum f i n)
  (cond ((= i n) (f i))
        (else (+ (f i) (sum f (+ i 1) n)))))

(define (id x) x)

(define (term k)
  (* (/ 1 (pow 16 k))
     (+ (/ 4 (+ (* 8 k) 1))
        (/ -2 (+ (* 8 k) 4))
        (/ -1 (+ (* 8 k) 5))
        (/ -1 (+ (* 8 k) 6)))))