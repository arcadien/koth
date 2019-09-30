#pragma once

#include <api/Action.h>
#include <api/Entity.h>

namespace Actor {

/*
 *
 *
 *
 *
 */
class Player {

public:
  Player() : _health(Entity::Tag::Health, 200) {}

  void SetEntityValue(Entity::Tag const &tag, uint16_t value) {
    _health.SetValue(value);
  }

  void Accept(Action const &action) {
    uint16_t newValue = action.Process(_health.GetValue());
    _health.SetValue(newValue);
  }

  uint16_t GetEntityValue(Entity::Tag const &tag) { return _health.GetValue(); }

private:
  Entity _health;
};

class Weapon {

public:
  Weapon(Action const &primaryAction, Action const &secondaryAction)
      : _primary(primaryAction), _secondary(secondaryAction) {}
  Action const &GetPrimary() { return _primary; }
  Action const &GetSecondary() { return _secondary; }

private:
  Action const &_primary;
  Action const &_secondary;
};

} // namespace Actor
