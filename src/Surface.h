/*
 *  Surface.h
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

#ifndef SRC_SURFACE_H
#define SRC_SURFACE_H 1

#include "Common.h"

#include <vector>

namespace SRDummy
{
  /*
   * This class is used to represent closed surfaces (polygons) in the world,
   * which are described by vertices (coordinates). However, this is a basic
   * implementation which does the minimum checking and error reporting.
   *
   * DO NOT use this class for complex polygons and do not rely on it to
   * detect errors such as polygon edges cutting themselves or ill-formed
   * shapes.
   *
   * Also, this class only supports orthogonal polygons (only with right
   * angles).
   */
  class Surface
  {
  public:
    Surface() = default;

    Surface& operator<<(const Coordinate& c);
    bool  isComplete() const noexcept;
    bool  canClose  () const noexcept;
  private:
    std::vector<Coordinate> m_vCoordinates;

    friend class World;
  };
}

#endif
