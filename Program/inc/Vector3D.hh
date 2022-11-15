#ifndef VECTOR3D_HH
#define VECTOR3D_HH

#include "geomVector.hh"
#include <istream>

/*!
 * \file
 * \brief Deklaracja instacji szablonu geom::Vector
 */

 /*!
  * \brief Instacja szablonu geom::Vector<typename,int> dla przestrzeni 3D.
  */
typedef geom::Vector<double,3>  Vector3D;
inline
std::istream& operator>>(std::istream& inputStream, Vector3D& vector3D){
   inputStream >> vector3D[0];
   inputStream >> vector3D[1];
   inputStream >> vector3D[2];
   return inputStream;
}

#endif
