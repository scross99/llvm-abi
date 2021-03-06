#ifndef LLVMABI_X86_X86_32ABITYPEINFO_HPP
#define LLVMABI_X86_X86_32ABITYPEINFO_HPP

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

#include <llvm-abi/ABITypeInfo.hpp>
#include <llvm-abi/DefaultABITypeInfo.hpp>
#include <llvm-abi/Type.hpp>
#include <llvm-abi/TypeBuilder.hpp>

namespace llvm_abi {
	
	namespace x86 {
		
		class X86_32ABITypeInfo: public ABITypeInfo,
		                         public DefaultABITypeInfoDelegate {
		public:
			X86_32ABITypeInfo(llvm::LLVMContext& llvmContext);
			
			const TypeBuilder& typeBuilder() const;
			
			DataSize getTypeRawSize(Type type) const;
			
			DataSize getTypeAllocSize(Type type) const;
			
			DataSize getTypeStoreSize(Type type) const;
			
			DataSize getTypeRequiredAlign(Type type) const;
			
			DataSize getTypePreferredAlign(Type type) const;
			
			llvm::Type* getLLVMType(Type type) const;
			
			llvm::SmallVector<DataSize, 8>
			calculateStructOffsets(llvm::ArrayRef<RecordMember> structMembers) const;
			
			bool isLegalVectorType(Type type) const;
			
			bool isBigEndian() const;
			
			bool isCharSigned() const;
			
			bool isHomogeneousAggregateBaseType(Type type) const;
			
			bool isHomogeneousAggregateSmallEnough(Type base,
			                                       uint64_t members) const;
			
			DataSize getPointerSize() const;
			DataSize getPointerAlign() const;
			
			DataSize getIntSize(IntegerKind kind) const;
			DataSize getIntAlign(IntegerKind kind) const;
			
			DataSize getFloatSize(FloatingPointKind kind) const;
			DataSize getFloatAlign(FloatingPointKind kind) const;
			
			DataSize getComplexSize(FloatingPointKind kind) const;
			DataSize getComplexAlign(FloatingPointKind kind) const;
			
			DataSize getArrayAlign(Type type) const;
			DataSize getVectorAlign(Type type) const;
			
			llvm::Type* getLongDoubleIRType() const;
			
		private:
			llvm::LLVMContext& llvmContext_;
			TypeBuilder typeBuilder_;
			DefaultABITypeInfo defaultABITypeInfo_;
			
		};
		
	}
	
}

#endif
