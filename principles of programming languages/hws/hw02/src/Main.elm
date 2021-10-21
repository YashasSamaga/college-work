module Main exposing (..)
import Defns exposing (..)

repeat : Int -> a -> List a
repeat n x =
    if n == 0 then
        []
    else
      x :: repeat (n - 1) x

invert : List (List a) -> List (List a)
invert twolst =
    let
        reverse lst = 
            case lst of
                [] -> []
                x :: xs -> (reverse xs) ++ [x]
        map f lst =
            case lst of
                [] -> []
                x :: xs -> (f x) :: (map f xs)
    in
    map reverse twolst

count_occurrences : a -> List a -> Int
count_occurrences s slist =
    case slist of
        [] -> 0
        x :: xs -> 
            if x == s then
                1 + (count_occurrences s xs)
            else
                (count_occurrences s xs)

product : List a -> List a -> List (List a)
product lstA lstB =
    let
        product1 val lst =
            case lst of
                [] -> []
                x :: xs -> [val, x] :: (product1 val xs) 
        product2 lst1 lst2 =
            case lst1 of
                [] -> []
                x :: xs -> (product1 x lst2) ++ (product2 xs lst2)
    in
    case (lstA, lstB) of
        ([], _) -> []
        (_, []) -> []
        (itemsA, itemsB) -> product2 itemsA itemsB 

every : (a -> Bool) -> List a -> Bool
every pred lst =
    case lst of
        [] -> True
        x :: xs -> (pred x) && (every pred xs)

merge : List Int -> List Int -> List Int
merge lst1 lst2 =
    case (lst1, lst2) of
        ([], []) -> []
        ([], items) -> items
        (items, []) -> items
        (x :: xs, y :: ys) ->
            if x <= y then
                x :: merge xs lst2
            else
                y :: merge lst1 ys


preorder : Tree -> List Int
preorder tree =
    case tree of
        Node v left right -> [v] ++ (preorder left) ++ (preorder right)
        Leaf v -> [v]

inorder : Tree -> List Int
inorder tree =
    case tree of
        Node v left right -> (inorder left) ++ [v] ++ (inorder right)
        Leaf v -> [v]

postorder : Tree -> List Int
postorder tree =
    case tree of
        Node v left right -> (postorder left) ++ (postorder right) ++ [v]
        Leaf v -> [v]

count_nodes : Tree -> Int
count_nodes tree =
    case tree of
        Node v left right -> (count_nodes left) + 1 + (count_nodes right)
        Leaf v -> 1

count_leaves : Tree -> Int
count_leaves tree =
    case tree of
        Node v left right -> (count_leaves left) + (count_leaves right)
        Leaf v -> 1

count_internal : Tree -> Int
count_internal tree =
    case tree of
        Node v left right -> (count_internal left) + 1 + (count_internal right)
        Leaf v -> 0

tree_map : (Int -> Int) -> Tree -> Tree
tree_map f tree =
    case tree of
        Node v left right -> Node (f v) (tree_map f left) (tree_map f right)
        Leaf v -> Leaf (f v)

value_at_path : List PathItem -> Tree -> Maybe Int
value_at_path path tree =
    case tree of
        Node v left right ->
            case path of
                [] -> Just v
                Left :: xs -> (value_at_path xs left)
                Right :: xs -> (value_at_path xs right)
        Leaf v ->
            case path of
                [] -> Just v
                _ -> Nothing

search : Int -> Tree -> Maybe (List PathItem)
search key tree =
    case tree of
        Node v left right ->
            if v == key then Just []
            else
                case (search key left) of
                    Nothing ->
                        case (search key right) of
                            Nothing -> Nothing
                            Just items -> Just (Right :: items)
                    Just items -> Just (Left :: items)
        Leaf v ->
            if v == key then
                Just []
            else Nothing

update : List PathItem -> (Int -> Int) -> Tree -> Tree
update path f tree =
    case tree of
        Node v left right ->
            case path of
                [] -> Node (f v) left right
                Left :: xs -> Node v (update xs f left) right
                Right :: xs -> Node v left (update xs f right)
        Leaf v ->
            case path of
                [] -> Leaf (f v)
                _ -> Leaf v

tree_insert : List PathItem -> Tree -> Tree -> Tree -> Tree
tree_insert path lst rst tree =
    case tree of
    Node v left right ->
        case path of
            [] -> Node v left right
            Left :: xs -> Node v (tree_insert xs lst rst left) right
            Right :: xs -> Node v left (tree_insert xs lst rst right)
    Leaf v ->
        case path of
            [] -> Node v lst rst
            _ -> Leaf v
