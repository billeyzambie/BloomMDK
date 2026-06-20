#pragma once

#include "EventContexts.h"
#include <vector>
#include "Bloom.h"

template <class ContextT> class BLOOM_API Event
{
	using ContextFunctionPointer = void (*)(ContextT &);

  private:
	std::vector<ContextFunctionPointer> mFunctionPointers;

  public:
	ContextFunctionPointer operator+=(ContextFunctionPointer theFunctionPointer)
	{
		for (size_t i = 0; i < mFunctionPointers.size(); i++)
		{
			auto &aFunctionPointer = mFunctionPointers[i];
			if (!aFunctionPointer)
			{
				aFunctionPointer = theFunctionPointer;
				return theFunctionPointer;
			}
		}
		mFunctionPointers.push_back(theFunctionPointer);
		return theFunctionPointer;
	}

	ContextFunctionPointer operator-=(ContextFunctionPointer theFunctionPointer)
	{
		for (auto &aFunctionPointer : mFunctionPointers)
		{
			if (aFunctionPointer == theFunctionPointer)
				aFunctionPointer = nullptr;
		}
		return theFunctionPointer;
	}

	ContextT &Execute(ContextT &theContext) const
	{
		for (const auto &aFunctionPointer : mFunctionPointers)
		{
			if (aFunctionPointer)
				aFunctionPointer(theContext);
			if (theContext.mCanceled)
				break;
		}
		return theContext;
	}

	ContextT Execute(ContextT &&theContext) const
	{
		for (const auto &aFunctionPointer : mFunctionPointers)
		{
			if (aFunctionPointer)
				aFunctionPointer(theContext);
			if (theContext.mCanceled)
				break;
		}
		return theContext;
	}
};