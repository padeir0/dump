#lang sicp

(define days-per-year 365)
(define liters-1-to-10 0.5)
(define liters-10-to-15 1)
(define liters-15-to-20 1)
(define liters-20-to-25 1.5)

(define total-liters (+
                       (* 10 days-per-year liters-1-to-10)
                       (* 5 days-per-year liters-10-to-15)
                       (* 5 days-per-year liters-15-to-20)
                       (* 5 days-per-year liters-20-to-25)))

(display total-liters)
