#pragma once

#include <memory>
#include <vector>

namespace df {
class Buffer;
using PtrBuffer = std::shared_ptr<Buffer>;
using WeakPtrBuffer = std::weak_ptr<Buffer>;
using BufferPack = std::vector<PtrBuffer>;
} // namespace df
