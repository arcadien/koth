/*
 * This file is part of the KOTH distribution (https://github.com/arcadien/koth)
 *
 * Copyright (c) 2019 Aurélien Labrosse
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <actors/Player.h>
#include <api/Meta.h>
#include <transports/Dummy.h>
#include <weapons/Vampire.h>

#if not defined(AVR)
#define UNITY_OUTPUT_COLOR
#endif
#include <unity.h>

void Expect_Vampire_to_damage_target_user_when_using_vampire_primary_action();
void Expect_Vampire_to_heal_target_user_when_using_vampire_secondary_action();

int main(int, char **) {
  UNITY_BEGIN();
  RUN_TEST(
      Expect_Vampire_to_damage_target_user_when_using_vampire_primary_action);
  RUN_TEST(
      Expect_Vampire_to_heal_target_user_when_using_vampire_secondary_action);
  return UNITY_END();
}
void tearDown() {}
void setUp() {}

void Expect_Vampire_to_damage_target_user_when_using_vampire_primary_action() {
  transport::Dummy dummyTransport;
  Weapons::Vampire vampire(dummyTransport);
  actors::Player target;
  auto action = vampire.GetPrimary();
  target.SetEntityValue(Entity::Tag::Health, 10);
  target.Accept(action);
  uint16_t actualHealth = target.GetEntityValue(Entity::Tag::Health);
  TEST_ASSERT_EQUAL_INT(5, actualHealth);
}

void Expect_Vampire_to_heal_target_user_when_using_vampire_secondary_action() {
  transport::Dummy dummyTransport;
  Weapons::Vampire vampire(dummyTransport);
  Entity health(Entity::Tag::Health, 1);
  actors::Player target;
  auto action = vampire.GetSecondary();
  target.SetEntityValue(Entity::Tag::Health, 10);
  target.Accept(action);
  uint16_t actualHealth = target.GetEntityValue(Entity::Tag::Health);
  TEST_ASSERT_EQUAL_INT(15, actualHealth);
}
