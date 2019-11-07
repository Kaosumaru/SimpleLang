#include <iostream>

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <vector>

using namespace llvm;

using namespace std;
    

Value* LogErrorV(const char* Str) {
	//LogError(Str);
	return nullptr;
}

void Test()
{
	static LLVMContext TheContext;
	static IRBuilder<> Builder(TheContext);
	static std::unique_ptr<Module> TheModule;
	static std::map<std::string, Value*> NamedValues;

	TheModule = std::make_unique<Module>("my cool jit", TheContext);

	Value *v1 = ConstantFP::get(TheContext, APFloat(1.0f));
	Value* v2 = ConstantFP::get(TheContext, APFloat(2.0f));

	Value* add = Builder.CreateFAdd(v1, v2, "addtmp");

	TheModule->print(errs(), nullptr);

}

int main() 
{
    //cout << "Hello, World!";
	Test();
    return 0;
}