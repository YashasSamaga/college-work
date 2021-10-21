#lang racket

(require eopl)
(require rackunit)
(require racket/match)
(require rackunit/text-ui)
(require "main.rkt")



(define test-f1
  (test-case "f1"
    (check-equal? (parse '(recursive ([f1 (x) (< 5 x)])(ifte (f1 2) 0 10)))
                  (recursive (list 
                                (make-fbind 'f1
                                            '(x)
                                            (app (id-ref '<) (list (num 5) (id-ref 'x)))))
                              (ifte (app (id-ref 'f1) (list (num 2)))
                                    (num 0) 
                                    (num 10))))))

(define test-no-params
  (test-case "no params to recur func"
    (check-equal? (parse '(recursive ([v () 3]) v))
                  (recursive (list (make-fbind 'v '() (num 3))) (id-ref 'v)))))


(define test-multi-binds
  (test-case "multiple binds"
    (check-equal? (parse '(recursive ([f (x) (+ x x)] [g (y) (- (f y) 1)]) (g 1)))
                  (recursive (list (make-fbind 'f '(x) (app (id-ref '+) (list (id-ref 'x) (id-ref 'x))))
                                   (make-fbind 'g '(y) (app (id-ref '-) 
                                                            (list (app (id-ref 'f) (list (id-ref 'y)))
                                                                  (num 1)))))
                             (app (id-ref 'g) (list (num 1)))))))


(define test-recursive-parsing
  (test-suite "Recursive Parsing"
    test-f1
    test-no-params
    test-multi-binds))

(define e1
  (extended-env '(x y z) '(1 2 3) (empty-env)))

(define e2
  (extended-env '(w x) '(5 6) e1))

(define even-body
  (ifte
    (app (id-ref '0?) (list (id-ref 'n)))
    (bool #t)
    (app
      (id-ref 'odd?)
      (list (app
              (id-ref '-)
              (list (id-ref 'n) (num 1)))))))

(define odd-body
  (ifte (app (id-ref '0?) (list (id-ref 'n)))
    (bool #f)
    (app (id-ref 'even?)
      (list (app (id-ref '-) (list (id-ref 'n) (num 1)))))))

(define e3
  (extended-rec-env
    '(even? odd?)
    '((n) (n))
    (list even-body odd-body)
    e2))



(check-equal?
 (closure '(n) even-body e3)
 (lookup-env e3 'even?) "lookup-env-even? test")


(define test-env
  (test-case "outer env"
    (check-equal? 6 (lookup-env e3 'x))))

(define test-rec-env
  (test-case "Outer Rec Env"
    (check-equal?
      (closure '(n) even-body e3)
      (lookup-env e3 'even?))))


(define lookup-test
  (test-suite "Lookup"
    test-env
    test-rec-env))
(define test-even-odd
 (test-case "Even Odd"
  (check-equal?
   (eval-ast
    (recursive
     (list
      (make-fbind 'even?
                  '(n)
                  (ifte (app (id-ref '0?) (list (id-ref 'n)))
                        (bool #t)
                        (app (id-ref 'odd?)
                             (list (app (id-ref '-) (list (id-ref 'n) (num 1)))))))
      
      (make-fbind 'odd?
                  '(n)
                  (ifte (app (id-ref '0?) (list (id-ref 'n)))
                        (bool #f)
                        (app (id-ref 'even?)
                             (list (app (id-ref '-) (list (id-ref 'n) (num 1))))))))
     
     (app (id-ref 'even?) (list (num 3))))
     *init-env*)
   #f)))


(define test-factorial
 (test-case "factorial"
  (check-equal?
   (eval-ast (parse '(recursive ([f (n) (ifte (0? n) 1 (* n (f (- n 1))))])
         (f 3))) *init-env*)
   6)))


(define test-recursive-evaluation
  (test-suite "test-eval"
   test-even-odd
   test-factorial))


(define test-recursive
  (test-suite "Recursive Tests"
              test-recursive-parsing
              lookup-test
              test-recursive-evaluation))


(define run-all-tests 
  (lambda ()
    (run-tests test-recursive)))


(module+ test
  (run-all-tests))
