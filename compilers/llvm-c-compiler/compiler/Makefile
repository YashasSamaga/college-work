ANTLR4=java -Xmx500M -cp "/usr/local/lib/antlr-4.8-complete.jar:$CLASSPATH" org.antlr.v4.Tool

SOURCE_FILES=main.cpp ExprLexer.cpp ExprParser.cpp ExprBuildASTVisitor.cpp lib/AST/Passes/*.cpp  lib/CodeGen/*.cpp
INCLUDE_DIRS=-I/usr/include/llvm-c-10/ -I/usr/include/llvm-10/ -I/usr/local/include/antlr4-runtime -Iinclude 

LDFLAGS= `llvm-config --ldflags`
LIBS= `llvm-config --libs` -lantlr4-runtime

CXXFLAGS=-g -std=c++17

.PHONY: all antlr compiler

all: antlr compiler

antlr:	Expr.g4
		$(ANTLR4) -Dlanguage=Cpp -no-listener -visitor Expr.g4

compiler:
		g++ $(INCLUDE_DIRS) $(SOURCE_FILES) $(CXXFLAGS) $(LDFLAGS) $(LIBS) -o expr 

clean:	
		rm -f ExprLexer.h ExprParser.h expr *.tokens *.interp ExprBaseVisitor.cpp \
		rm -f ExprBaseVisitor.h ExprParser.cpp ExprLexer.cpp ExprBaseVisitor.cpp  \ 
		rm -f ExprVisitor.cpp  ExprVisitor.h

