#include "ball.h"

class Command
{
public:
  virtual ~Command() {}
  virtual void execute(Ball& ball) = 0;
};


