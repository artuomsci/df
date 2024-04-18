#include "buffer.h"

#include "actor/actor.h"

using namespace df;

Buffer::~Buffer(){};

void Buffer::setSource(Port index, const WeakPtrActor &src) {
  m_src = src;
  m_sourcePort = index;
  if (auto src = m_src.lock()) {
    src->attachOutput(index, shared_from_this());
  }
}

WeakPtrActor Buffer::source() const { return m_src; }

Port Buffer::sourcePort() const { return m_sourcePort; }

void Buffer::setTarget(Port index, const WeakPtrActor &tgt) {
  m_tgt = tgt;
  m_targetPort = index;
  if (auto tgt = m_tgt.lock()) {
    tgt->attachInput(index, shared_from_this());
  }
}

WeakPtrActor Buffer::target() const { return m_tgt; }

Port Buffer::targetPort() const { return m_targetPort; }

const Value &Buffer::operator[](size_t pos) { return m_data[pos]; }

bool Buffer::empty() const { return m_data.empty(); }

const Value &Buffer::value() const { return m_data.front(); }

void Buffer::pop() { m_data.pop_front(); }

void Buffer::clear() { m_data.clear(); }

void Buffer::push(const Value &val) {
  m_data.push_back(val);
}

size_t Buffer::size() const { return m_data.size(); }

void Buffer::moveDataTo(Buffer &other) { other.m_data = std::move(m_data); }
