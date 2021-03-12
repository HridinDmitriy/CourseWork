#pragma once
#include <SFML/Graphics/Transform.hpp>
#include <SFML/System/Clock.hpp>
#include "WindowSize.h"
#include "MotionConstants.h"
using namespace sf;

class SFML_GRAPHICS_API Transformable
{
public:

	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	///
	////////////////////////////////////////////////////////////
	Transformable();

	////////////////////////////////////////////////////////////
	/// \brief Virtual destructor
	///
	////////////////////////////////////////////////////////////
	virtual ~Transformable();

	////////////////////////////////////////////////////////////
	/// \brief set the position of the object
	///
	/// This function completely overwrites the previous position.
	/// See the move function to apply an offset based on the previous position instead.
	/// The default position of a transformable object is (0, 0).
	///
	/// \param x X coordinate of the new position
	/// \param y Y coordinate of the new position
	///
	/// \see move, getPosition
	///
	////////////////////////////////////////////////////////////
	void setPosition(float x, float y);

	////////////////////////////////////////////////////////////
	/// \brief set the position of the object
	///
	/// This function completely overwrites the previous position.
	/// See the move function to apply an offset based on the previous position instead.
	/// The default position of a transformable object is (0, 0).
	///
	/// \param position New position
	///
	/// \see move, getPosition
	///
	////////////////////////////////////////////////////////////
	void setPosition(const Vector2f& position);

	////////////////////////////////////////////////////////////
	/// \brief set the orientation of the object
	///
	/// This function completely overwrites the previous rotation.
	/// See the rotate function to add an angle based on the previous rotation instead.
	/// The default rotation of a transformable object is 0.
	///
	/// \param angle New rotation, in degrees
	///
	/// \see rotate, getRotation
	///
	////////////////////////////////////////////////////////////
	virtual void setRotation(float angle);

	////////////////////////////////////////////////////////////
	/// \brief set the scale factors of the object
	///
	/// This function completely overwrites the previous scale.
	/// See the scale function to add a factor based on the previous scale instead.
	/// The default scale of a transformable object is (1, 1).
	///
	/// \param factorX New horizontal scale factor
	/// \param factorY New vertical scale factor
	///
	/// \see scale, getScale
	///
	////////////////////////////////////////////////////////////
	virtual void setScale(float factorX, float factorY);

	////////////////////////////////////////////////////////////
	/// \brief set the scale factors of the object
	///
	/// This function completely overwrites the previous scale.
	/// See the scale function to add a factor based on the previous scale instead.
	/// The default scale of a transformable object is (1, 1).
	///
	/// \param factors New scale factors
	///
	/// \see scale, getScale
	///
	////////////////////////////////////////////////////////////
	virtual void setScale(const Vector2f& factors);

	////////////////////////////////////////////////////////////
	/// \brief set the local origin of the object
	///
	/// The origin of an object defines the center point for
	/// all transformations (position, scale, rotation).
	/// The coordinates of this point must be relative to the
	/// top-left corner of the object, and ignore all
	/// transformations (position, scale, rotation).
	/// The default origin of a transformable object is (0, 0).
	///
	/// \param x X coordinate of the new origin
	/// \param y Y coordinate of the new origin
	///
	/// \see getOrigin
	///
	////////////////////////////////////////////////////////////
	void setOrigin(float x, float y);

	////////////////////////////////////////////////////////////
	/// \brief set the local origin of the object
	///
	/// The origin of an object defines the center point for
	/// all transformations (position, scale, rotation).
	/// The coordinates of this point must be relative to the
	/// top-left corner of the object, and ignore all
	/// transformations (position, scale, rotation).
	/// The default origin of a transformable object is (0, 0).
	///
	/// \param origin New origin
	///
	/// \see getOrigin
	///
	////////////////////////////////////////////////////////////
	void setOrigin(const Vector2f& origin);

	////////////////////////////////////////////////////////////
	/// \brief get the position of the object
	///
	/// \return Current position
	///
	/// \see setPosition
	///
	////////////////////////////////////////////////////////////
	const Vector2f& getPosition() const;

	////////////////////////////////////////////////////////////
	/// \brief get the orientation of the object
	///
	/// The rotation is always in the range [0, 360].
	///
	/// \return Current rotation, in degrees
	///
	/// \see setRotation
	///
	////////////////////////////////////////////////////////////
	float getRotation() const;

