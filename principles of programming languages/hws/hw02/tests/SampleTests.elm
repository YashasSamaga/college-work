module SampleTests exposing (..)
import Expect exposing (Expectation)
import Test exposing (..)
import Main exposing (..)
import Defns exposing (..)

test_repeat: Test
test_repeat =
    describe "Repeat"
             [ test "Repeat a number" <| 
                    \_ -> Expect.equal (repeat 3 5) [5, 5, 5]
             , test "Repeat a string" <|
                    \_ -> Expect.equal (repeat 4 "ab") ["ab", "ab", "ab", "ab"]
             , test "Repeat a list" <|
                    \_ -> Expect.equal (repeat 2 [1, 4]) [[1, 4], [1, 4]]
             ]
test_invert: Test
test_invert =
    describe "invert-tests"
             [ test "2-list is (number number)" <|
                    \_ -> Expect.equal (invert [[1, 100], [2, 300], [5, 600], [8, 200]])
                                       [[100, 1], [300, 2], [600, 5], [200, 8]]
             ]
test_countoccur: Test
test_countoccur =
    describe "Count Occurrences"
             [ test "Multiple Occurrences" <|
                    \_ -> Expect.equal (count_occurrences 3 [2, 3, 4, 3, 5, 6, 3]) 3
             ]
test_product: Test
test_product =
    describe "Product"
        [ test "Multiple Item" <|
               \_ -> Expect.equal (product [1, 3, 4] [10, 20])
                                  [[1, 10], [1, 20], [3, 10], [3, 20], [4, 10], [4, 20]]
        ]
isPositive x = x > 0

test_every : Test
test_every = 
    describe "Every"
             [ test "All Pass" <|
                    \_ -> Expect.equal (every isPositive [10, 40, 60])
                                       True
             , test "One Fail" <|
                    \_ -> Expect.equal (every isPositive [40, (-20), 100])
                                       False
             ]
test_merge: Test
test_merge =
    describe "Merge"
             [ test "Both lists length > 1" <|
                    \_ -> Expect.equal (merge [10, 50, 60, 100] [1, 3, 6, 9])
                                       [1, 3, 6, 9, 10, 50, 60, 100]
             ]
singleton_tree = Leaf 10

regular_tree =
    Node 100
         (Node 50
               (Node 200
                     (Leaf 5)
                     (Leaf 6))
               (Leaf 80))
         (Leaf 40)
test_preorder : Test
test_preorder =
    describe "Preorder"
             [ test "singleton" <|
                    \_ -> Expect.equal (preorder singleton_tree)
                                         [10]
             , test "larger" <|
                    \_ -> Expect.equal (preorder regular_tree)
                                         [100, 50 ,200, 5, 6, 80, 40]
             ]
test_inorder : Test
test_inorder =
    describe "Inorder"
             [ test "singleton" <|
                    \_ -> Expect.equal (inorder singleton_tree)
                                         [10]
             , test "larger" <|
                    \_ -> Expect.equal (inorder regular_tree)
                                         [5, 200, 6, 50, 80, 100, 40]
             ]
test_postorder : Test
test_postorder =
    describe "Postorder"
             [ test "singleton" <|
                    \_ -> Expect.equal (postorder singleton_tree)
                                         [10]
             , test "larger" <|
                    \_ -> Expect.equal (postorder regular_tree)
                                         [5, 6, 200, 80, 50, 40, 100]
             ]
test_count_nodes: Test
test_count_nodes =
    describe "Count Nodes"
             [ test "singleton" <|
                    \_ -> Expect.equal (count_nodes singleton_tree)
                                       1
             , test "larger" <|
                    \_ -> Expect.equal (count_nodes regular_tree)
                                       7
             ]
test_count_leaves: Test
test_count_leaves =
    describe "Count Leaves"
             [ test "singleton" <|
                    \_ -> Expect.equal (count_leaves singleton_tree)
                                       1
             , test "larger" <|
                    \_ -> Expect.equal (count_leaves regular_tree)
                                       4
             ]
test_count_internal: Test
test_count_internal =
    describe "Count Internals"
             [ test "singleton" <|
                    \_ -> Expect.equal (count_internal singleton_tree)
                                       0
             , test "larger" <|
                    \_ -> Expect.equal (count_internal regular_tree)
                                       3
             ]
test_tree_map : Test
test_tree_map =
    describe "Tree Map"
         [ test "singleton" <|
                \_ -> Expect.equal (tree_map
                                   (\v -> v+1)
                                   singleton_tree)
                                   (Leaf 11)
         , test "No change" <|
                \_ -> Expect.equal (tree_map
                                   (\v -> v)
                                   regular_tree)
                                   (regular_tree)
         ]

test_value_at_path: Test
test_value_at_path =
    describe "Value at Path"
             [ test "left-right" <|
                    \_ -> Expect.equal (value_at_path
                                              [Left, Right]
                                              regular_tree)
                                             (Just 80)
             , test "root" <|
                    \_ -> Expect.equal (value_at_path 
                                              []
                                              regular_tree)
                                             (Just 100)
             , test "nothing" <|
                    \_ -> Expect.equal (value_at_path 
                                              [Left, Right]
                                              singleton_tree)
                                             Nothing
             ]
test_search: Test
test_search =
    describe "Search"
             [ test "found" <|
                    \_ -> Expect.equal (search
                                              200
                                              regular_tree)
                                             (Just [Left, Left])
             ]
test_update : Test
test_update =
    describe "Update"
             [ test "update" <|
                    \_ -> Expect.equal (update
                                              [Left]
                                              (\x -> x+1)
                                              singleton_tree)
                                       (Leaf 10)
             ]
test_insert =
    describe "Insert"
             [ test "insert" <|
                    \_ -> Expect.equal (tree_insert
                                      []
                                      (Leaf 3)
                                      (Leaf 5)
                                      singleton_tree)
                                 (Node 10
                                       (Leaf 3)
                                       (Leaf 5))
             ]
