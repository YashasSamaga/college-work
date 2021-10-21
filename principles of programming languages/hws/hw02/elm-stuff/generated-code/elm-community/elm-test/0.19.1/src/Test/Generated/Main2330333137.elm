module Test.Generated.Main2330333137 exposing (main)

import SampleTests

import Test.Reporter.Reporter exposing (Report(..))
import Console.Text exposing (UseColor(..))
import Test.Runner.Node
import Test

main : Test.Runner.Node.TestProgram
main =
    [     Test.describe "SampleTests" [SampleTests.test_tree_map,
    SampleTests.test_search,
    SampleTests.test_count_internal,
    SampleTests.test_product,
    SampleTests.test_countoccur,
    SampleTests.test_invert,
    SampleTests.test_repeat,
    SampleTests.test_merge,
    SampleTests.test_every,
    SampleTests.test_postorder,
    SampleTests.test_value_at_path,
    SampleTests.test_count_leaves,
    SampleTests.test_preorder,
    SampleTests.test_inorder,
    SampleTests.test_update,
    SampleTests.test_count_nodes,
    SampleTests.test_insert] ]
        |> Test.concat
        |> Test.Runner.Node.run { runs = Nothing, report = (ConsoleReport UseColor), seed = 116203323959872, processes = 8, paths = ["/home/yashas/Desktop/semester/popl/popl-assignments/hws/hw02/tests/SampleTests.elm"]}