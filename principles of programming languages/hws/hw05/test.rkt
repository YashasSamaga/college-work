#lang racket

(require rackunit)
(require "main.rkt")

(define (a) (list 'a))

(let ([t (a)])
  (check-true (bisimilar? t t)))

(let ([t1 (colist 'a)]
      [t2 (list 'a)])
  (check-true (bisimilar? t1 t2)))

(letrec ([t (colist 'g t)])
  (check-true (bisimilar? t t)))

(let* ([t1 (a)]
       [t2 (a)])
  (check-true (bisimilar? (list 'f t1 t2) (list 'f t1 t1))))

(letrec ([t1 (colist 'g t2)]
         [t2 (colist 'g t1)])
  (check-true (bisimilar? t1 t2)))


(letrec ([t1 (colist 'g t2)]
         [t2 (colist 'g t2)])
  (check-true (bisimilar? t1 t2)))

(letrec ([t1 (list 'f '(a) '(b))]
         [t2 (colist 'g t1 t2)])
  (check-false (bisimilar? t1 t2)))

(letrec ([t1 (list 'g (list 'g '(a)))]
         [t2 (colist 'g t2)])
  (check-false (bisimilar? t1 t2)))

(check-exn 
  exn:fail?
  (lambda () (bisimilar? (list 'r))))

(check-exn 
  exn:type-error?
  (lambda () (bisimilar? '() '())))

(check-exn 
  exn:type-error?
  (lambda () (bisimilar? '1 (list 'x))))
