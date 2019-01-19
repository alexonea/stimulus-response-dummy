/*
 *  main.cpp
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

#include <iostream>

#include "SRAgent.h"
#include "Surface.h"
#include "World.h"

int
main
(int argc, char const *argv[])
{
  using namespace SRDummy;

  std::cout << "Welcome to this demo of a stimulus-response agent!\n";

  World w{11, 14};

  {
    Surface s;
    s << Coordinate{0, 13}
      << Coordinate{3, 13}
      << Coordinate{3, 11}
      << Coordinate{0, 11};

    if (!w.addSolidObject(s))
      std::cerr << "[ERROR] Cannot fill solid object!\n";
  }

  {
    Surface s;
    s << Coordinate{7, 13}
      << Coordinate{10, 13}
      << Coordinate{10, 11}
      << Coordinate{7, 11};

    if (!w.addSolidObject(s))
      std::cerr << "[ERROR] Cannot fill solid object!\n";      
  }

  {
    Surface s;
    s << Coordinate{9, 5}
      << Coordinate{9, 7}
      << Coordinate{10, 7}
      << Coordinate{10, 5};
      
    if (!w.addSolidObject(s))
      std::cerr << "[ERROR] Cannot fill solid object!\n";      
  }

  {
    Surface s;
    s << Coordinate{4, 2}
      << Coordinate{6, 2}
      << Coordinate{6, 3}
      << Coordinate{4, 3};

      
    if (!w.addSolidObject(s))
      std::cerr << "[ERROR] Cannot fill solid object!\n";      
  }

  {
    Surface s;
    s << Coordinate{4, 6}
      << Coordinate{6, 6}
      << Coordinate{6, 7}
      << Coordinate{4, 7};
      
    if (!w.addSolidObject(s))
      std::cerr << "[ERROR] Cannot fill solid object!\n";      
  }

  {
    Surface s;
    s << Coordinate{4, 3}
      << Coordinate{4, 6};
      
    if (!w.addSolidObject(s))
      std::cerr << "[ERROR] Cannot fill solid object!\n";      
  }
  
  std::cout << w.toString();

  return 0;
}
