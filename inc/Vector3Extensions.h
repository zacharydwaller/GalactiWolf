#ifndef VECTOR_3_EXTENSIONS
#define VECTOR_3_EXTENSIONS

#include <OgreVector3.h>

namespace Vector3
{
	using Ogre::Vector3;
	inline Vector3 lerp(Vector3 start, Vector3 end, float t)
	{
		return ((1 - t) * start) + (t * end);
	}
}

#endif /* #ifndef VECTOR_3_EXTENSIONS */