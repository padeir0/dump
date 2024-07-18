#lang sicp

(define (cell a) (cons a nil))

(define operator car)
(define exp-var cadr)
(define exp-exp caddr)

(define (deriv poly)
  (cond ((number? poly) 0)
        ((equal? poly 'x) 1)
        (else (simplify (let ((op (operator poly)))
                          (cond ((equal? op '+) (sum-rule poly))
                                ((equal? op '*) (product-rule poly))
                                ((equal? op '^) (exp-rule poly))
                                (else (display op)
                                      (newline)
                                      "unrecognized operation")))))))

(define (simplify poly)
  (cond ((number? poly) poly)
        ((equal? poly 'x) poly)
        (else (let ((op (operator poly)))
                (cond ((equal? op '+) (simplify-sum poly))
                      ((equal? op '*) (simplify-product poly))
                      ((equal? op '^) (simplify-exp poly))
                      (else (display op)
                            (newline)
                            "unrecognized operation"))))))

(define (has list item)
  (if (equal? list nil)
      #f
      (if (equal? (car list) item)
          #t
          (has (cdr list) item))))

(define (map-list list f)
  (if (equal? list nil)
      nil
      (cons (f (car list)) (map-list (cdr list) f))))

(define (filter-list list item)
  (if (equal? list nil)
      nil
      (if (equal? (car list) item)
          (filter-list (cdr list) item)
          (cons (car list)
                (filter-list (cdr list) item)))))

(define (extract list)
  (if (= (length list) 2)
      (cadr list)
      list))

(define (simplify-sum poly)
  (if (equal? (operator poly) '+)
      (extract (cons '+
                     (filter-list (map-list (cdr poly) simplify) 0)))
      (error "not a sum")))

(define (simplify-product poly)
  (if (equal? (operator poly) '*)
      (if (has poly 0)
          0
          (extract (cons '*
                         (filter-list (map-list (cdr poly) simplify) 1))))
      (error "not a product")))

(define (simplify-exp poly)
  (if (equal? (operator poly) '^)
      (let ((var (exp-var poly))
            (exp (exp-exp poly)))
        (cond ((= exp 1) var)
              ((= exp 0) 1)
              (else poly)))
      (error "not a exponentiation")))

(define (exp-rule poly)
  (define (chain poly)
    (let ((var (exp-var poly))
          (exp (exp-exp poly)))
      (cons '*
            (cons (deriv var)
                  (cons exp
                        (cell (cons '^
                                    (cons var
                                          (cell (- exp 1))))))))))
  (define (simple mono)
    (let ((var (exp-var poly))
          (exp (exp-exp poly)))
      (cons '*
            (cons exp
                  (cell (cons '^
                              (cons var
                                    (cell (- exp 1)))))))))
  (if (equal? (operator poly) '^)
      (let ((var (exp-var poly)))
        (if (equal? var 'x) 
            (simple poly)
            (chain poly)))
      (error "not a exponentiation")))

(define (sum-rule poly)
  (define (deriv-terms operands)
    (if (equal? operands nil)
        nil
        (cons (deriv (car operands)) (deriv-terms (cdr operands)))))
  (if (equal? (operator poly) '+)
      (cons '+
            (deriv-terms (cdr poly)))
      (error "not a sum")))

(define (length poly)
  (if (equal? poly nil)
      0
      (+ 1 (length (cdr poly)))))

(define (product-rule poly)
  (define (deriv-term operands n i)
    (if (equal? operands nil)
        nil
        (if (= n i)
            (cons (deriv (car operands)) (deriv-term (cdr operands) n (+ i 1)))
            (cons (car operands) (deriv-term (cdr operands) n (+ i 1))))))
  (define (rule operands i n)
    (if (= i n)
        nil
        (cons (cons '* (deriv-term operands i 0)) (rule operands (+ i 1) n))))
  (if (equal? (operator poly) '*)
      (let ((operands (cdr poly)))
        (cons '+ (rule operands 0 (length operands))))
      (error "not a product")))

(define cases '((^ x 3)
                (* 3 (^ x 2))
                (* 6 x)
                6
                (+ (^ x 3) (^ x 2) x 1)
                (^ (+ 1 (^ x 2)) 2)
                (* 4 (+ 1 (^ x 2)) x)))

(define (try-cases cases)
  (if (equal? cases nil)
      nil
      (let ((out (deriv (car cases))))
        (display (car cases))
        (display " -> ")
        (display out)
        (newline)
        (try-cases (cdr cases)))))

(try-cases cases)