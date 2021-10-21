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
              (test-case "add" (check-equal? (parse '(+ 10 20)) (binop 'add (num 10) (num 20))))
              (test-case "sub" (check-equal? (parse '(- 10 20)) (binop 'sub (num 10) (num 20))))
              (test-case "mul" (check-equal? (parse '(* 10 20)) (binop 'mul (num 10) (num 20))))
              (test-case "div" (check-equal? (parse '(/ 10 20)) (binop 'div (num 10) (num 20))))
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
                                             (binop 'mul (num 20) (num 30)))))
              ))
(define ts-evaluation
  (test-suite
    "evaluation"
    (test-case "num" (check-equal? (eval-ast (num 10)) 10))
    (test-case "add" (check-equal? (eval-ast (binop 'add (num 10) (num 20))) 30))
    (test-case "sub" (check-equal? (eval-ast (binop 'sub (num 10) (num 20))) -10))
    (test-case "mul" (check-equal? (eval-ast (binop 'mul (num 10) (num 20))) 200))
    (test-case "lt" (check-equal? (eval-ast (binop 'lt? (num 10) (num 20))) #t))
    (test-case "eq" (check-equal? (eval-ast (binop 'eq? (num 10) (num 10))) #t))
    (test-case "div-success" (check-equal? (eval-ast (binop 'div (num 20) (num 10))) 2))
    ;; raise an exception, so use the correct `raise' function!
    (test-case "div-failure"
               (check-exn exn:exec-div-by-zero?
                          (lambda () (eval-ast (binop 'div (num 20) (num 0))) 2)))
    (test-case "bool-t" (check-equal? (eval-ast (bool #t)) #t))
    (test-case "bool-f" (check-equal? (eval-ast (bool #f)) #f))
    (test-case "if-true" (check-equal? (eval-ast (ifte (bool #t) (num 10) (num 20))) 10))
    (test-case "if-false" (check-equal? (eval-ast (ifte (bool #f) (num 10) (num 20))) 20))
    (test-case "if-type-mismatch"  (check-exn exn:exec-type-mismatch?
               (lambda () (eval-ast (ifte (num 42) (num 10) (num 20))))))))
(define run-all-tests 
  (lambda ()
    (run-tests ts-parsing)
    (run-tests ts-evaluation)
    (run-tests ts-numop-incorrect-param-rand1)
    (run-tests ts-numop-incorrect-param-rand2)))
(module+ test
  (run-all-tests))
