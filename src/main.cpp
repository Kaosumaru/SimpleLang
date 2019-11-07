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


	// create extern function add(A, B)
	const char* Name = "Add";
	auto Args = std::vector<std::string>{ "A", "B" };

	std::vector<Type*> Doubles(Args.size(), Type::getDoubleTy(TheContext));
	FunctionType* FT = FunctionType::get(Type::getDoubleTy(TheContext), Doubles, false);
	Function* F = Function::Create(FT, Function::ExternalLinkage, Name, TheModule.get());
	unsigned Idx = 0;
	for (auto& Arg : F->args())
		Arg.setName(Args[Idx++]);


	// create function definition
	Function* TheFunction = TheModule->getFunction(Name);

	if (!TheFunction->empty())
	{
		//functions cant be redefined
		assert(false);
	}

	BasicBlock* BB = BasicBlock::Create(TheContext, "entry", TheFunction);
	Builder.SetInsertPoint(BB);

	// Record the function arguments in the NamedValues map.
	NamedValues.clear();
	for (auto& Arg : TheFunction->args())
		NamedValues[Arg.getName()] = &Arg;

	Builder.CreateRet(add);

	// Validate the generated code, checking for consistency.
	verifyFunction(*TheFunction);


	TheModule->print(errs(), nullptr);

}

int main() 
{
    //cout << "Hello, World!";
	Test();
    return 0;
}