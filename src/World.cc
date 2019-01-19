/*
 *  World.cc
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

#include <sstream>
#include <cstdarg>
#include <algorithm>

namespace SRDummy
{
  World::World
  (std::size_t nRows, std::size_t nCols)
  : m_pImpl{new WorldImpl{nRows, nCols}}
  {}

  World::~World()
  {
    /*
     * We need an empty destructor here, where WorldImpl is a complete type,
     * otherwise the compiler cannot generate a destructor for the World class
     * only based on the declaration, because WorldImpl is an incomplete type
     * in the declaration.
     */
  }

  World::World
  (const World& other)
  : m_pImpl{new WorldImpl{*other.m_pImpl}}
  {}

  World&
  World::operator=
  (const World& other)
  {
    m_pImpl.reset(new WorldImpl{*other.m_pImpl});
  }

  World::World
  (World&& other)
  : m_pImpl{std::move(other.m_pImpl)}
  {}

  World&
  World::operator=
  (World&& other)
  {
    m_pImpl.swap(other.m_pImpl);
  }

  /*
   * Simple implementation of a scan-line filling algorithm. Bugs exist!
   * This implementation only works in limited cases and is in particular
   * sensitive to the surface specification (see also Surface.h).
   *
   * Main idea: 1)  Iterate through all points in surface specification and find
   *                  top-left and bottom-right points (extremes).
   *            2)  Iterate through all the lines in that range and for each
   *                  line collect all edges (pairs of vertices) that intersect
   *                  the line.
   *            3)  Sort the edges by the x-position
   *            4)  For each edge in the sorted container, if it is a vertical
   *                  edge, then get the next one as well and either print or
   *                  do nothing, depending on what has been done in the
   *                  previous interation:
   *            4a) If in the previous iteration, we painted, now we do nothing.
   *            4B) If we did nothing, now we paint. This is in sync with how 
   *                  vertical edges delimit areas of paint from areas of empty
   *                  space.
   */
  bool
  World::addSolidObject
  (const Surface& s)
  {
    WorldImplRef pTemp{new WorldImpl{*m_pImpl}};

    /*
     * If the surface is not conplete or cannot be easily closed, we are not
     * able to fill it. (see Surface.h)
     */
    if (!s.isComplete() && !s.canClose())
      return false;

    /*
     * If there is just one point in the surface, paint it and return success.
     */
    if (s.m_vCoordinates.size() == 1)
    {
      pTemp->m_vCells[pTemp->toPos(s.m_vCoordinates[0])] = WALL;
      m_pImpl.swap(pTemp);
      return true;
    }

    /*
     * Initially define the top-left and bottom-right points as the first and
     * the last of the surface.
     */
    Coordinate topLeft = s.m_vCoordinates.front();
    Coordinate buttomRight = s.m_vCoordinates.back();

    /*
     * Iterate through all coordinates and detect the real top-left and
     * bottom-right coordinates.
     */
    for (const auto& coord : s.m_vCoordinates)
    {
      if (topLeft.first > coord.first ||
          topLeft.second > coord.second)
        topLeft = coord;

      if (buttomRight.first < coord.first ||
          buttomRight.second < coord.second)
        buttomRight = coord;
    }

    using Edge = std::pair<Coordinate, Coordinate>;
    std::vector<Edge> vEdges;

    /*
     * Collect all edges from the surface definition.
     */
    const auto& end = s.m_vCoordinates.end();
    auto last = s.m_vCoordinates.begin();
    for (auto it = std::next(last); it != end; ++it)
    {
      vEdges.push_back(std::make_pair(*last, *it));
      last = it;
    }

    /*
     * For each row in the surface area (between top-left and bottom-right):
     */
    for (std::size_t iRow = topLeft.first; iRow <= buttomRight.first; ++iRow)
    {
      /*
       * Detect edges that intersect the current "scan" line.
       */
      std::vector<Edge> vCrossing;
      for (const auto& e : vEdges)
      {
        if ((e.first.first >= iRow && iRow >= e.second.first) ||
            (e.first.first <= iRow && iRow <= e.second.first ))
          vCrossing.push_back(e);
      }

      /*
       * Sort the found edges by their x-coordinate. This is important, so we
       * process them as they appear from left to right.
       */
      std::sort(vCrossing.begin(), vCrossing.end(),
        [] (const Edge& a, const Edge& b) -> bool
        {
          std::size_t iMinA = std::min(a.first.second, a.second.second);
          std::size_t iMinB = std::min(b.first.second, b.second.second);
          
          if (iMinA == iMinB)
          {
            std::size_t iMaxA = std::max(a.first.second, a.second.second);
            std::size_t iMaxB = std::max(b.first.second, b.second.second);

            return (iMaxA < iMaxB);
          }

          return (iMinA < iMinB);
        }
      );

      /*
       * Start by assuming that we are filling (first vertical edge is where
       * we start drawing).
       *
       * For each of the intersection edges:
       */
      bool bDrawing = true;
      const auto& end = vCrossing.end();
      auto it = vCrossing.begin();
      while (it != end)
      {
        /*
         * If this is a vertical edges (which means alternating drawing and
         * empty spaces based on parity).
         */
        if (it->first.second == it->second.second)
        {
          /*
           * Get the next one as well, if does't exist continue to next line.
           */
          auto next = std::next(it);
          if (next == end)
            break;

          /*
           * Calculate the start and end x-coordinates of "to draw" area on
           * the current line, based on the sorted x-coordinates of the two
           * edges.
           */
          std::size_t iColStart = it->first.second;
          std::size_t iColEnd = 
            std::min(next->first.second, next->second.second);

          if (iColStart == iColEnd)
          {
            it = next;
            continue;
          }

          /* 
           * If the parity indicates drawing (i.e. we are in between two edges
           * where there the is not empty space), draw the line segment.
           */
          if (bDrawing)
          {
            for (std::size_t iCol = iColStart; iCol <= iColEnd; ++iCol)
              pTemp->m_vCells[pTemp->toPos(iRow, iCol)] = WALL;
            
            /*
             * Alternate the parity
             */
            bDrawing = !bDrawing;
          }

          it = next;
        }
        else
        {
          /*
           * If the edge is horizontal, we must draw it indefinitely.
           * First, sort the start and end x-coordinates of the edge.
           */
          std::size_t iColStart = std::min(it->first.second, it->second.second);
          std::size_t iColEnd = std::max(it->first.second, it->second.second);

          for (std::size_t iCol = iColStart; iCol <= iColEnd; ++iCol)
            pTemp->m_vCells[pTemp->toPos(iRow, iCol)] = WALL;

          it = std::next(it);
        }
      }
    }

    m_pImpl.swap(pTemp);
    return true;
  }

  std::string
  World::toString
  () const
  {
    std::stringstream ss;

    const std::size_t nSize = m_pImpl->m_nRows * m_pImpl->m_nCols;

    for (std::size_t iPos = 0; iPos <= m_pImpl->m_nCols; ++iPos)
      ss << "#";

    for (std::size_t iPos = 0; iPos < nSize; ++iPos)
    {
      if (iPos % m_pImpl->m_nCols == 0)
        ss << "#\n#";

      ss << m_pImpl->m_vCells[iPos];
    }

    ss << "#\n#";

    for (std::size_t iPos = 0; iPos <= m_pImpl->m_nCols; ++iPos)
      ss << "#";

    ss << "\n";

    return ss.str();
  }
}
