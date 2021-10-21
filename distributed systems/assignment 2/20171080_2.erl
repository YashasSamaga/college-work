-module('20171080_2').
-export([main/1]).

createProcesses(NumProcs, Func, Args) -> createProcesses(1, NumProcs, Func, Args).
createProcesses(Current, NumProcs, _, _) when Current == NumProcs -> [];
createProcesses(Current, NumProcs, Func, Args) ->
    Pid = spawn(fun() -> Func(Current, Args) end),
    [Pid|createProcesses(Current + 1, NumProcs, Func, Args)].

setnth(1, [_|Rest], Value) -> [Value|Rest];
setnth(Idx, [First|Rest], Value) -> [First|setnth(Idx - 1, Rest, Value)].

arange(S, E) when S >= E -> [];
arange(S, E) -> [S|arange(S + 1, E)].

read_edge(InputHandle, AdjMatrix) ->
    {ok, [V1, V2, W]} = io:fread(InputHandle, "", "~d ~d ~d"),
    Row1 = lists:nth(V1, AdjMatrix),
    Row2 = lists:nth(V2, AdjMatrix),
    Row1m = setnth(V2, Row1, W),
    Row2m = setnth(V1, Row2, W),
    AdjMatrix1 = setnth(V1, AdjMatrix, Row1m),
    AdjMatrix2 = setnth(V2, AdjMatrix1, Row2m),
    AdjMatrix2.

read_edges(V, E, InputHandle) ->
    AdjMatrix = lists:duplicate(V, lists:duplicate(V, -1)),
    read_edges(V, E, 1, InputHandle, AdjMatrix).

read_edges(_, E, CurrentEdge, _, AdjMatrix) when CurrentEdge > E -> AdjMatrix;
read_edges(V, E, CurrentEdge, InputHandle, AdjMatrix) ->
    read_edges(V, E, CurrentEdge + 1, InputHandle, read_edge(InputHandle, AdjMatrix)).

broadcast([], _, _) -> [];
broadcast([Pid|PidList], Tag, Message) ->
    Pid ! {Tag, Message},
    broadcast(PidList, Tag, Message).

mindist([], _, _, CurIdx) -> CurIdx;
mindist([V|R], Dist, CurMin, CurIdx) ->
    VDist = lists:nth(V, Dist),
    if
        VDist < CurMin ->
            mindist(R, Dist, VDist, V);
        true ->
            mindist(R, Dist, CurMin, CurIdx)
    end.

pairwiseMinimum([], []) -> [];
pairwiseMinimum([First1|Rest1], [First2|Rest2]) ->
    if
        First1 > First2 ->
            [First2|pairwiseMinimum(Rest1, Rest2)];
        true ->
            [First1|pairwiseMinimum(Rest1, Rest2)]
    end.

getDist([], Dist) -> Dist;
getDist([_|PidList], Dist) ->
    receive
        {update, DistUpdate} ->
            DistFinal = pairwiseMinimum(Dist, DistUpdate),
            io:fwrite("master recv update >> before: ~w, update: ~w, after: ~w~n", [Dist, DistUpdate, DistFinal])
    end,
    getDist(PidList, DistFinal).

updateDist(_, _, StartIdx, EndIdx, Dist, _) when StartIdx >= EndIdx -> Dist;
updateDist(U, Q, StartIdx, EndIdx, Dist, URow) ->
    CurDist = lists:nth(StartIdx, Dist),
    UDist = lists:nth(U, Dist),
    EdgeW = lists:nth(StartIdx, URow),
    IsNodeMember = lists:member(StartIdx, Q),
    if
        (EdgeW == -1) or (not IsNodeMember) ->
            DistFinal = Dist;
        CurDist > UDist + EdgeW ->
            DistFinal = setnth(StartIdx, Dist, UDist + EdgeW);
        true ->
            DistFinal = Dist
    end,
    updateDist(U, Q, StartIdx + 1, EndIdx, DistFinal, URow).

slaveProcessUpdateListener(ID, RootPid, StartIdx, EndIdx, AdjMatrix) ->
    receive
        {selected, [U, Q, Dist]} ->
            io:fwrite("Slave process ~w recv selection >> U = ~w, Q = ~w, Dist = ~w~n", [ID, U, Q, Dist]),
            URow = lists:nth(U, AdjMatrix),
            LocalDist = updateDist(U, Q, StartIdx, EndIdx, Dist, URow),
            RootPid ! {update, LocalDist},
            io:fwrite("Slave process ~w sent updated dist >> Dist = ~w~n", [ID, LocalDist]),
            slaveProcessUpdateListener(ID, RootPid, StartIdx, EndIdx, AdjMatrix);
        {exit, []} ->
            io:fwrite("Slave process ~w recv exit~n", [ID]),
            []
    end.

