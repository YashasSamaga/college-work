#lang racket

(require eopl)

(require rackunit)
(require rackunit/text-ui)
(require "datatypes.rkt")
(require "main.rkt")

(define repeat-fn-tests
  (test-suite "Repeat"
              (test-case "Repeat a number" (check-equal? (repeat 3 5) '(5 5 5)))
              (test-case "Repeat a string" (check-equal? (repeat 3 'hi) '(hi hi hi)))
              (test-case "Repeat a list" (check-equal? (repeat 2 '(ab ab)) '((ab ab) (ab ab))))
              (test-case "Repeat zero times" (check-equal? (repeat 0 4) '()))))
(define invert-fn-tests
  (test-suite "invert-tests"
            (test-case "2-list is (number number)"
                       (check-equal?
                        (invert '((1 100) (2 300) (5 600) (8 200)))
                        '((100 1) (300 2) (600 5) (200 8))))
            (test-case "2-list is (any any)"
                       (check-equal?
                        (invert '((1 400) (a b) (xy 50) ((l m) 9)))
                        '((400 1) (b a) (50 xy) (9 (l m)))))
            (test-case "Found a non-2-list item"
                       (check-exn exn:fail?
                                  (lambda () (invert '(1 (2 3))))))
            (test-case "Not a List"
                       (check-exn exn:fail?
                                  (lambda () (invert 2))))))
(define count-occur-fn-tests
  (test-suite "Count Occurrences"
              (test-case "Single Occurrence"
                         (check-equal? (count-occurrences 3 '(2 3 4 3 5 6 3)) 3))
              (test-case "Multiple Occurrences"
                         (check-equal? (count-occurrences 2 '(2 3 4 3 5 6 3)) 1))
              (test-case "No Occurrence"
                         (check-equal? (count-occurrences 9 '(2 3 4 3 5 6 3)) 0))))
(define test-fn-product
  (test-suite "Product"
              (test-case "Single Item"
                         (check-equal? (product '(a) '(b))
                                       '((a b))))
              (test-case "Multiple Items"
                         (check-equal? (product '(a b c) '(e d))
                                       '((a e) (a d) (b e) (b d) (c e) (c d))))
              (test-case "Any one null"
                         (check-equal? (product '() '(e d))
                                       '(e d)))
              ))
(define test-fn-every
  (test-suite "Every"
              (test-case "All Pass"
                         (check-equal? (every symbol? '(a b d g))
                                       #t))
              (test-case "One Fail"
                         (check-equal? (every integer? (list 3 5 7 'd))
                                       #f))
              ))
(define test-fn-merge
  (test-suite "Merge"
              (test-case "Both lists length > 1"
                         (check-equal? (merge (list 10 50 60 100) (list 1 3 6 9))
                                       (list 1 3 6 9 10 50 60 100)))
              (test-case "One list with single item"
                         (check-equal? (merge (list 55) (list 40 60 70 120))
                                       (list 40 55 60 70 120)))
              ))
(define test-fn-flatten
  (test-suite "Flatten"
              (test-case "Already Flat"
                         (check-equal? (flatten '(a b e 4 6 r 9 s))
                                       '(a b e 4 6 r 9 s)))
              (test-case "Nested"
                         (check-equal? (flatten '(g (3 (5) (f) (d e)) (9) 1))
                                       '(g 3 5 f d e 9 1)))
              ))


(define singleton-tree (lnode 10))

(define small-tree
  (inode 20
         (lnode 30)
         (lnode 40)))

(define larger-tree
  (inode 100
         (inode 50
                (inode 200
                       (lnode 5)
                       (lnode 6))
                (lnode 80))
         (lnode 40)))

(define test-preorder 
  (test-suite "Preorder"
              (test-case "singleton"
                         (check-equal? (traverse/preorder singleton-tree)
                                       (list 10)))
              (test-case "small"
                         (check-equal? (traverse/preorder small-tree)
                                       (list 20 30 40)))
              (test-case "larger"
                         (check-equal? (traverse/preorder larger-tree)
                                       (list 100 50 200 5 6 80 40)))))
(define test-inorder
  (test-suite "Inorder"
              (test-case "singleton"
                         (check-equal? (traverse/inorder singleton-tree)
                                       (list 10)))
              (test-case "small"
                         (check-equal? (traverse/inorder small-tree)
                                       (list 30 20 40)))
              (test-case "larger"
                         (check-equal? (traverse/inorder larger-tree)
                                       (list 5 200 6 50 80 100 40)))))
(define test-postorder
  (test-suite "Postorder"
              (test-case "singleton"
                         (check-equal? (traverse/postorder singleton-tree)
                                       (list 10)))
              (test-case "small"
                         (check-equal? (traverse/postorder small-tree)
                                       (list 30 40 20)))
              (test-case "larger"
                         (check-equal? (traverse/postorder larger-tree)
                                       (list 5 6 200 80 50 40 100)))))
(define test-count-nodes
  (test-suite "Count Nodes"
              (test-case "singleton"
                         (check-equal? (count-nodes singleton-tree)
                                       1))
              (test-case "small"
                         (check-equal? (count-nodes small-tree)
                                       3))
              (test-case "larger"
                         (check-equal? (count-nodes larger-tree)
                                       7))))
(define test-count-leaves
  (test-suite "Count Leaves"
              (test-case "singleton"
                         (check-equal? (count-leaves singleton-tree)
                                       1))
              (test-case "small"
                         (check-equal? (count-leaves small-tree)
                                       2))
              (test-case "larger"
                         (check-equal? (count-leaves larger-tree)
                                       4))))
(define test-count-internal
  (test-suite "Count Internal"
              (test-case "singleton"
                         (check-equal? (count-internal singleton-tree)
                                       0))
              (test-case "small"
                         (check-equal? (count-internal small-tree)
                                       1))
              (test-case "larger"
                         (check-equal? (count-internal larger-tree)
                                       3))))
(define test-tree-map
  (test-suite "Tree Map"
              (test-case "singleton"
                         (check-equal? (tree/map 
                                        add1 singleton-tree
                                        )
                                       (lnode 11)))
              (test-case "small"
                         (check-equal? (tree/map 
                                        add1 small-tree
                                        )
                                       (inode 21
                                                      (lnode 31)
                                                      (lnode 41))))
              ))
(define path-item (list "left" "right"))
(define test-value-at-path
  (test-suite "Value at Path"
              (test-case "left-right"
                         (check-equal? (value-at-path 
                                        (list "left" "right")
                                        larger-tree)
                                       80))
              (test-case "root"
                         (check-equal? (value-at-path 
                                        '()
                                        larger-tree)
                                       100))
              ))
(define test-search
  (test-suite "Search"
              (test-case "found"
                         (check-equal? (search 
                                        200
                                        larger-tree)
                                       (list "left" "left")))
              ))
(define test-update
  (test-suite "Update"
              (test-case "update"
                         (check-equal? (update
                                        (list "left")
                                        add1
                                        singleton-tree)
                                       (lnode 10)))
              ))
(define test-insert
  (test-suite "Insert"
              (test-case "insert"
                         (check-equal? (tree/insert
                                        '()
                                        (lnode 3)
                                        (lnode 5)
                                        singleton-tree)
                                       (inode 10
                                            (lnode 3)
                                            (lnode 5))))
              ))


(run-tests repeat-fn-tests)
(run-tests invert-fn-tests)
(run-tests count-occur-fn-tests)
(run-tests test-fn-product)
(run-tests test-fn-every)
(run-tests test-fn-merge)
(run-tests test-fn-flatten)
(run-tests test-preorder)
(run-tests test-inorder)
(run-tests test-postorder)
(run-tests test-count-nodes)
(run-tests test-count-leaves)
(run-tests test-count-internal)
(run-tests test-tree-map)

(run-tests test-value-at-path)
(run-tests test-search)
(run-tests test-update)
(run-tests test-insert)
