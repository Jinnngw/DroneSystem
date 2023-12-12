#ifndef IHUMAN_PUBLISHER_H_
#define IHUMAN_PUBLISHER_H_

#include <vector>
#include "ICarSubscriber.h"

/**
 * @class IHumanPublisher
 * @brief
 *
 */
class IHumanPublisher {
 public:
  IHumanPublisher(){};
  ~IHumanPublisher(){};

  /**
   * @brief Subscribes an observer to this entity.
   * @param observer The observer to subscribe.
   */
  virtual void subscribe(ICarSubscriber* observer) = 0;

  /**
   * @brief Unsubscribes an observer from this entity.
   * @param observer The observer to unsubscribe.
   */
  virtual void unsubscribe(ICarSubscriber* observer) = 0;

//   /**
//    * @brief Notifies all subscribed observers about the entity's state.
//    * @return True if the notification is successful.
//    */
//   virtual bool notifySubscribers(std::string context) = 0;

 protected:
  static std::vector<ICarSubscriber*> cars;
};

#endif