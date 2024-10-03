#lang sicp

(define data '((out 13 4 9)
               (nov 13 5 8)
               (dez 13 4 9)
               (jan 14 5 9)))

(define (id x) x)

(define (to-all list)
  (if (eq? list nil)
      nil
      (begin
        (to-tuple (car list))
        (to-all (cdr list)))))

(define (popular days) (* days 3.5))
(define (lunch days) (* days 18))
(define (bus days) (* days 5))
(define (uber days) (* days 16))

(define (workday-expenses tup)
  (let ((days (cadr tup))
        (fridays (caddr tup)))
    (list (lunch days)
          (bus (- days fridays))
          (uber fridays))))

(define (uffday-expenses days)
  (list (* 2 (bus days))
        (popular days)))

(define (sum list)
  (if (eq? list nil)
      0
      (+ (car list) (sum (cdr list)))))

(define (put-item item)
  (display item)
  (display " "))

(define (to-tuple tup)
  (display (car tup))
  (display " ")
  (let ((wk-exp (workday-expenses tup))
        (uff-exp (uffday-expenses (caddr tup))))
    (put-item wk-exp)
    (put-item uff-exp)
    (put-item (+ (sum wk-exp) (sum uff-exp))))
  (newline))

(to-all data)