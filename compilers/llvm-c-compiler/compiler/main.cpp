#include <iostream>

#include "antlr4-runtime.h"
#include "ExprLexer.h"
#include "ExprParser.h"

#include "ExprBuildASTVisitor.h"

#include "AST/tree.h"
#include "AST/Passes/PrettyPrintVisitor.h"
#include "AST/Passes/ConstantFoldingTransform.h"
#include "AST/Passes/TypeInference.h"

#include "CodeGen/IRGenerator.h"

using namespace std;
using namespace antlr4;

int main(int argc, const char* argv[]) {
    std::ifstream stream;

    cout << "Processing input file " << argv[1] << endl;
    stream.open(argv[1]);
    
    ANTLRInputStream input(stream);

    ExprLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    ExprParser parser(&tokens);    

    ExprParser::TranslationUnitContext *ctx = parser.translationUnit();

    ExprBuildASTVisitor ASTBuilder;

    std::shared_ptr<ast::TranslationUnit> tu = ASTBuilder.visitTranslationUnit(ctx);
    
    std::cout << "PRETTY PRINTER:" << std::endl;
    PrettyPrintVisitor visitor;
    //visitor.visit(*tu);

    std::cout << "\n\n\n";
    std::cout << "Applying constant folding transformation\n";
    ConstantFoldingTransform cft;

    cft.visit(*tu);
    std::cout << "\n\n\n";

    //visitor.visit(*tu);

    std::cout << "\n\n\n";
    std::cout << "Applying type inference transformation\n";
    TypeInference ti;
    ti.visit(*tu);
    std::cout << "\n\n\n";

    visitor.visit(*tu);

    codegen::IRGenerator irgen("main");
    irgen.visit(*tu);

    std::string str;
    irgen.dump(str);
    std::cout << str;

    std::ofstream outFile("dump.ll");
    outFile << str;
    return 0;
}
