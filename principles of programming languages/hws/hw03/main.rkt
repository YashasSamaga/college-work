#lang racket
(require eopl)
(require rackunit)
(require racket/match)
(provide (all-defined-out))


(define-datatype ast ast?
 [binop (op binop?) (rand1 ast?) (rand2 ast?)]
 [ifte (c ast?) (t ast?) (e ast?)]
 [num (n number?)]
 [bool (b boolean?)])
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
(struct exn:parse-error exn:fail ())
(define raise-parse-error 
 (lambda (err-msg)
   (raise (exn:parse-error err-msg (current-continuation-marks)))))
;;; parse :: any/c -> ast?  Raises exception exn:parse-error?
;;; Fill in the function parse here
(define (parse exp)
  (define (op->symbol op)
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
    [(and (list? exp) (= (length exp) 3))
      (let* ([opraw (first exp)] [op (op->symbol opraw)] [exp1 (second exp)] [exp2 (third exp)])
        (cond
          [(eq? op #f) (raise-parse-error "unknown binary operator")]
          [else (binop op (parse exp1) (parse exp2))]
        )
      )
    ]
    [(and (list? exp) (= (length exp) 4) (eq? 'if (first exp)))
      (let* ([testexpr (second exp)] [thenexpr (third exp)] [elseexpr (fourth exp)])
        (ifte (parse testexpr) (parse thenexpr) (parse elseexpr))
      )
    ]
    [else (raise-parse-error "unknown token")]
  )
)

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
      ['lt? <]
      ['eq? =]
      [_ error 'op-interpretation "unknown op"])))
;;; eval-ast :: ast? -> expressible? || (or/c exn:exec-div-by-zero  exn:exec-type-mismatch)
(define eval-ast
  (lambda (a)
    (cases ast a
      [num (n) n]
      [bool (b) b]
      [ifte (testexpr thenexpr elseexpr)
        (if (typecheck-bool (eval-ast testexpr))
          (eval-ast thenexpr)
          (eval-ast elseexpr)
        )
      ]
      [binop (op expr1 expr2)
        (let ([exp1val (eval-ast expr1)] [exp2val (eval-ast expr2)])
          (match op
            ['add (+ (typecheck-num exp1val) (typecheck-num exp2val))]
            ['sub (- (typecheck-num exp1val) (typecheck-num exp2val))]
            ['mul (* (typecheck-num exp1val) (typecheck-num exp2val))]
            ['div (/ (typecheck-num exp1val) (check-non-zero (typecheck-num exp2val)))]
            ['lt? (< (typecheck-num exp1val) (typecheck-num exp2val))]
            ['eq? (= (typecheck-num exp1val) (typecheck-num exp2val))]
            [_ error 'op-interpretation "unknown op"]
          )
        )
      ]
    )
  )
)
(define ts-numop-incorrect-param-rand1
  (test-suite 
   "wrongly typed rand1 parameters"
   (for/list ([numerical-op '(add sub mul div lt? eq?)])
     (test-case (string-append (symbol->string numerical-op) "-type-mismatch-rand1")
       (check-exn exn:exec-type-mismatch?
                  (lambda () 
                    (eval-ast (binop numerical-op
                                     (binop 'lt? (num 10) (num 20)) ; boolean
                                     (num 10)))))))))

(define ts-numop-incorrect-param-rand2
  (test-suite
   "wrongly typed rand2 parameters"
   (for/list ([numerical-op '(add sub mul div)])
     (test-case (string-append (symbol->string numerical-op) "-type-mismatch-rand1")
       (check-exn exn:exec-type-mismatch?
                  (lambda () 
                    (eval-ast (binop numerical-op (num 10)
                                     (binop 'lt? (num 10) (num 20))))))))))
