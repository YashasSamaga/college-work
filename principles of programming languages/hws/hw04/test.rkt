#lang racket
(require eopl)
(require rackunit)
(require racket/match)
(require rackunit/text-ui)
(require "main.rkt")

;;; Tests for parsing
(define ts-parsing
  (test-suite "parsing"
              (test-case "num" (check-equal? (parse 10) (num 10)))
              (test-case "symbol" (check-equal? (parse 'a) (id-ref 'a)))
              (test-case "add" (check-equal? (parse '(+ 10 20)) (binop 'add (num 10) (num 20))))
              (test-case "sub" (check-equal? (parse '(- 10 20)) (binop 'sub (num 10) (num 20))))
              (test-case "mul" (check-equal? (parse '(* 10 20)) (binop 'mul (num 10) (num 20))))
              (test-case "div" (check-equal? (parse '(/ 10 20)) (binop 'div (num 10) (num 20))))
              (test-case "neg true" (check-equal? (parse '(! #t)) (unaryop 'neg (bool #t))))
              (test-case "neg false" (check-equal? (parse '(! #f)) (unaryop 'neg (bool #f))))
              (test-case "bool-t" (check-equal? (parse #t) (bool #t)))
              (test-case "bool-f" (check-equal? (parse #f) (bool #f)))
              (test-case "if" (check-equal? (parse '(if #t 10 20)) (ifte (bool #t) (num 10) (num 20))))
              (test-case "failure"
                (check-exn exn:parse-error?
                           (lambda () (parse '(** 10 20)))))
              (test-case "recur" (check-equal?
                                  (parse '(+ (- 10 20) (* 20 30)))
                                  (binop 'add
                                             (binop 'sub (num 10) (num 20))
                                             (binop 'mul (num 20) (num 30)))))))
(define test-parse-assume
  (test-suite "Parsing assume construct"

    (test-case "valid : single binding"
      (check-equal? 
       (assume
        (list (make-bind 'x (num 30)))
        (binop 'add (num 100) (id-ref 'x)))
       (parse '(assume ([x 30])(+ 100 x)))))

    (test-case "valid : operation in binding"
      (check-equal? 
       (assume
        (list (make-bind 'x (binop 'add (num 2) (num 4))))
        (binop 'add (num 100) (id-ref 'x)))
       (parse '(assume ([x (+ 2 4)])(+ 100 x)))))

    (test-case "valid : multiple bindings"
      (check-equal?
       (assume
        (list (make-bind 'a (num 40)) (make-bind 'x (num 30)))
        (binop 'add (id-ref 'a) (id-ref 'x)))
       (parse '(assume ([a 40][x 30])(+ a x)))))

    (test-case "fail: no body"
      (check-exn exn:parse-error?
        (lambda()
          (parse '(assume ([a 40][x 30]))))))))
(define ts-evaluation
  (test-suite
    "evaluation"
    (test-case "num" 
               (check-equal? 10 
                             (eval-ast (num 10) (empty-env))))
    (test-case "id-ref" 
               (check-equal? 3
                             (eval-ast (id-ref 'x) 
                             (extended-env '(x v) (list 3 5) (empty-env)))))
    (test-case "add" 
               (check-equal? 30 
                             (eval-ast (binop 'add (num 10) (num 20)) (empty-env))))
    (test-case "sub" 
               (check-equal? -10 
                             (eval-ast (binop 'sub (num 10) (num 20)) (empty-env))))
    (test-case "mul" 
               (check-equal? 200 
                             (eval-ast (binop 'mul (num 10) (num 20)) (empty-env))))
    (test-case "lt" 
               (check-equal? #t 
                             (eval-ast (binop 'lt? (num 10) (num 20)) (empty-env))))
    (test-case "eq" 
               (check-equal? #t 
                             (eval-ast (binop 'eq? (num 10) (num 10)) (empty-env))))
    (test-case "div-success" 
               (check-equal? 2
                             (eval-ast (binop 'div (num 20) (num 10)) (empty-env))))
    (test-case "div-failure"
               (check-exn exn:exec-div-by-zero?
                          (lambda () 
                            (eval-ast (binop 'div (num 20) (num 0)) (empty-env)) 2)))
    (test-case "bool-t" 
               (check-equal? #t
                             (eval-ast (bool #t) (empty-env))))
    (test-case "bool-f" 
               (check-equal? #f 
                             (eval-ast (bool #f) (empty-env))))
    (test-case "if-true" 
               (check-equal? 10 
                             (eval-ast 
                               (ifte (bool #t) (num 10) (num 20)) (empty-env))))
    (test-case "if-false" 
               (check-equal? 20
                             (eval-ast 
                               (ifte (bool #f) (num 10) (num 20)) (empty-env))))
    (test-case "if-type-mismatch"  
               (check-exn exn:exec-type-mismatch?
                          (lambda () 
                            (eval-ast 
                              (ifte (num 42) (num 10) (num 20)) (empty-env)))))
    (test-case "assume : single binding : empty-env at top level : no reference"
               (check-equal? 50
                             (eval-ast 
                               (assume (list (make-bind 'x (num 100)))
                                       (binop 'add (num 2) (num 48)))
                               (empty-env))))
    (test-case "assume : single binding : empty-env at top level : single reference"
               (check-equal? 150
                             (eval-ast 
                               (assume (list (make-bind 'x (num 100)))
                                       (binop 'add (num 50) (id-ref 'x)))
                               (empty-env))))))
(define test-lookup-env
  (test-suite "Lookup Env"
    (test-case "Binding is present : Lookup returns the ast"
      (let 
        ((mock-env (extended-env (list 'x) (list 10) (empty-env))))
        (check-equal? 10
                      (lookup-env mock-env 'x))))

    (test-case "Binding not found : Lookup throws error"
      (let 
        ((mock-env (extended-env (list 'x) (list 10) (empty-env))))
        (check-exn exn:lookup-error?
                   (lambda ()
                     (lookup-env mock-env 'y)))))
    (test-case "Binding found in outer env"
      (let*
        ((other-env (extended-env (list 'y) (list 10) (empty-env)))
         (mock-env (extended-env (list 'x) (list 3) other-env)))
        (check-equal? 10
                     (lookup-env mock-env 'y))))))
(define run-all-tests 
  (lambda ()
    (run-tests ts-parsing)
    (run-tests test-parse-assume)
    (run-tests test-lookup-env)
    (run-tests ts-evaluation)
    (run-tests ts-numop-incorrect-param-rand1)
    (run-tests ts-numop-incorrect-param-rand2)))
(module+ test
  (run-all-tests))
