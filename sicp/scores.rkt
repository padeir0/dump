#lang sicp

(define score car)
(define weight cadr)

(define test '((10 30) (10 60) (10 90)))

(define scores '((10  30)
                 (10  60)
                 (10  60)
                 (9   60)
                 (9.8 60)
                 (8.0 60)
                 (9   90)
                 (9   30)
                 (9.3 90)
                 (8.3 60)))

(define (apply-weight item)
  (* (score item) (weight item)))
  
(define (weighted-sum list)
  (if (eq? list nil)
      0
      (+ (apply-weight (car list))
         (weighted-sum (cdr list)))))
(define (sum-weights list)
  (if (eq? list nil)
      0
      (+ (weight (car list)) (sum-weights (cdr list)))))

(define (weighted-average list)
  (/ (weighted-sum list) (sum-weights list)))

(weighted-average scores)