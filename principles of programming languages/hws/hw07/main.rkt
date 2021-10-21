#lang racket

(require eopl)

(define-datatype ast ast?
  [num (datum number?)]
  [bool (datum boolean?)]
  [ifte (test ast?) (then ast?) (else-ast ast?)]
  [function
   (formals (list-of id?))
   (body ast?)]
  [recursive (fbinds (list-of fbind?)) (body ast?)]
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
(define-datatype fbind fbind?
  [make-fbind (fb-id id?)
              (fb-formals (list-of id?))
              (fb-body ast?)])

;;; fbind-id : fbind? -> id?
(define fbind-id
  (lambda (b)
    (cases fbind b
      [make-fbind (fb-id fb-formals fb-body) fb-id])))

;;; fbind-formals : fbind? -> (list-of id?)
(define fbind-formals
  (lambda (b)
    (cases fbind b
      [make-fbind (fb-id fb-formals fb-body) fb-formals])))

;;; fbind-body : fbind? -> ast?
(define fbind-body
  (lambda (b)
    (cases fbind b
      [make-fbind (fb-id fb-formals fb-body) fb-body])))
(define *keywords*
  '(ifte assume function recursive))

(define id?
  (lambda (x)
    (and
     (symbol? x)
     (not (memq x *keywords*)))))

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
    [(and (list? exp) (= (length exp) 3) (equal? (first exp) 'recursive))
      (let ([fbindings (second exp)] [body (third exp)])
        (define (build-fbind fbinding)
          (let ([fb-id (first fbinding)] [fb-formals (second fbinding)] [fb-body (third fbinding)])
            (if (andmap id? fb-formals)
              (make-fbind fb-id fb-formals (parse fb-body))
              (raise "formal parameters must be identifiers")
            )
          )
        )
        (recursive (map build-fbind fbindings) (parse body))
      )
    ]
    [(and (list? exp) (= (length exp) 4) (equal? 'ifte (first exp)))
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

(define-datatype env env?
  [empty-env]
  [extended-env
    (syms (list-of symbol?))
    (vals (list-of denotable-value?))
    (outer-env env?)]
  [extended-rec-env
    (fsyms (list-of symbol?))
    (lformals (list-of (list-of symbol?)))
    (bodies (list-of ast?))
    (outer-env env?)])
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
;;; empty-env? : env? -> boolean?
(define empty-env?
  (lambda (e)
    (cases env e
      [empty-env () #t]
      [else #f])))

;;; extended-env? : env? -> boolean?
(define extended-env?
  (lambda (e)
    (cases env e
      [extended-env (syms vals outer-env) #t]
      [else #f])))

;;; extended-rec-env? : env? -> boolean?
(define extended-rec-env?
  (lambda (e)
    (cases env e
      [extended-rec-env (fsyms lformals bodies outer-env) #t]
      [else #f])))
(define (lookup-env e x)
  (define (get-index lst item)
    (let ([mres (member item lst)])
      (if mres
        (- (length lst) (length mres))
        #f
      )
    )
  )
  (cases env e
    [empty-env () (raise "lookup failed")]
    [extended-env (syms vals outer-env)
      (let ([idx (get-index syms x)])
        (if idx
          (list-ref vals idx)
          (lookup-env outer-env x)
        )
      )
    ]
    [extended-rec-env (fsyms lformals bodies outer-env)
      (let ([idx (get-index fsyms x)])
        (if idx
          (closure (list-ref lformals idx) (list-ref bodies idx) e)
          (lookup-env outer-env x)
        )
      )
    ]
  )
)
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
    [recursive (fbinds body)
      (define (extract-bindings bindings)
        (define (loop bindings fsyms lformals bodies)
          (cond
            [(null? bindings) (list fsyms lformals bodies)]
            [else
              (let* ([binding (first bindings)] [id (fbind-id binding)] [formals (fbind-formals binding)] [body (fbind-body binding)])
                (loop (rest bindings) (cons id fsyms) (cons formals lformals) (cons body bodies))
              )
            ]
          )
        )
        (loop bindings null null null)
      )
      (let* ([unpacked (extract-bindings fbinds)] [fsyms (first unpacked)] [lformals (second unpacked)] [bodies (third unpacked)])
        (eval-ast body (extended-rec-env fsyms lformals bodies e))
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

(define *init-env*
  (extended-env
   '(+ - * / < <= eq? 0? !)
   (list +p -p *p /p <p <=p eq?p 0?p !p)
   (empty-env)))


(provide (all-defined-out))