slaveProcess(ID, [P, ProcessStride, V, AdjMatrix]) ->
    io:fwrite("Slave process ~w started.~n", [ID]),
    StartIdx = ProcessStride * ID + 1,
    if
        ID == P - 1 ->
            EndIdx = V + 1;
        true ->
            EndIdx = StartIdx + ProcessStride
    end,
    io:fwrite("Slave process ~w computes StartIdx=~w, EndIdx=~w.~n", [ID, StartIdx, EndIdx]),
    receive
        {pidlist, SentPidList} ->
            io:fwrite("Slave process ~w recv PidList.~n", [ID]),
            PidList = SentPidList
    end,
    [RootPid|_] = PidList,
    slaveProcessUpdateListener(ID, RootPid, StartIdx, EndIdx, AdjMatrix).

masterLoopIter([_|OtherPids], _, _, [], Dist, _) ->
    broadcast(OtherPids, exit, []),
    Dist;
masterLoopIter(PidList, StartIdx, EndIdx, Q, Dist, AdjMatrix) ->
    U = mindist(Q, Dist, lists:nth(lists:nth(1, Q), Dist), lists:nth(1, Q)), % select the closest pending node
    Qfinal = lists:delete(U, Q),
    io:fwrite("master loop iter >> Q = ~w, U = ~w, Qfinal = ~w, StartIdx=~w, EndIdx=~w~n", [Q, U, Qfinal, StartIdx, EndIdx]),
    [_|OtherPids] = PidList,
    broadcast(OtherPids, selected, [U, Qfinal, Dist]),
    io:fwrite("Master process 0 recv selection >> U = ~w, Q = ~w, Dist = ~w~n", [U, Qfinal, Dist]),
    URow = lists:nth(U, AdjMatrix),
    LocalDist = updateDist(U, Qfinal, StartIdx, EndIdx, Dist, URow),
    io:fwrite("Master process 0 computed updated dist >> Dist = ~w~n", [LocalDist]),
    DistFinal = getDist(OtherPids, LocalDist),
    masterLoopIter(PidList, StartIdx, EndIdx, Qfinal, DistFinal, AdjMatrix).

masterProcess(PidList, ProcessStride, V, S, AdjMatrix) ->
    Dist_pre = lists:duplicate(V, 1000000000), % TODO
    Dist = setnth(S, Dist_pre, 0),
    Q = arange(1, V + 1), % remaining nodes
    StartIdx = 1,
    EndIdx = StartIdx + ProcessStride,
    masterLoopIter(PidList, StartIdx, EndIdx, Q, Dist, AdjMatrix).

dumpList(OutputHandle, Dist) -> dumpList(OutputHandle, Dist, 1).
dumpList(_, [], _) -> [];
dumpList(OutputHandle, [First|Rest], CurrentIdx) ->
    io:fwrite(OutputHandle, "~w ~w~n", [CurrentIdx, First]),
    dumpList(OutputHandle, Rest, CurrentIdx + 1).

main([InputFile, OutputFile]) ->
    {ok, InputHandle} = file:open(InputFile, [read]),
    {ok, [P]} = io:fread(InputHandle, "", "~d"),
    {ok, [V, E]} = io:fread(InputHandle, "", "~d ~d"),
    AdjMatrix = read_edges(V, E, InputHandle),
    {ok, [S]} = io:fread(InputHandle, "", "~d"),
    ProcessFunc = fun(ID, Args) -> slaveProcess(ID, Args) end,
    ProcessStride = floor(V / P),
    PidList = [self()|createProcesses(P, ProcessFunc, [P, ProcessStride, V, AdjMatrix])],
    [_|OtherPids] = PidList,
    broadcast(OtherPids, pidlist, PidList), % self msg
    Dist = masterProcess(PidList, ProcessStride, V, S, AdjMatrix),
    {ok, OutputHandle} = file:open(OutputFile, [write]),
    dumpList(OutputHandle, Dist),
    file:close(OutputHandle).