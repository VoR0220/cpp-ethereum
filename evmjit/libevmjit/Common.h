#pragma once

#include <vector>
#include <boost/multiprecision/cpp_int.hpp>

namespace dev
{
namespace eth
{
namespace jit
{

using byte = uint8_t;
using bytes = std::vector<byte>;
using u256 = boost::multiprecision::uint256_t;
using bigint = boost::multiprecision::cpp_int;

struct NoteChannel {};	// FIXME: Use some log library?

enum class ReturnCode
{
	Stop = 0,
	Return = 1,
	Suicide = 2,

	BadJumpDestination = 101,
	OutOfGas = 102,
	StackTooSmall = 103,
	BadInstruction = 104,

	LLVMConfigError = 201,
	LLVMCompileError = 202,
	LLVMLinkError = 203,
};

/// Representation of 256-bit value binary compatible with LLVM i256
// TODO: Replace with h256
struct i256
{
	uint64_t a;
	uint64_t b;
	uint64_t c;
	uint64_t d;
};
static_assert(sizeof(i256) == 32, "Wrong i265 size");

#define UNTESTED assert(false)

}
}
}
