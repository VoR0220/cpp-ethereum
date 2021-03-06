#include "Cache.h"
#include <unordered_map>
#include <cassert>
#include <iostream>
#include <llvm/IR/Module.h>
#include <llvm/Support/Path.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/raw_os_ostream.h>

namespace dev
{
namespace eth
{
namespace jit
{

//#define LOG(...) std::cerr << "CACHE "
#define LOG(...) std::ostream(nullptr)

ObjectCache* Cache::getObjectCache()
{
	static ObjectCache objectCache;
	return &objectCache;
}


void ObjectCache::notifyObjectCompiled(llvm::Module const* _module, llvm::MemoryBuffer const* _object)
{
	auto&& id = _module->getModuleIdentifier();
	llvm::SmallString<256> cachePath;
	llvm::sys::path::system_temp_directory(false, cachePath);
	llvm::sys::path::append(cachePath, "evm_objs");

	if (llvm::sys::fs::create_directory(cachePath.str()))
		return; // TODO: Add log

	llvm::sys::path::append(cachePath, id);

	std::string error;
	llvm::raw_fd_ostream cacheFile(cachePath.c_str(), error, llvm::sys::fs::F_None);
	cacheFile << _object->getBuffer();
}

llvm::MemoryBuffer* ObjectCache::getObject(llvm::Module const* _module)
{
	auto&& id = _module->getModuleIdentifier();
	llvm::SmallString<256> cachePath;
	llvm::sys::path::system_temp_directory(false, cachePath);
	llvm::sys::path::append(cachePath, "evm_objs", id);

	if (auto r = llvm::MemoryBuffer::getFile(cachePath.str(), -1, false))
		return llvm::MemoryBuffer::getMemBufferCopy(r.get()->getBuffer());
	else if (r.getError() != std::make_error_code(std::errc::no_such_file_or_directory))
		std::cerr << r.getError().message(); // TODO: Add log
	return nullptr;
}

}
}
}
