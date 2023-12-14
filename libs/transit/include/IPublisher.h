#ifndef PUBLISHER_H_
#define PUBLISHER_H_

#include <vector>
#include "IObserver.h"

/**
 * @class IPublisher
 * @brief
 *
 */
class IPublisher {
 public:
  IPublisher(){};
  ~IPublisher(){};

  /**
   * @brief Subscribes an observer to this entity.
   * @param observer The observer to subscribe.
   */
  virtual void subscribe(IObserver* observer) = 0;

  /**
   * @brief Unsubscribes an observer from this entity.
   * @param observer The observer to unsubscribe.
   */
  virtual void unsubscribe(IObserver* observer) = 0;

  /**
   * @brief Notifies all subscribed observers about the entity's state.
   * @return True if the notification is successful.
   */
  virtual bool notifySubscribers(std::string context) = 0;

 protected:
  std::vector<IObserver*> observers;
};

#endif
