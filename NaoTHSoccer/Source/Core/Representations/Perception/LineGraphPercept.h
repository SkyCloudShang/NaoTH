/** 
 * @file LineGraphPercept.h
 * @author <a href="mailto:mellmann@informatik.hu-berlin.de">Heinrich Mellmann</a>
 * Declaration of class LineGraphPercept
 */

#ifndef _LineGraphPercept_h_
#define _LineGraphPercept_h_

#include <vector>

#include "Tools/Math/Vector2.h"
#include "Tools/ImageProcessing/Edgel.h"

class LineGraphPercept : public naoth::Printable
{ 
public:

  std::vector<Edgel> edgels;

  virtual void print(std::ostream& stream) const {
  }

};

#endif // _LineGraphPercept_h_

