/*
 *  WorldImpl.cc
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

#include "WorldImpl.h"

namespace SRDummy
{
  WorldImpl::WorldImpl
  (std::size_t nRows, std::size_t nCols)
  : m_nRows{nRows}
  , m_nCols{nCols}
  , m_vCells{nRows * nCols, EMPTY}
  {}

  WorldImpl::WorldImpl
  (const WorldImpl& other)
  : m_nRows{other.m_nRows}
  , m_nCols{other.m_nCols}
  , m_vCells{other.m_vCells}
  {}

  WorldImpl&
  WorldImpl::operator=
  (const WorldImpl& other)
  {
    m_nRows   = other.m_nRows;
    m_nCols   = other.m_nCols;
    m_vCells  = other.m_vCells;
  }

  WorldImpl::WorldImpl
  (WorldImpl&& other) noexcept
  : m_nRows{other.m_nRows}
  , m_nCols{other.m_nCols}
  , m_vCells{std::move(other.m_vCells)}
  {}

  WorldImpl&
  WorldImpl::operator=
  (WorldImpl&& other) noexcept
  {
    swap(other);
  }

  void
  WorldImpl::swap
  (WorldImpl& other) noexcept
  {
    m_nRows = other.m_nRows;
    m_nCols = other.m_nCols;
    m_vCells.swap(other.m_vCells);
  }
}
