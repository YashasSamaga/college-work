#lang racket

(require eopl)
(require rackunit)
(require racket/match)
(provide (all-defined-out))


(define-datatype ast ast?
  [unaryop (op unaryop?) (rand ast?)]
  [binop (op binop?) (rand1 ast?) (rand2 ast?)]
  [ifte (c ast?) (t ast?) (e ast?)]
  [num (n number?)]
  [bool (b boolean?)]
  [id-ref (sym id?)]
  [assume (bindings (list-of bind?)) (body ast?)])
(define-datatype bind bind?
  [make-bind (b-id id?) (b-ast ast?)])

(define id? symbol?)
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
;;; expressible-value? : any/c -> boolean?
(define expressible-value?
  (lambda (thing)
    (or (number? thing)
      (boolean? thing))))
;;; denotable-value? :any/c -> boolean?
(define denotable-value?
  (lambda (thing)
    (or (number? thing)
      (boolean? thing))))
(struct exn:parse-error exn:fail ())
(define raise-parse-error 
 (lambda (err-msg)
   (raise (exn:parse-error err-msg (current-continuation-marks)))))
;;; parse :: any/c -> ast?  Raises exception exn:parse-error?
;;; Fill in the function parse here

(define (parse exp)
  (define (uop->symbol op)
    (match op
      ['! 'neg]
      [_ #f]
    )
  )
  (define (binop->symbol op)
    (match op
      ['+ 'add]
      ['- 'sub]
      ['* 'mul]
      ['/ 'div]
      ['< 'lt?]
      ['== 'eq?]
      [_ #f]
    )
  )
  (cond
    [(number? exp) (num exp)]
    [(boolean? exp) (bool exp)]
    [(id? exp) (id-ref exp)]
    [(and (list? exp) (= (length exp) 2))
      (let* ([opraw (first exp)] [op (uop->symbol opraw)] [exp1 (second exp)])
        (cond
          [(eq? op #f) (raise-parse-error "unknown unary operator")]
          [else (unaryop op (parse exp1))]
        )
      )
    ]
    [(and (list? exp) (= (length exp) 3) (equal? (first exp) 'assume))
      (let* ([bindingsraw (second exp)] [body (third exp)]
             [bindings (map (lambda (entry) (make-bind (first entry) (parse (second entry)))) bindingsraw)])
        (assume bindings (parse body))
      )
    ]
    [(and (list? exp) (= (length exp) 3))
      (let* ([opraw (first exp)] [op (binop->symbol opraw)] [exp1 (second exp)] [exp2 (third exp)])
        (cond
          [(eq? op #f) (raise-parse-error "unknown binary operator")]
          [else (binop op (parse exp1) (parse exp2))]
        )
      )
    ]
    [(and (list? exp) (= (length exp) 4) (equal? 'if (first exp)))
      (let* ([testexpr (second exp)] [thenexpr (third exp)] [elseexpr (fourth exp)])
        (ifte (parse testexpr) (parse thenexpr) (parse elseexpr))
      )
    ]
    [else (raise-parse-error "unknown token")]
  )
)
(define-datatype env env?
  [empty-env]
  [extended-env
    (syms (list-of symbol?))
    (vals (list-of denotable-value?))
    (outer-env env?)])
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
      [empty-env () #f]
      [else #t])))
;;; lookup-env: [env?  symbol?] -> any/c || exn:lookup-err?
(define (lookup-env e x)
  (cases env e
    [empty-env () (raise-lookup-error)]
    [extended-env (syms vals outer-env)
      (define (get-index lst item)
        (let ([mres (member item lst)])
          (if mres
            (- (length lst) (length mres))
            #f
          )
        )
      )
      (let ([idx (get-index syms x)])
        (if idx
          (list-ref vals idx)
          (lookup-env outer-env x)
        )
      )
    ]
  )
)
(struct exn:lookup-error exn:fail ())
(define raise-lookup-error 
  (lambda ()
    (raise (exn:lookup-error "unbound identifier" (current-continuation-marks)))))
(struct exn:exec-div-by-zero exn:fail ())
(define raise-exec-div-by-zero
  (lambda ()
    (raise (exn:exec-div-by-zero "div-by-0!" (current-continuation-marks)))))

(struct exn:exec-type-mismatch exn:fail ())
(define raise-exec-type-mismatch
  (lambda ()
    (raise (exn:exec-type-mismatch "type mismatch!" (current-continuation-marks)))))
;;; runtime-check :: [expressible? -> boolean?], exn? -> [expressible? -> expressible? || exn?] 
(define runtime-check
  (lambda (pred? exn)
    (lambda (v)
      (if (pred? v)
          v
          (exn)))))

(define typecheck-num
  (runtime-check number?  raise-exec-type-mismatch))

(define typecheck-bool 
  (runtime-check boolean? raise-exec-type-mismatch))

(define check-non-zero
  (runtime-check (not/c zero?) raise-exec-div-by-zero))
(define op-interpretation
  (lambda (op)
    (match op
      ['add +]
      ['sub -]
      ['mul *]
      ['div /]
      ['lt? <]
      ['eq? =]
      ['neg not]
      [_ error 'op-interpretation "unknown op"])))

;;; eval-ast :: [ast? env?] -> expressible-value? 
;;;                         || (or/c exn:exec-div-by-zero  exn:exec-type-mismatch exn:lookup-error)
(define (eval-ast a e)
  (cases ast a
    [num (n) n]
    [bool (b) b]
    [id-ref (sym) (lookup-env e sym)]
    [unaryop (op expr)
      (let ([expval (eval-ast expr e)] [f (op-interpretation op)])
        (match op
          ['neg (f (typecheck-bool expval))]
          [_ error 'op-interpretation "unknown op"]
        )
      )
    ]
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
    [binop (op expr1 expr2)
      (let ([exp1val (eval-ast expr1 e)] [exp2val (eval-ast expr2 e)] [f (op-interpretation op)])
        (match op
          ['add (f (typecheck-num exp1val) (typecheck-num exp2val))]
          ['sub (f (typecheck-num exp1val) (typecheck-num exp2val))]
          ['mul (f (typecheck-num exp1val) (typecheck-num exp2val))]
          ['div (f (typecheck-num exp1val) (check-non-zero (typecheck-num exp2val)))]
          ['lt? (f (typecheck-num exp1val) (typecheck-num exp2val))]
          ['eq? (f (typecheck-num exp1val) (typecheck-num exp2val))]
          [_ error 'op-interpretation "unknown op"]
        )
      )
    ]
  )
)
(define unaryop?
  (lambda (x)
    (match x
      ['neg #t]
      [_ #f])))
(define binop?
  (lambda (x)
    (match x
      ['add #t]
      ['sub #t]
      ['mul #t]
      ['div #t]
      ['lt? #t]
      ['eq? #t]
      [_ #f])))
(define ts-numop-incorrect-param-rand1
  (test-suite 
   "wrongly typed rand1 parameters"
   (for/list ([numerical-op '(add sub mul div lt? eq?)])
     (test-case (string-append (symbol->string numerical-op) "-type-mismatch-rand1")
       (check-exn exn:exec-type-mismatch?
                  (lambda () 
                    (eval-ast (binop numerical-op
                                     (binop 'lt? (num 10) (num 20)) ; boolean
                                     (num 10))
                              (empty-env))))))))

(define ts-numop-incorrect-param-rand2
  (test-suite
   "wrongly typed rand2 parameters"
   (for/list ([numerical-op '(add sub mul div)])
     (test-case (string-append (symbol->string numerical-op) "-type-mismatch-rand1")
       (check-exn exn:exec-type-mismatch?
                  (lambda () 
                    (eval-ast (binop numerical-op (num 10)
                                     (binop 'lt? (num 10) (num 20)))
                              (empty-env))))))))
