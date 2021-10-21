#lang racket

(require eopl)
(require rackunit)
(require racket/match)
(require rackunit/text-ui)
(require "main-tang.rkt")


(define iden-fn '(function (x) x))
(define apply-iden-fn '((function (x) x) 10))

(define const-fn '(function () 1))
(define apply-const-fn '((function () 1)))

(define sum-fn '(function (p q) (+ p q)))
(define apply-sum-fn '((function (p q) (+ p q)) 10 30))

(define fn-with-assume '(assume ([sub-2 (function (x) (- x 2))]) (sub-2 10)))

(define fn-override-binding '(assume ([a 10])((function (a b) (+ a b)) 30 40)))



(define test-function-parsing
  (test-suite "Function Parsing"
              (test-case "Identity Function"
                (check-equal? (parse iden-fn)
                              (function '(x) (id-ref 'x))))
              
              (test-case "No Params"
                (check-equal? (parse const-fn)
                              (function '() (num 1))))
              
              (test-case "Two Params"
                (check-equal? (parse sum-fn)
                              (function '(p q)
                                        (app (id-ref '+)
                                             (list (id-ref 'p) (id-ref 'q))))))
              (test-case "Parse Error - function"
               (check-exn exn:fail?
                          (lambda () 
                            (parse '(function (a))))))

              (test-case "Parse Error - assume"
               (check-exn exn:fail?
                          (lambda () 
                            (parse '(assume)))))))
(define test-operator-functions
  (test-suite "Operator Function"
              (test-case "Add"
                          (check-equal? (eval-ast (app (id-ref '+) (list (num 10) (num 10))) *init-env*)
                                        20))                        
              (test-case "Sub"
                          (check-equal? (eval-ast (app (id-ref '-) (list (num 40) (num 10))) *init-env*)
                                        30))
              (test-case "Product"
                          (check-equal? (eval-ast (app (id-ref '*) (list (num 5) (num 5))) *init-env*)
                                        25))
              (test-case "Div"
                          (check-equal? (eval-ast (app (id-ref '/) (list (num 100) (num 5))) *init-env*)
                                        20))
              (test-case "lt-f"
                          (check-equal? (eval-ast (app (id-ref '<) (list (num 200) (num 10))) *init-env*)
                                        #f))
              (test-case "lt-t"
                          (check-equal? (eval-ast (app (id-ref '<) (list (num 1) (num 5))) *init-env*)
                                        #t))
              (test-case "neg"
                          (check-equal? (eval-ast (app (id-ref '!) (list (bool #t))) *init-env*)
                                        #f))
              (test-case "neg-t"
                          (check-equal? (eval-ast (app (id-ref '!) (list (bool #f))) *init-env*)
                                        #t))
              (test-case "<=p"
                          (check-equal? (eval-ast (app (id-ref '<=) (list (num 1) (num 1))) *init-env*)
                                        #t))
              (test-case "0?p"
                          (check-equal? (eval-ast (app (id-ref '0?) (list (num 0))) *init-env*)
                                        #t))
              (test-case "eq?p"
                          (check-equal? (eval-ast (app (id-ref 'eq?) (list (num 1) (num 1))) *init-env*)
                                        #t))
              (test-case "eq?p - #f"
                          (check-equal? (eval-ast (app (id-ref 'eq?) (list (num 4) (num 1))) *init-env*)
                                        #f))))
(define test-function-evaluation
  (test-suite "Function Evaluation"
              (test-case "Identity Function"
                (check-equal? (eval-ast (parse apply-iden-fn) *init-env*)
                              10))
              (test-case "No Params"
                (check-equal? (eval-ast (parse apply-const-fn) *init-env*)
                              1))
              (test-case "Two Params"
                (check-equal? (eval-ast (parse apply-sum-fn) *init-env*)
                              40))
              (test-case "Function Bound to identifier"
                (check-equal? (eval-ast (parse fn-with-assume) *init-env*)
                              8))
              (test-case "Function Parameter overrides the assume binding"
                (check-equal? (eval-ast (parse fn-override-binding) *init-env*)
                              70))
              (test-case "Eval Error"
               (check-exn exn:fail?
                          (lambda () 
                            (eval-ast (app (id-ref '/) (list (num 20) (num 0))) *init-env*))))
              (test-case "Eval Error - prim op - incorrect value"
               (check-exn exn:fail?
                          (lambda () 
                            (eval-ast (app +p (list (bool #t) (num 0))) *init-env*))))
              (test-case "Eval Error - prim op - incorrect # of params"
               (check-exn exn:fail?
                          (lambda () 
                            (eval-ast (app +p (list (num 0))) *init-env*))))))


(define test-function
  (test-suite "Function Tests"
              test-function-parsing
              test-function-evaluation
              test-operator-functions))


(define run-all-tests 
  (lambda ()
    (run-tests test-function)))


(module+ test
  (run-all-tests))
