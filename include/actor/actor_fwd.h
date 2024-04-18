#pragma once

#include <memory>

namespace df {
class Actor;
using PtrActor = std::shared_ptr<Actor>;
using WeakPtrActor = std::weak_ptr<Actor>;

using Port = size_t;
} // namespace df
