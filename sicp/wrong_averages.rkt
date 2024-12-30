#lang sicp

(define (sum list)
  (if (eq? list nil)
      0
      (+ (car list) (sum (cdr list)))))

(define (length list)
  (if (eq? list nil)
      0
      (+ 1 (length (cdr list)))))

(define (avg1 list)
  (/ (sum list) (length list)))

(define (avg2 list)
  (define (iter list cum)
    (if (eq? list nil)
      cum
      (iter (cdr list) (/ (+ cum (car list)) 2))))
  (if (eq? list nil)
      nil
      (iter (cdr list) (car list))))

(define a '(1 2 3 4 5 6 7 8 9))
(define b '(2 2 3 3 5 5 7 7 9 9))
(define c '(1 1 1 1 1 1 1))
(define d '(1 2 3))