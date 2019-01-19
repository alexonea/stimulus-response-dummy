/*
 *  Surface.cc
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

#include "Surface.h"

#include <stdexcept>

namespace SRDummy
{
  Surface&
  Surface::operator<<
  (const Coordinate& c)
  {
    if (m_vCoordinates.empty())
    {
      m_vCoordinates.push_back(c);
      return *this;
    }

    if (m_vCoordinates.back() == c)
      throw std::runtime_error("Cannot repeat coordinates");

    const auto& last = m_vCoordinates.back();
    if ((last.first != c.first) && (last.second != c.second))
      throw std::runtime_error("Invalid area");

    if (m_vCoordinates.size() > 1 &&
        m_vCoordinates.front() == m_vCoordinates.back())
      throw std::runtime_error("Already completed");

    m_vCoordinates.push_back(c);
    return *this;
  }

  bool
  Surface::isComplete
  () const noexcept
  {
    if (m_vCoordinates.empty())
      return false;

    if (m_vCoordinates.size() == 1)
      return true;

    return (m_vCoordinates.front() == m_vCoordinates.back());
  }

  bool
  Surface::canClose
  () const noexcept
  {
    if (m_vCoordinates.empty())
      return false;

    if (m_vCoordinates.size() == 1)
      return true;

    return ((m_vCoordinates.front().first == m_vCoordinates.back().first) ||
            (m_vCoordinates.front().second == m_vCoordinates.back().second));
  }
}
