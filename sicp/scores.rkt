#lang sicp

(define score car)
(define weight cadr)

(define scores '((10  30 algoritmos)
                 (10  60 ga)
                 (10  60 ims)
                 (9   60 fundamentos)
                 (9.8 60 prog)
                 (8.0 60 linear)
                 (9   90 calculo)
                 (9   30 itn)
                 (9.3 90 calculo-2)
                 (8.3 60 grafos)
                 (9.5 60 python)
                 (7.6 60 prob)
                 (6   60 linear-2)
                 ))

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