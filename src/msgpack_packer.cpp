// Copyright 2021 Kenji Brameld
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <string>
#include <map>
#include <utility>
#include <memory>
#include <vector>
#include "nao_lola/msgpack_packer.hpp"
#include "msgpack.hpp"
#include "nao_lola/lola_enums.hpp"
#include "nao_lola/index_conversion.hpp"

std::string MsgpackPacker::getPacked()
{
  msgpack::zone z;
  std::map<std::string, msgpack::object> map;

  if (position) {
    map.insert(std::make_pair("Position", msgpack::object(position, z)));
  }

  if (stiffness) {
    map.insert(std::make_pair("Stiffness", msgpack::object(stiffness, z)));
  }

  if (chest) {
    map.insert(std::make_pair("Chest", msgpack::object(chest, z)));
  }

  if (l_ear) {
    map.insert(std::make_pair("LEar", msgpack::object(l_ear, z)));
  }

  if (r_ear) {
    map.insert(std::make_pair("REar", msgpack::object(r_ear, z)));
  }

  if (l_eye) {
    map.insert(std::make_pair("LEye", msgpack::object(l_eye, z)));
  }

  if (r_eye) {
    map.insert(std::make_pair("REye", msgpack::object(r_eye, z)));
  }

  if (l_foot) {
    map.insert(std::make_pair("LFoot", msgpack::object(l_foot, z)));
  }

  if (r_foot) {
    map.insert(std::make_pair("RFoot", msgpack::object(r_foot, z)));
  }

  if (skull) {
    map.insert(std::make_pair("Skull", msgpack::object(skull, z)));
  }

  if (sonar) {
    map.insert(std::make_pair("Sonar", msgpack::object(sonar, z)));
  }

  std::stringstream buffer;
  msgpack::pack(buffer, map);
  std::string packed = buffer.str();

  return packed;
}

void MsgpackPacker::setJoints(std::shared_ptr<nao_interfaces::msg::Joints> joints)
{
  position = std::make_shared<std::vector<float>>(static_cast<int>(LolaEnums::Joint::NUM_JOINTS));
  stiffness = std::make_shared<std::vector<float>>(static_cast<int>(LolaEnums::Joint::NUM_JOINTS));
  for (unsigned i = 0; i < joints->NUMJOINTS; ++i) {
    LolaEnums::Joint lola_joint_index = IndexConversion::joint_msg_to_lola.at(i);
    position->at(static_cast<int>(lola_joint_index)) = joints->angles.at(i);
    stiffness->at(static_cast<int>(lola_joint_index)) = joints->stiffnesses.at(i);
  }
}

void MsgpackPacker::setChestLed(std::shared_ptr<nao_interfaces::msg::ChestLed> chestLed)
{
  chest = std::make_shared<std::vector<float>>(3);
  chest->at(0) = chestLed->color.r;
  chest->at(1) = chestLed->color.g;
  chest->at(2) = chestLed->color.b;
}

void MsgpackPacker::setLeftEarLeds(std::shared_ptr<nao_interfaces::msg::LeftEarLeds> leftEarLeds)
{
  l_ear = std::make_shared<std::vector<float>>(10);
  for (unsigned i = 0; i < leftEarLeds->NUM_LEDS; ++i) {
    l_ear->at(i) = leftEarLeds->intensities[i];
  }
}

void MsgpackPacker::setRightEarLeds(std::shared_ptr<nao_interfaces::msg::RightEarLeds> rightEarLeds)
{
  r_ear = std::make_shared<std::vector<float>>(10);
  for (unsigned i = 0; i < rightEarLeds->NUM_LEDS; ++i) {
    r_ear->at(i) = rightEarLeds->intensities[i];
  }
}

void MsgpackPacker::setLeftEyeLeds(std::shared_ptr<nao_interfaces::msg::LeftEyeLeds> leftEyeLeds)
{
  l_eye = std::make_shared<std::vector<float>>(24);
  for (unsigned i = 0; i < leftEyeLeds->NUM_LEDS; ++i) {
    LolaEnums::LeftEyeLeds lola_index = IndexConversion::left_eye_leds_msg_to_lola.at(i);
    l_eye->at(static_cast<int>(lola_index)) = leftEyeLeds->colors[i].r;
    l_eye->at(static_cast<int>(lola_index) + 8) = leftEyeLeds->colors[i].g;
    l_eye->at(static_cast<int>(lola_index) + 16) = leftEyeLeds->colors[i].b;
  }
}

void MsgpackPacker::setRightEyeLeds(std::shared_ptr<nao_interfaces::msg::RightEyeLeds> rightEyeLeds)
{
  r_eye = std::make_shared<std::vector<float>>(24);
  for (unsigned i = 0; i < rightEyeLeds->NUM_LEDS; ++i) {
    LolaEnums::RightEyeLeds lola_index = IndexConversion::right_eye_leds_msg_to_lola.at(i);
    r_eye->at(static_cast<int>(lola_index)) = rightEyeLeds->colors[i].r;
    r_eye->at(static_cast<int>(lola_index) + 8) = rightEyeLeds->colors[i].g;
    r_eye->at(static_cast<int>(lola_index) + 16) = rightEyeLeds->colors[i].b;
  }
}

// void MsgpackPacker::setStiffness(std::shared_ptr<std::array<float>> stiffness)
// {
//   this->stiffness = stiffness;
// }

// void MsgpackPacker::setChest(std::shared_ptr<std::array<float>> chest)
// {
//   this->chest = chest;
// }

// void MsgpackPacker::setLEar(std::shared_ptr<std::array<float>> l_ear)
// {
//   this->l_ear = l_ear;
// }

// void MsgpackPacker::setREar(std::shared_ptr<std::array<float>> r_ear)
// {
//   this->r_ear = r_ear;
// }

// void MsgpackPacker::setLEye(std::shared_ptr<std::array<float>> l_eye)
// {
//   this->l_eye = l_eye;
// }

// void MsgpackPacker::setREye(std::shared_ptr<std::array<float>> r_eye)
// {
//   this->r_eye = r_eye;
// }

// void MsgpackPacker::setLFoot(std::shared_ptr<std::array<float>> l_foot)
// {
//   this->l_foot = l_foot;
// }

// void MsgpackPacker::setRFoot(std::shared_ptr<std::array<float>> r_foot)
// {
//   this->r_foot = r_foot;
// }

// void MsgpackPacker::setSkull(std::shared_ptr<std::array<float>> skull)
// {
//   this->skull = skull;
// }

// void MsgpackPacker::setSonar(std::shared_ptr<std::array<bool>> sonar)
// {
//   this->sonar = sonar;
// }
