#lang sicp

(define (first-denomination kind)
  (cond ((= kind 1) 1)
        ((= kind 2) 5)
        ((= kind 3) 10)
        ((= kind 4) 25)
        ((= kind 5) 50)))

(define (cc amount kinds-of-coins)
  (cond ((= amount 0) 1)
        ((or (< amount 0) (= kinds-of-coins 0)) 0)
        (else (+ (cc amount (- kinds-of-coins 1))
                 (cc (- amount (first-denomination kinds-of-coins)) kinds-of-coins)))))

(define (count-change amount)
  (cc amount 5))