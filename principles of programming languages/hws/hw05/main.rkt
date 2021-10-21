#lang racket

(define-syntax colist
  (syntax-rules ()
    [(colist sym terms ...) 
     (lambda () (list sym terms ...))]))

;;; unroll :: term? -> term?
(define (unroll t)
  (if (procedure? t) (t) t))
;;; hd :: term? -> symbol?
(define (hd t)
  (car (unroll t)))

;;; tl :: term? -> term?
(define (tl t)
  (cdr (unroll t)))
(struct exn:type-error exn:fail ())

(define (raise-type-error)
  (raise (exn:type-error
          "Invalid Arguments"
          (current-continuation-marks))))
;;; term? -> term? -> boolean?
(define (bisimilar? t1 t2)
  (define (term? t)
    (cond
      [(and (list? t) (not (null? t))) #t]
      [(and (procedure? t)) #t]
      [else #f]
    )
  )
  (define (inlst item lst)
    (if (member item lst) #t #f)
  )
  (define (loop? t1 t2 assumptions)
    (define (same-args? lst1 lst2 assumptions)
      (if (null? lst1)
        #t
        (let* ([x (hd lst1)] [y (hd lst2)] [xs (tl lst1)] [ys (tl lst2)] [tpr1 (list x y)] [tpr2 (list y x)])
          (if (and (procedure? x) (procedure? y))
            (cond
              [(inlst tpr1 assumptions) (same-args? xs ys assumptions)]
              [(inlst tpr2 assumptions) (same-args? xs ys assumptions)]
              [else
                (if (same-args? xs ys (cons tpr1 assumptions))
                  #t
                  (loop? x y assumptions)
                )
              ]
            )
            (loop? x y assumptions)
          )          
        )
      )
    )
    (cond
      [(not (and (term? t1) (term? t2))) (raise-type-error)]
      [(not (equal? (length (unroll t1)) (length (unroll t2)))) #f]
      [(equal? (hd t1) (hd t2)) (same-args? (tl t1) (tl t2) assumptions)]
      [else #f]
    )
  )
  (loop? t1 t2 (list))
)

(provide bisimilar?)
(provide colist)
(provide (struct-out exn:type-error))
