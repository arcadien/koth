#pragma once

#include <actors/Player.h>
#include <actors/Weapon.h>
#include <api/ITransport.h>

namespace transport {
class Software : public ITransport {
 public:
  Software();

  void Wire(actors::Weapon *weapon, actors::Player *player) {
    _player = player;
  }
  void Queue(Action const &action) override;

  bool ActionAvailable() override { return false; }
  const Action GetAction() override { return Action(); }

 private:
  actors::Player *_player;
};
}  // namespace transport