#pragma once

#include "Display.h"
#include "Event.h"
#include "Transform.h"

#include <glm/glm.hpp>

/// <summary>
/// User interface element to control display-based positioning.
/// </summary>
class UIElement : public EventListener {
public:

	/// <summary>
	/// User interface element
	/// </summary>
	/// <param name="disp">Display to use. (Main display if null)</param>
	UIElement(Display* disp = nullptr);

	/// <summary>
	/// Element draw function prototype
	/// </summary>
	virtual void draw() {};

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

private:

	void onEvent(Event*) override;

	glm::vec2 relPos = glm::vec2(0, 0);
	glm::vec2 absPos = glm::vec2(0, 0);
	glm::vec2 relSize = glm::vec2(0, 0);
	glm::vec2 absSize = glm::vec2(1, 1);
	Transform trans;

};