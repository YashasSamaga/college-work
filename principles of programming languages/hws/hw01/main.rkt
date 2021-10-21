#lang racket/base

(require eopl)
(require "datatypes.rkt")

(define (repeat n x)
    (cond
        [(equal? n 0) (list)]
        [(equal? n 1) (list x)]
        [else (append (list x) (repeat (sub1 n) x))]
    )
)
(define (invert lst)
    (define (my-reverse lst)
        (cond
            [(null? lst) empty]
            [else (append (my-reverse (cdr lst)) (list (car lst)))]
        )
    )
    (define (my-map f lst)
        (cond
            [(null? lst) empty]
            [else (cons (f (car lst)) (my-map f (cdr lst)))]
        )
    )
    (my-map my-reverse lst)
)
(define (count-occurrences s lst)
    (cond
        [(null? lst) 0]
        [(equal? s (car lst)) (+ 1 (count-occurrences s (cdr lst)))]
        [else (count-occurrences s (cdr lst))]
    )
)
(define (product lst1 lst2)
    (define (product1 x lst)
        (cond
            [(null? lst) null]
            [else (append (list (list x (car lst))) (product1 x (cdr lst)))]
        )
    )
    (define (product2 lst1 lst2)
        (cond
            [(null? lst1) null]
            [(append (product1 (car lst1) lst2) (product2 (cdr lst1) lst2))]
        )
    )
    (cond
        [(and (null? lst1) (null? lst2)) (list)] ;; redundant but let's keep it for clarity
        [(null? lst1) lst2]
        [(null? lst2) lst1]
        [else (product2 lst1 lst2)]
    )
)
(define (every f lst) ;; andmap
    (cond
        [(null? lst) #t]
        [else (and (f (car lst)) (every f (cdr lst)))]
    )
)
(define (merge lst1 lst2)
    (cond
        [(and (null? lst1) (null? lst2)) null] ;; retundant but let's keep it for clarity
        [(null? lst1) lst2]
        [(null? lst2) lst1]
        [(<= (car lst1) (car lst2)) (append (list (car lst1)) (merge (cdr lst1) lst2))]
        [else (merge lst2 lst1)]
    )
)
(define (flatten lst)
    (if (null? lst)
        null
        (let
            ([x (car lst)] [r (cdr lst)])
            (cond
                [(list? x) (append (flatten x) (flatten r))]
                [else (append (list x) (flatten r))]
            )
        )
    )
)

(define (traverse/preorder tree)
  (cases full-binary-tree tree
    (internal-node (v l r) (append (list v) (traverse/preorder l) (traverse/preorder r)))
    (leaf-node (v) (list v))
  )
)
(define (traverse/inorder tree)
  (cases full-binary-tree tree
    (internal-node (v l r) (append (traverse/inorder l) (list v) (traverse/inorder r)))
    (leaf-node (v) (list v))
  )
)
(define (traverse/postorder tree)
  (cases full-binary-tree tree
    (internal-node (v l r) (append (traverse/postorder l) (traverse/postorder r) (list v)))
    (leaf-node (v) (list v))
  )
)
(define (count-nodes tree)
  (cases full-binary-tree tree
    (internal-node (v l r) (+ (count-nodes l) 1 (count-nodes r)))
    (leaf-node (v) 1)
  )
)
(define (count-leaves tree)
  (cases full-binary-tree tree
    (internal-node (v l r) (+ (count-leaves l) 0 (count-leaves r)))
    (leaf-node (v) 1)
  )
)
(define (count-internal tree)
  (cases full-binary-tree tree
    (internal-node (v l r) (+ (count-internal l) 1 (count-internal r)))
    (leaf-node (v) 0)
  )
)
(define (tree/map f tree)
  (cases full-binary-tree tree
    (internal-node (v l r) (inode (f v) (tree/map f l) (tree/map f r)))
    (leaf-node (v) (lnode (f v)))
  )
)
(define (value-at-path path tree)
  (cases full-binary-tree tree
    (internal-node (v l r)
      (cond
        [(null? path) v]
        [(equal? (car path) "left") (value-at-path (cdr path) l)]
        [(equal? (car path) "right") (value-at-path (cdr path) r)]
        [else (raise "invalid path item")]
      )
    )
    (leaf-node (v)
      (cond
        [(null? path) v]
        [else (raise "invalid path (seeks subtree at leaf node)")]
      )
    )
  )
)
(define (search key tree)
  (cases full-binary-tree tree
    (internal-node (v l r)
      (if (equal? v key)
        '()
        (cond
          [(list? (search key l)) (append (list "left") (search key l))]
          [(list? (search key r)) (append (list "right") (search key r))]
          [else #f]
        )
      )
    )
    (leaf-node (v)
      (cond
        [(equal? v key) '()]
        [else #f]
      )
    )
  )
)
(define (update path f tree)
  (cases full-binary-tree tree
    (internal-node (v l r)
      (cond
        [(null? path) (inode (f v) l r)]
        [(equal? (car path) "left") (inode v (update (cdr path) f l) r)]
        [(equal? (car path) "right") (inode v l (update (cdr path) f r))]
        [else (inode v l r)] ;; return unmodified tree for invalid path
      )
    )
    (leaf-node (v)
      (cond
        [(null? path) (lnode (f v))]
        [else (lnode v)] ;; return unmodified tree for invalid path
      )
    )
  )
)
(define (tree/insert path left-st right-st tree)
  (cases full-binary-tree tree
    (internal-node (v l r)
      (cond
        [(null? path) (inode v l r)] ;; return unmodified for invalid path
        [(equal? (car path) "left") (inode v (tree/insert (cdr path) left-st right-st l) r)]
        [(equal? (car path) "right") (inode v l (tree/insert (cdr path) left-st right-st r))]
        [else (inode v l r)]
      )
    )
    (leaf-node (v)
      (cond
        [(null? path) (inode v left-st right-st)]
        [else (lnode v)] ;; return unmodified tree for invalid path
      )
    )
  )
)

(provide repeat)
(provide invert)
(provide count-occurrences)
(provide product)
(provide every)
(provide merge)
(provide flatten)

(provide traverse/preorder)
(provide traverse/inorder)
(provide traverse/postorder)
(provide count-nodes)
(provide count-leaves)
(provide count-internal)
(provide tree/map)
(provide value-at-path)
(provide search)
(provide update)
(provide tree/insert)
