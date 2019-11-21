#ifndef CLASS_REGISTRATION_H
#define CLASS_REGISTRATION_H

#include <unordered_map>

namespace inventory {

template <typename Key, typename Value>
struct ClassRepos {
  static ClassRepos& instance(){
    static ClassRepos<Key, Value> repos;
    return repos;
  }

  void add(Key key, Value value) {
    classes.insert({key, value});
  }

  Value* lookup(Key key) {
    auto it = classes.find(key);
    return it != classes.end() ? &(it->second) : nullptr;
  }

private:
  ClassRepos() {}
  std::unordered_map<Key, Value> classes;
};

template <typename Key, typename Value>
struct ClassRegister{
  ClassRegister(Key key, Value value) {
    ClassRepos<Key, Value>::instance().add(key, value);
  }
};

}

#endif
