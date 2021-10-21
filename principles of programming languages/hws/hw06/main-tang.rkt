#lang racket

(require eopl)

(define-datatype ast ast?
  [num (datum number?)]
  [bool (datum boolean?)]
  [ifte (test ast?) (then ast?) (else-ast ast?)]
  [function
   (formals (list-of id?))
   (body ast?)]
  [app (rator ast?) (rands (list-of ast?))]
  [id-ref (sym id?)]
  [assume (binds  (list-of bind?)) (body ast?)])

(define-datatype bind bind?
  [make-bind (b-id id?) (b-ast ast?)])

;;; bind-id : bind? -> id?
(define bind-id
  (lambda (b)
    (cases bind b
      [make-bind (b-id b-ast) b-id])))

;;; bind-ast : bind? -> ast?
(define bind-ast
  (lambda (b)
    (cases bind b
      [make-bind (b-id b-ast) b-ast])))
(define env? procedure?)


;;; lookup-env: [env?  symbol?] -> any/c
;;; lookup-env: throws "unbound identifier" error
(define lookup-env
  (lambda (e x)
    (e x)))

;;; empty-env : () -> env?
(define empty-env
  (lambda ()
    (lambda (x)
      (error 'empty-env "unbound identifier ~a" x))))

;;; extended-env :
;;;    [(list-of symbol?) (list-of any/c) env?] -> env?
(define extended-env
  (lambda (syms vals outer-env)
    (lambda (x)
      (let ([j (list-index syms x)])
        (cond
          [(= j -1) (lookup-env outer-env x)]
          [#t (list-ref vals j)])))))

;;; Returns the loction of the element in a list, -1 if the
;;; element is absent.

;;; list-index : [(listof any/c)  any/c] -> 
(define list-index
  (lambda (ls a)
    (letrec ([loop
               (lambda (ls ans)
                 (cond
                   [(null? ls) -1]
                   [(eq? (first ls) a) ans]
                   [#t (loop (rest ls) (+ 1 ans))]))])
      (loop ls 0))))
(define *keywords*
  '(ifte function assume))

(define id?
  (lambda (x)
    (and
     (symbol? x)
     (not (memq x *keywords*)))))

;;; parse :: any/c -> ast?  Raises exception exn?
;;; Fill in the function parse here
(define (parse exp)
  (cond
    [(number? exp) (num exp)]
    [(boolean? exp) (bool exp)]
    [(id? exp) (id-ref exp)]
    [(and (list? exp) (= (length exp) 3) (equal? (first exp) 'assume))
      (let* ([bindingsraw (second exp)] [body (third exp)]
             [bindings (map (lambda (entry) (make-bind (first entry) (parse (second entry)))) bindingsraw)])
        (assume bindings (parse body))
      )
    ]
    [(and (list? exp) (= (length exp) 3) (equal? (first exp) 'function))
      (let ([args (second exp)] [body (third exp)])
        (if (andmap id? args)
          (function args (parse body))
          (raise "formal parameters must be identifiers")
        )
      )
    ]
    [(and (list? exp) (= (length exp) 4) (equal? 'if (first exp)))
      (let* ([testexpr (second exp)] [thenexpr (third exp)] [elseexpr (fourth exp)])
        (ifte (parse testexpr) (parse thenexpr) (parse elseexpr))
      )
    ]
    [(and (list? exp))
      (let ([rator (first exp)] [args (rest exp)])
        (app (parse rator) (map parse args))
      )
    ]
    [else raise "unknown language construct"]
  )
)
(define-datatype proc proc?
  [prim-proc
    ;; prim refers to a scheme procedure
    (prim procedure?)
    ;; sig is the signature
    (sig (list-of procedure?))] 
  [closure
    (formals (list-of symbol?))
    (body ast?)
    (env env?)])

;;; prim? : proc? -> boolean?
(define prim-proc?
  (lambda (p)
    (cases proc p
      [prim-proc (prim sig) #t]
      [else #f])))

(define closure? 
  (lambda (p)
    (cases proc p
      [prim-proc (prim sig) #f]
      [else #t])))
;;; expressible-value? : any/c -> boolean?
(define expressible-value?
  (or/c number? boolean? proc?))
;;; denotable-value? :any/c -> boolean?
(define denotable-value?
  (or/c number? boolean? proc?))
;;; implement all procedures in the list
(define (numberOrBoolean? v) (or (number? v) (boolean? v)))

(define +p (prim-proc + (list number? number?)))
(define -p (prim-proc - (list number? number?)))
(define *p (prim-proc * (list number? number?)))
(define /p (prim-proc / (list number? number?)))
(define <p (prim-proc < (list number? number?)))
(define <=p (prim-proc <= (list number? number?)))
(define eq?p (prim-proc eq? (list numberOrBoolean? numberOrBoolean?)))
(define 0?p (prim-proc zero? (list number?)))
(define !p (prim-proc not (list boolean?)))
(define *init-env*
  (extended-env
   '(+ - * / < <= eq? 0? !)
   (list +p -p *p /p <p <=p eq?p 0?p !p)
   (empty-env)))
(define (eval-ast a e)
  (define (typecheck-num v)
    (if (number? v)
      v
      (raise "expected number")
    )
  )
  (define (typecheck-bool v)
    (if (boolean? v)
      v
      (raise "expected bool")
    )
  )
  (cases ast a
    [num (n) n]
    [bool (b) b]
    [id-ref (sym) (lookup-env e sym)]
    [assume (bindings body)
      (define (extract-bindings bindings)
        (define (loop bindings syms vals)
          (cond
            [(null? bindings) (list syms vals)]
            [else
              (let* ([binding (first bindings)] [id (bind-id binding)] [expr (bind-ast binding)])
                (loop (rest bindings) (cons id syms) (cons (eval-ast expr e) vals))
              )
            ]
          )
        )
        (loop bindings null null)
      )
      (let* ([unpacked (extract-bindings bindings)] [syms (first unpacked)] [vals (second unpacked)])
        (eval-ast body (extended-env syms vals e))
      )
    ]
    [ifte (testexpr thenexpr elseexpr)
      (if (typecheck-bool (eval-ast testexpr e))
        (eval-ast thenexpr e)
        (eval-ast elseexpr e)
      )
    ]
    [function (formals body)
      (closure formals body e)
    ]
    [app (rator rands)
      (cases proc (eval-ast rator e)
        [closure (formals body gamma)
          (eval-ast body (extended-env formals (map (lambda (ast) (eval-ast ast e)) rands) gamma))
        ]
        [prim-proc (prim sig)
          (apply prim (map (lambda (ast) (eval-ast ast e)) rands))
        ]
      )
    ]
  )
)


(provide (all-defined-out))
