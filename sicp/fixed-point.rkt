#lang sicp

(define tolerance 0.00001)

(define (fixed-point f first-guess)
  (define (close-enough? v1 v2)
    (< (abs (- v1 v2)) tolerance))
  (define (try guess)
    (let ((next (f guess)))
      (if (close-enough? guess next)
          next
          (try next))))
  (try first-guess))

(define (average a b)
  (/ (+ a b) 2))

(define (average-damp f)
  (lambda (x) (average x (f x))))

(define (sqrt x)
  (fixed-point (average-damp (lambda (y) (/ x y))) 1))

(define phi (/ (+ 1 (sqrt 5.0)) 2))

(define dx 0.00001)

(define (derivative g)
  (lambda (x)
    (/ (- (g (+ x dx)) (g x))
       dx)))

(define (integral g a b)
  (define (iter a out)
    (if (> a b)
        out
        (iter (+ a dx) (+ (* (g a) dx) out))))
  (iter a 0))

(define parabola (lambda (x) (* x x)))
(define hiperbole (lambda (x) (/ 1 x)))

(define (newton-transform g)
  (lambda (x)
    (- x (/ (g x) ((derivative g) x)))))

(define (newtons-method g guess)
  (fixed-point (newton-transform g) guess))

(define (sqrt-b x)
  (newtons-method (lambda (y) (- (* y y) x)) 1.0))

(define (cuberoot x)
  (newtons-method (lambda (y) (- (* y y y) x)) 1.0))

(define (pow p n)
  (define (iter n out)
    (if (= n 0)
        out
        (iter (- n 1) (* out p))))
  (iter n 1))

(define (nroot x n)
  (newtons-method (lambda (y) (- (pow y n) x)) 1.0))

(define (distance a b)
  (abs (- a b)))

(define (close-enough? a b dx)
  (< (distance a b) dx))

(define (range f start end)
  (define (iter i)
    (if (f i)
        (if (= i end)
            #t
            (iter (+ i 1)))
        #f))
  (iter start))

(define (test n)
  (define dx 0.0001)
  (define (identity x)
    (nroot (pow x n) n))
  (define (assert x)
    (close-enough? (identity x) x dx))
  (range assert 0 32))

(define (square x) (* x x))
(define (cube x) (* x x x))
(define (cubic a b c)
  (lambda (x) (+ (cube x) (* a (square x)) (* b x) c)))

(define (double f)
  (lambda (x) (f (f x))))

(define (compose f g)
  (lambda (x) (f (g x))))

(define (repeat f n)
  (define (iter i out)
    (if (= i n)
        out
        (iter (+ i 1) (f out))))
  (lambda (x) (iter 0 x)))

(define (rep-comp f n)
  (if (= n 1)
      f
      (compose f (rep-comp f (- n 1)))))

(define (smooth f)
  (lambda (x) (/ (+ (f (- x dx)) (f x) (f (+ x dx))) 3)))

(define (n-smooth f n)
  ((repeat smooth n) f))