/*
 *  World.h
 *
 *  Copyright (C) 2019 Alexandru N. Onea <alexandru.onea@toporcomputing.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#ifndef SRC_WORLD_H
#define SRC_WORLD_H 1

#include <string>
#include <memory>

#include "Common.h"
#include "Surface.h"
#include "SRAgent.h"

namespace SRDummy
{
  class World
  {
  public:
    World(std::size_t nRows, std::size_t nCols, const Coordinate& agent);
    ~World();

    World(const World& other);
    World& operator=(const World& other);

    World(World&& other);
    World& operator=(World&& other);

    bool addSolidObject(const Surface& area);
    void updatePercept(bool (&percept) [8]);
    bool performAction(Action next);

    std::string toString() const;
  private:
    class WorldImpl;
    using WorldImplRef = std::unique_ptr<WorldImpl>;
    WorldImplRef m_pImpl;

    Coordinate   m_agentPosition;
  };
}

#endif
