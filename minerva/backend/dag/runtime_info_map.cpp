#include "runtime_info_map.h"
#include <glog/logging.h>

using namespace std;

namespace minerva {

ostream& operator<<(ostream& os, NodeState s) {
  switch (s) {
    case NodeState::kReady:
      return os << "ready";
    case NodeState::kCompleted:
      return os << "completed";
    default:
      LOG(FATAL) << "unknown state";
      return os;
  }
}

RuntimeInfo::RuntimeInfo() : num_triggers_needed(0), reference_count(0), state(NodeState::kReady) {
}

void RuntimeInfoMap::AddNode(uint64_t id) {
  if (info_.find(id) != info_.end()) {
    LOG(FATAL) << "node #" << id << " already existed in runtime info map";
  }
  info_[id];
}

void RuntimeInfoMap::RemoveNode(uint64_t id) {
  CHECK_EQ(info_.erase(id), 1);
}

RuntimeInfo& RuntimeInfoMap::At(uint64_t id) {
  return info_.at(id);
}

NodeState RuntimeInfoMap::GetState(uint64_t id) {
  return info_.at(id).state;
}

}  // namespace minerva

