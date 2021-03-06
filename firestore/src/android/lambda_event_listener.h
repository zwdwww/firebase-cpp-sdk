#ifndef FIREBASE_FIRESTORE_CLIENT_CPP_SRC_ANDROID_LAMBDA_EVENT_LISTENER_H_
#define FIREBASE_FIRESTORE_CLIENT_CPP_SRC_ANDROID_LAMBDA_EVENT_LISTENER_H_

#include "app/meta/move.h"
#include "firestore/src/include/firebase/firestore/event_listener.h"
#include "Firestore/core/include/firebase/firestore/firestore_errors.h"

#if defined(FIREBASE_USE_STD_FUNCTION) || defined(DOXYGEN)
#include <functional>

namespace firebase {
namespace firestore {

/**
 * A particular EventListener type that wraps a listener provided by user in the
 * form of lambda.
 */
template <typename T>
class LambdaEventListener : public EventListener<T> {
 public:
  LambdaEventListener(std::function<void(const T&, Error)> callback)
      : callback_(firebase::Move(callback)) {
    FIREBASE_ASSERT(callback);
  }

  void OnEvent(const T& value, Error error) override {
    callback_(value, error);
  }

 private:
  std::function<void(const T&, Error)> callback_;
};

template <>
class LambdaEventListener<void> : public EventListener<void> {
 public:
  LambdaEventListener(std::function<void()> callback)
      : callback_(firebase::Move(callback)) {
    FIREBASE_ASSERT(callback);
  }

  void OnEvent(Error) override { callback_(); }

 private:
  std::function<void()> callback_;
};

}  // namespace firestore
}  // namespace firebase

#endif  // defined(FIREBASE_USE_STD_FUNCTION) || defined(DOXYGEN)

#endif  // FIREBASE_FIRESTORE_CLIENT_CPP_SRC_ANDROID_LAMBDA_EVENT_LISTENER_H_