	////////////////////////////////////////////////////////////
	/// \brief get the current scale of the object
	///
	/// \return Current scale factors
	///
	/// \see setScale
	///
	////////////////////////////////////////////////////////////
	const Vector2f& getScale() const;

	////////////////////////////////////////////////////////////
	/// \brief get the local origin of the object
	///
	/// \return Current origin
	///
	/// \see setOrigin
	///
	////////////////////////////////////////////////////////////
	const Vector2f& getOrigin() const;

	////////////////////////////////////////////////////////////
	/// \brief Move the object by a given offset
	///
	/// This function adds to the current position of the object,
	/// unlike setPosition which overwrites it.
	/// Thus, it is equivalent to the following code:
	/// \code
	/// sf::Vector2f pos = object.getPosition();
	/// object.setPosition(pos.x + offsetX, pos.y + offsetY);
	/// \endcode
	///
	/// \param offsetX X offset
	/// \param offsetY Y offset
	///
	/// \see setPosition
	///
	////////////////////////////////////////////////////////////
	virtual void move(float offsetX, float offsetY);

	////////////////////////////////////////////////////////////
	/// \brief Move the object by a given offset
	///
	/// This function adds to the current position of the object,
	/// unlike setPosition which overwrites it.
	/// Thus, it is equivalent to the following code:
	/// \code
	/// object.setPosition(object.getPosition() + offset);
	/// \endcode
	///
	/// \param offset Offset
	///
	/// \see setPosition
	///
	////////////////////////////////////////////////////////////
	virtual void move(const Vector2f& offset);

	virtual void auto_move(float speed, Clock& clock);

	////////////////////////////////////////////////////////////
	/// \brief Rotate the object
	///
	/// This function adds to the current rotation of the object,
	/// unlike setRotation which overwrites it.
	/// Thus, it is equivalent to the following code:
	/// \code
	/// object.setRotation(object.getRotation() + angle);
	/// \endcode
	///
	/// \param angle Angle of rotation, in degrees
	///
	////////////////////////////////////////////////////////////
	virtual void rotate(float angle);

	////////////////////////////////////////////////////////////
	/// \brief Scale the object
	///
	/// This function multiplies the current scale of the object,
	/// unlike setScale which overwrites it.
	/// Thus, it is equivalent to the following code:
	/// \code
	/// sf::Vector2f scale = object.getScale();
	/// object.setScale(scale.x * factorX, scale.y * factorY);
	/// \endcode
	///
	/// \param factorX Horizontal scale factor
	/// \param factorY Vertical scale factor
	///
	/// \see setScale
	///
	////////////////////////////////////////////////////////////
	virtual void scale(float factorX, float factorY);

	////////////////////////////////////////////////////////////
	/// \brief Scale the object
	///
	/// This function multiplies the current scale of the object,
	/// unlike setScale which overwrites it.
	/// Thus, it is equivalent to the following code:
	/// \code
	/// sf::Vector2f scale = object.getScale();
	/// object.setScale(scale.x * factor.x, scale.y * factor.y);
	/// \endcode
	///
	/// \param factor Scale factors
	///
	/// \see setScale
	///
	////////////////////////////////////////////////////////////
	virtual void scale(const Vector2f& factor);

	////////////////////////////////////////////////////////////
	/// \brief get the combined transform of the object
	///
	/// \return Transform combining the position/rotation/scale/origin of the object
	///
	/// \see getInverseTransform
	///
	////////////////////////////////////////////////////////////
	const Transform& getTransform() const;

	////////////////////////////////////////////////////////////
	/// \brief get the inverse of the combined transform of the object
	///
	/// \return Inverse of the combined transformations applied to the object
	///
	/// \see getTransform
	///
	////////////////////////////////////////////////////////////
	const Transform& getInverseTransform() const;

private:

	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	Vector2f          m_origin;                     //!< Origin of translation/rotation/scaling of the object
	Vector2f          m_position;                   //!< Position of the object in the 2D world
	float             m_rotation;                   //!< Orientation of the object, in degrees
	Vector2f          m_scale;                      //!< Scale of the object
	mutable Transform m_transform;                  //!< Combined transformation of the object
	mutable bool      m_transformNeedUpdate;        //!< Does the transform need to be recomputed?
	mutable Transform m_inverseTransform;           //!< Combined transformation of the object
	mutable bool      m_inverseTransformNeedUpdate; //!< Does the transform need to be recomputed?

};

