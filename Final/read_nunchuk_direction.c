#include <stdio.h>
#include <structure.h>
#include <read_nunchuk_direction.h>
#include <f3d_nunchuk.h>

direction_t getDirection(nunchuk_t* p) {

  if (p->jx > 230)
    return EAST;
  else if (p->jx < 20)
    return WEST;
  else if (p->jy > 230)
    return NORTH;
  else if (p->jy < 20)
    return SOUTH;
  else
    return STAY;
}
