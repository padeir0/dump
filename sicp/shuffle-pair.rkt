#lang sicp

(define (get-item list index)
  (define (get-iter list index n)
    (if (eq? list nil)
        nil
        (if (= index n)
            (car list)
            (get-iter (cdr list) index (+ n 1)))))
  (get-iter list index 0))

(define (remove-item list index)
  (define (rem-iter list index n)
    (if (eq? list nil)
        nil
        (if (= index n)
            (rem-iter (cdr list) index (+ n 1))
            (cons (car list) (rem-iter (cdr list) index (+ n 1))))))
  (rem-iter list index 0))

(define (pop-item list index)
  (define item (get-item list index))
  (define remains (remove-item list index))
  (cons item remains))

(define (first-ret ret)
  (car ret))
(define (second-ret ret)
  (cdr ret))

(define people '(iure ribas jc tommy paulo vrido))

(define (shuffle list)
  (if (= (length list) 0)
      nil
      (let
          ((ret (pop-item list (random (length list)))))
        (cons (first-ret ret) (shuffle (second-ret ret))))))

(define (pair a b)
  (cons a (cons b nil)))
(define (cell a)
  (cons a nil))

(define (pair-up list)
  (if (eq? list nil)
      nil
      (if (eq? (cdr list) nil)
          (cell list)
          (cons (pair (car list) (cadr list)) (pair-up (cddr list))))))

(pair-up (shuffle people))