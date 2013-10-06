/* 
 * File:   Event.h
 * Author: daddy
 *
 * Created on September 28, 2013, 10:47 AM
 */

#ifndef EVENT_H
#define	EVENT_H

#include <vector>
#include <algorithm>

template <typename... Args>
class Event {
public:
  Event() {}
  ~Event() {}

  Event& operator+=(void (*func)(Args...)) 
  {
    mDelegates.push_back(func);
    return *this;
  }

  Event& operator-=(void (*func)(Args...)) 
  {
    auto it = std::find(mDelegates.begin(), mDelegates.end(), func);
    
    if (it != mDelegates.end()) 
    {
      mDelegates.erase(it);      
    }
    return *this;
  }

  void Invoke(Args... args) 
  {
    for(auto i : mDelegates)
    {
      (*(*i))(args...);
    }
  }
private:
  std::vector<void (*)(Args...)> mDelegates;
};

#endif	/* EVENT_H */

