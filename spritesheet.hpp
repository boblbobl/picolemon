#ifndef SPRITESHEET_HPP_INCLUDED_
#define SPRITESHEET_HPP_INCLUDED_

#include "picosystem.hpp"

using namespace picosystem;

extern buffer_t *custom_sprite_sheet;

enum sprites_ids {
  PIT_ICON,
  BAT_ICON,
  WUMPUS_ICON,
  PLAYER_FALLING,
  WUMPUS_TOP_TOOTH,
  WUMPUS_BOTTOM_TOOTH,
  WUMPUS_EYE,
  PLAYER_CARRIED,
  ARROW_NORTH,
  ARROW_EAST,
  ARROW_SOUTH,
  ARROW_WEST
};

#endif // SPRITESHEET_HPP_INCLUDED_
