#lang sicp

(define score car)
(define weight cadr)

(define scores '((10  30 algoritmos)
                 (10  60 ga)
                 (10  60 ims)
                 (9   60 fundamentos)
                 (9.8 60 prog)
                 (8.0 60 linear)
                 (9   90 calc)
                 (9   30 itn)
                 (9.3 90 calc-2)
                 (8.3 60 grafos)
                 (9.5 60 python)
                 (7.6 60 prob)
                 (7   60 linear-2)
                 
                 (6   60 calc-3)
                 (6   60 edo)
                 (8   60 analise-1)
                 (8   60 edd)
                 (8   30 icc)))

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
