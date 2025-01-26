#lang sicp

(define (inv a)
  (/ 1 a))

(define (abs x)
  (if (< x 0)
      (- x)
      x))

(define (close-enough? a b)
  (< (abs (- a b)) 0.0001))

(define (reverse a)
  (define (f input output)
    (if (eq? input nil)
        output
        (f (cdr input) (cons (car input) output))))
  (f a nil))

(define (vec-eq? a b)
  (if (eq? b nil)
      (eq? a nil)
      (and (close-enough? (car a) (car b))
           (vec-eq? (cdr a) (cdr b)))))

(define (basis-eq? A B)
  (if (eq? B nil)
      (eq? A nil)
      (and (vec-eq? (car A) (car B))
           (basis-eq? (cdr A) (cdr B)))))

(define (sum x y)
  (if (eq? y nil)
      x
      (cons (+ (car x) (car y))
            (sum (cdr x) (cdr y)))))

(define (sumate . args)
  (if (eq? args nil)
      nil
      (sum (car args)
           (apply sumate (cdr args)))))

(define (scale a x)
  (if (eq? x nil)
      nil
      (cons (* a (car x))
            (scale a (cdr x)))))

(define (neg x) (scale -1 x))

(define (sum-coord x)
  (if (eq? x nil)
      0
      (+ (car x) (sum-coord (cdr x)))))

(define (mult-coord x y)
  (if (eq? x nil)
      nil
      (cons (* (car x) (car y))
            (mult-coord (cdr x) (cdr y)))))

(define (inner-product x y)
  (sum-coord (mult-coord x y)))

(define (norm x)
  (if (eq? x nil)
      0
      (sqrt (inner-product x x))))

(define (normalize x)
  (scale (/ 1 (norm x)) x))

(define (orthogonal? x y)
  (close-enough? (inner-product x y) 0))

(define (ortho? x basis)
  (if (eq? basis nil)
      #t
      (and (orthogonal? x (car basis))
           (ortho? x (cdr basis)))))

(define (ortho-all? basis)
  (if (eq? basis nil)
      #t
      (and (ortho? (car basis) (cdr basis))
           (ortho-all? (cdr basis)))))

(define (gsch-proj x y)
  (scale (inner-product x y) y))

(define (atom x)
  (cons x nil))

(define (proj-each x basis)
  (if (eq? basis nil)
      nil
      (cons (gsch-proj x (car basis))
            (proj-each x (cdr basis)))))

(define (gsch-step x basis)
  (normalize (sum x (neg (apply sumate (proj-each x basis))))))

(define (gram-schmidt basis)
  (define (gsch input output)
    (if (eq? input nil)
        output
        (gsch (cdr input)
              (cons (gsch-step (car input) output)
                    output))))
  (gsch (cdr basis) (atom (normalize (car basis)))))

(define v_1 '(0 1 2))
(define v_2 '(1 0 2))
(define v_3 '(1 2 0))

(define o_1
  (scale (/ 1 (sqrt 5))
         '(0 1 2)))
(define o_2
  (scale (/ 1 (* 3 (sqrt 5)))
         '(5 -4 2)))
(define o_3
  (normalize
   (sumate v_3
           (neg (scale (inner-product v_3 o_1) o_1))
           (neg (scale (inner-product v_3 o_2) o_2)))))

(define init (list v_1 v_2 v_3))
(define hand-ortho (list o_1 o_2 o_3))
(define canonical (list '(1 0 0) '(0 1 0) '(0 0 1)))

(define test
  (list (normalize v_1)
        (gsch-step v_2 (list (normalize v_1)))
        (gsch-step v_3 (list (normalize v_1)
                             (gsch-step v_2 (list (normalize v_1)))))))