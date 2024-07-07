#lang sicp

(define (pascal row col)
  (cond ((= col 1) 1)
        ((= col row) 1)
        (else (+ (pascal (- row 1) (- col 1))
                 (pascal (- row 1) col)))))

(define (iter f i n)
  (cond ((< i n)
         (f i)
         (iter f (+ i 1) n))))

(define (print-pascal depth)
  (define (print-col-iter depth col)
    (cond ((<= col depth)
           (display " ")
           (display (pascal depth col))
           (print-col-iter depth (+ col 1)))))
  (define (print-iter depth)
    (print-col-iter depth 1)
    (display "\n"))
  (iter print-iter 0 depth))