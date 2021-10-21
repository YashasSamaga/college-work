-module('20171080_1'). 
-export([main/1]). 

createProcesses(NumProcs, Func, Args) -> createProcesses(1, NumProcs, Func, Args).
createProcesses(Current, NumProcs, _, _) when Current == NumProcs -> [];
createProcesses(Current, NumProcs, Func, Args) ->
    Pid = spawn(fun() -> Func(Current, Args) end), 
    [Pid|createProcesses(Current + 1, NumProcs, Func, Args)].

broadcast([], _, _) -> [];
broadcast([Pid|PidList], Tag, Message) ->
    Pid ! {Tag, Message},
    broadcast(PidList, Tag, Message).

processLoop(ID, [P, OutputFile]) ->
    %io:fwrite("Process ~w starting.~n", [ID]),
    receive            
        {pidlist, PidList} ->
            %io:fwrite("Process ~w received pidlist.~n", [ID]),
            NextID = (ID + 1) rem P,
            NextPid = lists:nth(NextID + 1, PidList)
    end,
    %io:fwrite("Process ~w listening for token.~n", [ID]),
    receive
        {token, SenderID, Token} ->
            {ok, OutputHandle} = file:open(OutputFile, [append]),
            io:fwrite(OutputHandle, "Process ~w received token ~w from process ~w.~n", [ID, Token, SenderID]),
            file:close(OutputHandle),
            if
                ID == 0 ->
                    [];
                true ->
                    % io:fwrite("Sending token to ~w from ~w.~n", [NextPid, ID]),
                    NextPid ! {token, ID, Token}
            end
    end,
    %io:fwrite("Process ~w finished.~n", [ID]).
    [].

main([InputFile, OutputFile]) ->
    {ok, InputHandle} = file:open(InputFile, [read]),
    {ok, [P, M]} = io:fread(InputHandle, "", "~d ~d"),
    file:close(InputFile),
    file:delete(OutputFile),
    ProcessFunc = fun(ID, Args) -> processLoop(ID, Args) end,
    PidList = [self()|createProcesses(P, ProcessFunc, [P, OutputFile])],
    SecondPid = lists:nth(2, PidList),
    broadcast(PidList, pidlist, PidList),
    SecondPid ! {token, 0, M},
    processLoop(0, [P, OutputFile]).
    