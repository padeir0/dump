#lang sicp

(define days-per-year 365)
(define litters-1-to-10 0.5)
(define litters-10-to-15 1)
(define litters-15-to-20 1)
(define litters-20-to-25 1.5)

(define total-litters (+
                       (* 10 days-per-year litters-1-to-10)
                       (* 5 days-per-year litters-10-to-15)
                       (* 5 days-per-year litters-15-to-20)
                       (* 5 days-per-year litters-20-to-25)))

(display total-litters)