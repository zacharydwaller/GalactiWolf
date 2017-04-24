#ifndef UTILS_H_
#define UTILS_H_

#include <OgreMath.h>
#include <OgreVector3.h>

namespace Utils
{
    static float degToRad = 0.0174533f;
    static float radToDeg = 57.295779f;

    inline float Clamp(float value, float lower, float upper)
    {
        if (value > upper)
            return upper;
        if (value < lower)
            return lower;
        return value;
    }

    inline float MakeAnglePosNeg(float angle)
    {
        while (angle > 180)
            angle -= 180;
        while (angle < -180)
            angle += 180;
        return angle;
    }

    inline float FixAngle(float angle)
    {
        while (angle > 360)
            angle -= 360;
        while (angle < 0)
            angle += 360;

        return angle;
    }

    inline float DifferenceBetweenAngles(float angle1, float angle2)
    {
        return MakeAnglePosNeg(angle1 - angle2);
    }

	inline Ogre::Vector3 lerp(Ogre::Vector3 start, Ogre::Vector3 end, float t)
	{
		return ((1 - t) * start) + (t * end);
	}
} /* namespace Utils */

#endif /* UTILS_H_ */