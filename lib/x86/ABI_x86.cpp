#include <vector>

#include <llvm-abi/ABI.hpp>
#include <llvm-abi/Type.hpp>

#include "ABI_x86.hpp"

namespace llvm_abi {
	
	ABI_x86::ABI_x86(llvm::Module* module)
	: llvmContext_(module->getContext()) { }
	
	ABI_x86::~ABI_x86() { }
	
	std::string ABI_x86::name() const {
		return "x86";
	}
	
	size_t ABI_x86::typeSize(Type type) const {
		switch (type.kind()) {
			case VoidType:
				return 0;
			case PointerType:
				return 4;
			case UnspecifiedWidthIntegerType: {
				switch (type.integerKind()) {
					case Bool:
						return 1;
					case Char:
					case SChar:
					case UChar:
						return 1;
					case Short:
					case UShort:
						return 2;
					case Int:
					case UInt:
						return 4;
					case Long:
					case ULong:
						return 4;
					case LongLong:
					case ULongLong:
						return 8;
					case SizeT:
					case SSizeT:
						return 4;
					case IntPtrT:
					case UIntPtrT:
					case PtrDiffT:
						return 4;
				}
				llvm_unreachable("Unknown Integer type kind.");
			}
			case FixedWidthIntegerType: {
				return type.integerWidth().roundUpToPowerOf2Bytes().asBytes();;
			}
			case FloatingPointType: {
				switch (type.floatingPointKind()) {
					case Float:
						return 4;
					case Double:
						return 8;
					case LongDouble:
						// NB: Apparently on Android this is the same as 'double'.
						return 12;
					case Float128:
						return 16;
				}
				llvm_unreachable("Unknown Float type kind.");
			}
			case ComplexType: {
				switch (type.complexKind()) {
					case Float:
						return 8;
					case Double:
						return 16;
					case LongDouble:
						// NB: Apparently on Android this is the same as 'double'.
						return 24;
					case Float128:
						return 32;
				}
				llvm_unreachable("Unknown Complex type kind.");
			}
			case StructType: {
				llvm_unreachable("TODO");
			}
			case ArrayType: {
				llvm_unreachable("TODO");
			}
		}
		llvm_unreachable("Unknown type kind.");
	}
	
	size_t ABI_x86::typeAlign(Type type) const {
		switch (type.kind()) {
			case VoidType:
				return 0;
			case PointerType:
				return 4;
			case UnspecifiedWidthIntegerType: {
				switch (type.integerKind()) {
					case Bool:
						return 1;
					case Char:
					case SChar:
					case UChar:
						return 1;
					case Short:
					case UShort:
						return 2;
					case Int:
					case UInt:
						return 4;
					case Long:
					case ULong:
						return 4;
					case LongLong:
					case ULongLong:
						return 4;
					case SizeT:
					case SSizeT:
						return 4;
					case IntPtrT:
					case UIntPtrT:
					case PtrDiffT:
						return 4;
				}
				llvm_unreachable("Unknown Integer type kind.");
			}
			case FixedWidthIntegerType: {
				return type.integerWidth().roundUpToPowerOf2Bytes().asBytes();
			}
			case FloatingPointType: {
				switch (type.floatingPointKind()) {
					case Float:
						return 4;
					case Double:
						return 4;
					case LongDouble:
						return 4;
					case Float128:
						return 16;
				}
				llvm_unreachable("Unknown Float type kind.");
			}
			case ComplexType: {
				switch (type.complexKind()) {
					case Float:
						return 4;
					case Double:
						return 4;
					case LongDouble:
						return 4;
					case Float128:
						return 16;
				}
				llvm_unreachable("Unknown Complex type kind.");
			}
			case StructType: {
				llvm_unreachable("TODO");
			}
			case ArrayType: {
				llvm_unreachable("TODO");
			}
		}
		llvm_unreachable("Unknown type kind.");
	}
	
	llvm::Type* ABI_x86::getLLVMType(const Type type) const {
		switch (type.kind()) {
			case VoidType:
				return llvm::Type::getVoidTy(llvmContext_);
			case PointerType:
				return llvm::Type::getInt8PtrTy(llvmContext_);
			case UnspecifiedWidthIntegerType:
			case FixedWidthIntegerType: {
				return llvm::IntegerType::get(llvmContext_, typeSize(type) * 8);
			}
			case FloatingPointType: {
				switch (type.floatingPointKind()) {
					case Float:
						return llvm::Type::getFloatTy(llvmContext_);
					case Double:
						return llvm::Type::getDoubleTy(llvmContext_);
					case LongDouble:
						return llvm::Type::getX86_FP80Ty(llvmContext_);
					case Float128:
						return llvm::Type::getFP128Ty(llvmContext_);
				}
				llvm_unreachable("Unknown Float type kind.");
			}
			case ComplexType: {
				llvm_unreachable("TODO");
			}
			case StructType: {
				llvm_unreachable("TODO");
			}
			case ArrayType: {
				llvm_unreachable("TODO");
			}
		}
	}
	
	std::vector<size_t> ABI_x86::calculateStructOffsets(llvm::ArrayRef<StructMember> /*structMembers*/) const {
		llvm_unreachable("TODO");
	}
	
	llvm::Type* ABI_x86::longDoubleType() const {
		return llvm::Type::getX86_FP80Ty(llvmContext_);
	}
	
	llvm::CallingConv::ID ABI_x86::getCallingConvention(const CallingConvention callingConvention) const {
		switch (callingConvention) {
			case CC_CDefault:
			case CC_CDecl:
			case CC_CppDefault:
				return llvm::CallingConv::C;
			case CC_StdCall:
				return llvm::CallingConv::X86_StdCall;
			case CC_FastCall:
				return llvm::CallingConv::X86_FastCall;
			case CC_ThisCall:
				return llvm::CallingConv::X86_ThisCall;
			case CC_Pascal:
				return llvm::CallingConv::X86_StdCall;
			default:
				llvm_unreachable("Invalid calling convention for ABI.");
		}
	}
	
	llvm::FunctionType* ABI_x86::getFunctionType(const FunctionType& /*functionType*/) const {
		llvm_unreachable("TODO");
	}
	
	llvm::AttributeSet ABI_x86::getAttributes(const FunctionType& /*functionType*/,
	                                          const llvm::AttributeSet /*existingAttributes*/) const {
		llvm_unreachable("TODO");
	}
	
	llvm::Value* ABI_x86::createCall(Builder& /*builder*/,
	                                 const FunctionType& /*functionType*/,
	                                 std::function<llvm::Value* (llvm::ArrayRef<llvm::Value*>)> /*callBuilder*/,
	                                 llvm::ArrayRef<llvm::Value*> /*arguments*/) {
		llvm_unreachable("TODO");
	}
	
	std::unique_ptr<FunctionEncoder> ABI_x86::createFunction(Builder& /*builder*/,
	                                                         const FunctionType& /*functionType*/,
	                                                         llvm::ArrayRef<llvm::Value*> /*arguments*/) {
		llvm_unreachable("TODO");
	}
	
}

