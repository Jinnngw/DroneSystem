#ifndef CELEBRATION_DECORATOR_H_
#define CELEBRATION_DECORATOR_H_

#include "IStrategy.h"
#include "PathStrategy.h"

/**
 * @brief this class inhertis from the IStrategy class and is represents
 * a celebration decorator where the entity will celebrate according to it.
 */
class ICelebrationDecorator : public PathStrategy {
 protected:
  PathStrategy* strategy = nullptr;
  float time = 0;

 public:
  /**
   * @brief Construct a new Celebration Decorator object
   *
   * @param[in] strategy the strategy to decorate onto
   * @param[in] time how long to celebrate
   */
  ICelebrationDecorator(PathStrategy* strategy, double time = 4);
  /**
   * @brief Celebration Destructor
   */
  virtual ~ICelebrationDecorator();
  /**
   * @brief Move the entity with the behavior as described for 4 seconds.
   * 
   * @param entity Entity to move
   * @param dt Delta Time
   */
  virtual void move(IEntity* entity, double dt);
  /**
   * @brief Check if the movement is completed by checking the time.
   *
   * @return True if complete, false if not complete
   */
  virtual bool isCompleted();
  /**
   * @brief Abstract method for specific celebration behavior.
   * @param entity Entity to celebrate.
   * @param dt Delta Time.
   */
  virtual void celebrate(IEntity* entity, double dt) = 0;
  /**
   * @brief Retrieves the path of the entity.
   * @return A vector of points representing the path.
   */
  virtual std::vector<std::vector<float>> getPath();
};

#endif  // CELEBRATION_DECORATOR_H_
