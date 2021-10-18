#pragma once

#include "Display.h"
#include "Event.h"
#include "Transform.h"

#include <glm/glm.hpp>
#include <vector>

/// <summary>
/// User interface element to control display-based positioning.
/// </summary>
class UIElement : public EventListener {
public:

	/// <summary>
	/// Origin position of image
	/// </summary>
	enum class ORIGIN {
		CENTER, TOP, BOTTOM, RIGHT, LEFT,
		TOPRIGHT, BOTTOMRIGHT, TOPLEFT, BOTTOMLEFT,
		MAX_ORIGINS
	};

	/// <summary>
	/// User interface element
	/// </summary>
	/// <param name="evtM">EvtManager to use. (Main display if null)</param>
	UIElement(EventManager* evtM = nullptr);

	/// <summary>
	/// Set relative or absolute position. (0,0) is center.
	/// </summary>
	/// <param name="pos">Position vector</param>
	/// <param name="rel">Relative positioning option</param>
	void setPos(const glm::vec2& pos, bool rel = false);
	
	/// <summary>
	/// Set relative or absolute size. 
	/// </summary>
	/// <param name="size">Size vector</param>
	/// <param name="rel">Relative scaling option</param>
	void setSize(const glm::vec2& size, bool rel = false);

	/// <summary>
	/// Set rotation.
	/// </summary>
	/// <param name="rad">Radians to rotate by.</param>
	void setRot(float rad);

	/// <summary>
	/// Get relative or absolute position.
	/// </summary>
	/// <param name="rel">Relative position option.</param>
	/// <returns>Position vector</returns>
	glm::vec2 getPos(bool rel = false);

	/// <summary>
	/// Get relative or absolute size.
	/// </summary>
	/// <param name="rel"></param>
	/// <returns></returns>
	glm::vec2 getSize(bool rel = false);

	/// <summary>
	/// Get rotation in radians.
	/// </summary>
	/// <returns>Rotation in radians.</returns>
	float getRot();

	/// <summary>
	/// Get compiled transform matrix.
	/// </summary>
	/// <returns></returns>
	glm::mat4 getMatrix();

	/// <summary>
	/// Check if this element collides with a relative point.
	/// </summary>
	/// <param name="pt">Relative collision point</param>
	/// <returns>True if collides, otherwise false</returns>
	bool collides(glm::vec2 pt);

	/// <summary>
	/// Check if two elements collide.
	/// </summary>
	/// <param name="el">Other element</param>
	/// <returns>True if collides, otherwise false</returns>
	bool collides(UIElement& el);

	/// <summary>
	/// Get origin position of image
	/// </summary>
	/// <returns>Origin enum</returns>
	ORIGIN getOrigin();

	/// <summary>
	/// Set origin position of image
	/// </summary>
	/// <param name=""></param>
	void setOrigin(ORIGIN);

	struct Vertex {
		glm::vec3 position;
		glm::vec2 texCoord;
	};

protected:

	/// <summary>
	/// Get origin offset for element vertices
	/// </summary>
	/// <param name="origin">Assoc. origin</param>
	/// <returns>Offset vector</returns>
	static glm::vec3 getOriginOffset(ORIGIN);

	static const std::vector<Vertex>& getVertices();

	static const std::vector<unsigned int>& getIndices();

	void onEvent(Event*) override;

	/// <summary>
	/// Origin anchor point of UI element
	/// </summary>
	ORIGIN origin = ORIGIN::CENTER;

private:
	
	glm::vec2 relPos = glm::vec2(0, 0);
	glm::vec2 absPos = glm::vec2(0, 0);
	glm::vec2 relSize = glm::vec2(0, 0);
	glm::vec2 absSize = glm::vec2(0, 0);
	Transform trans;

	/// <summary>
	/// For rectangle-defining points, get side-axis with projected intervals respectfully.
	/// </summary>
	/// <param name="pts">Defining points</param>
	/// <param name="axis">Array of side-axis</param>
	/// <param name="interval">Array of intervals</param>
	static void getAxisAndIntervals(glm::vec2 pts[4], glm::vec2 axis[2], glm::vec2 interval[2]);

	/// <summary>
	/// Get transformed points.
	/// </summary>
	/// <param name="pts">Array of points (bottom-left, bottom-right, top-left, top-right)</param>
	void getTransPts(glm::vec2 pts[4]);

	/// <summary>
	/// Determine if two intervals overlap.
	/// </summary>
	/// <param name="int1">First interval (min,max)</param>
	/// <param name="int2">Second interval (min,max)</param>
	/// <returns>True if overlap, otherwise false</returns>
	static bool isIntervalOverlap(glm::vec2 int1, glm::vec2 int2);

};