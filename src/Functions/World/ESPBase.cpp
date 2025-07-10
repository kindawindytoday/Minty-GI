#include "ESPBase.h"


// CAUTION: HUGE MESS


inline ImVec4 ESPBase::ColorVecToImVec(std::vector<float> color) {
	return ImVec4(color[0] / 255.f, color[1] / 255.f, color[2] / 255.f, color[3] / 255.f);
}

inline ESPBase::Bounds ESPBase::GetBoundsFromActor(MoleMole::BaseEntity* actor) {
	Unity::Vector3 origin, extent;

	auto gameObject = actor->get_GameObject();
	if (gameObject == nullptr) return { {0,0,0}, {0,0,0} };

	try {
		auto bounds = Offsets::StageManager::GetBounds(gameObject);
		if (bounds.center.zero() == true) return { {0,0,0}, {0,0,0} };

		return { bounds.center, bounds.extent };
	}
	catch (...) {
		return { {0,0,0}, {0,0,0} };
	}
}

ImVec2 ClampToScreen(ImVec2 point) {
	float margin = 30.f; // Min possible distance from screen border

	auto Size = ImGui::GetMainViewport()->Size;
	ImVec2 limitedPosition = point;

	if (limitedPosition.x <= margin) {
		limitedPosition.x = margin;
	}

	if (limitedPosition.x >= Size.x - margin) {
		limitedPosition.x = Size.x - margin;
	}

	if (limitedPosition.y <= margin) {
		limitedPosition.y = margin;
	}

	if (limitedPosition.y >= Size.y - margin) {
		limitedPosition.y = Size.y - margin;
	}

	return { limitedPosition.x, limitedPosition.y };
}

ImVec2 ESPBase::WorldToScreen(Unity::Vector3 world, Unity::Camera* camera) {
	if (camera == nullptr) {
		return { 0, 0 };
	}

	auto screenPos = Offsets::Camera::WorldToScreenPoint(camera, world);
	if (screenPos.zero() == true) {
		return { 0, 0 };
	}

	auto screenHeight = Offsets::Screen::get_height();
	if (screenHeight == 0) {
		return { 0, 0 };
	}

	screenPos.y = ImGui::GetMainViewport()->Size.y - screenPos.y;
	if (screenPos.z < 1) {
		screenPos.x -= ImGui::GetMainViewport()->Size.x;
		return { -screenPos.x, ImGui::GetMainViewport()->Size.y };
	}

	return { screenPos.x, screenPos.y };
}

Unity::Vector3 ESPBase::Bounds::p_min() {
	return this->center - this->extent;
}

Unity::Vector3 ESPBase::Bounds::p_max() {
	return this->center + this->extent;
}

bool isPointInQuad(const ImVec2& point, const ImVec2& A, const ImVec2& B, const ImVec2& C, const ImVec2& D) {
	auto cross = [](const ImVec2& p1, const ImVec2& p2, const ImVec2& p3) {
		return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
		};

	float crossAB = cross(A, B, point);
	float crossBC = cross(B, C, point);
	float crossCD = cross(C, D, point);
	float crossDA = cross(D, A, point);

	return (crossAB >= 0 && crossBC >= 0 && crossCD >= 0 && crossDA >= 0) ||
		(crossAB <= 0 && crossBC <= 0 && crossCD <= 0 && crossDA <= 0);
}

void DrawBox(ESPBase::Bounds bounds, Unity::Camera* camera, std::vector<float> boxColor, std::vector<float> borderColor, std::function<void(MoleMole::BaseEntity*)> onClickCallback = 0, MoleMole::BaseEntity* actor = 0) {
	// Coords
	ImVec2 A = ESPBase::WorldToScreen({ bounds.center.x - bounds.extent.x, bounds.center.y + bounds.extent.y, bounds.center.z + bounds.extent.z }, camera);
	ImVec2 B = ESPBase::WorldToScreen({ bounds.center.x + bounds.extent.x, bounds.center.y + bounds.extent.y, bounds.center.z + bounds.extent.z }, camera);
	ImVec2 C = ESPBase::WorldToScreen({ bounds.center.x - bounds.extent.x, bounds.center.y + bounds.extent.y, bounds.center.z - bounds.extent.z }, camera);
	ImVec2 D = ESPBase::WorldToScreen({ bounds.center.x + bounds.extent.x, bounds.center.y + bounds.extent.y, bounds.center.z - bounds.extent.z }, camera);

	ImVec2 X = ESPBase::WorldToScreen({ bounds.center.x - bounds.extent.x, bounds.center.y - bounds.extent.y, bounds.center.z + bounds.extent.z }, camera);
	ImVec2 Y = ESPBase::WorldToScreen({ bounds.center.x + bounds.extent.x, bounds.center.y - bounds.extent.y, bounds.center.z + bounds.extent.z }, camera);
	ImVec2 W = ESPBase::WorldToScreen({ bounds.center.x - bounds.extent.x, bounds.center.y - bounds.extent.y, bounds.center.z - bounds.extent.z }, camera);
	ImVec2 Z = ESPBase::WorldToScreen({ bounds.center.x + bounds.extent.x, bounds.center.y - bounds.extent.y, bounds.center.z - bounds.extent.z }, camera);

	POINT point;
	GetCursorPos(&point);

	point.x /= ((float)GetSystemMetrics(SM_CYSCREEN) / (float)Offsets::Screen::get_height());
	point.y /= ((float)GetSystemMetrics(SM_CYSCREEN) / (float)Offsets::Screen::get_height());

	auto boxColor2 = boxColor;
	auto borderColor2 = borderColor;
	if (onClickCallback != 0) {
		//printf("omw!\n");
		if (isPointInQuad({ (float)point.x, (float)point.y }, C, A, B, D) ||
			isPointInQuad({ (float)point.x, (float)point.y }, W, X, Y, Z) ||
			isPointInQuad({ (float)point.x, (float)point.y }, W, C, A, X) ||
			isPointInQuad({ (float)point.x, (float)point.y }, Z, D, B, Y) ||
			isPointInQuad({ (float)point.x, (float)point.y }, W, C, D, Z) ||
			isPointInQuad({ (float)point.x, (float)point.y }, X, A, B, Y)) {
			
			//printf("hovering!\n");
			boxColor2[0] *= 0.8; boxColor2[1] *= 0.8; boxColor2[2] *= 0.8;
			borderColor2[0] *= 0.8; borderColor2[1] *= 0.8; borderColor2[2] *= 0.8;
			if ((GetKeyState(VK_RBUTTON) & 0x8000) != 0) {
				std::thread(onClickCallback, actor).detach();
			}
		}
	}

	auto list = ImGui::GetBackgroundDrawList();

	auto border = ImColor(ESPBase::ColorVecToImVec(borderColor2));
	auto box = ImColor(ESPBase::ColorVecToImVec(boxColor2));

	// Borders
	list->AddLine(A, B, border);
	list->AddLine(A, C, border);
	list->AddLine(D, B, border);
	list->AddLine(D, C, border);

	list->AddLine(X, Y, border);
	list->AddLine(X, W, border);
	list->AddLine(Z, Y, border);
	list->AddLine(Z, W, border);

	list->AddLine(X, A, border);
	list->AddLine(Y, B, border);
	list->AddLine(W, C, border);
	list->AddLine(Z, D, border);
	// Sides 

	list->AddQuadFilled(C, A, B, D, box);
	list->AddQuadFilled(W, X, Y, Z, box);
	list->AddQuadFilled(W, C, A, X, box);
	list->AddQuadFilled(Z, D, B, Y, box);
	list->AddQuadFilled(W, C, D, Z, box);
	list->AddQuadFilled(X, A, B, Y, box);
}

/*

   A  +-------+  B
	 /|      /|
 C  +-------+D|
	|X|+-0--|-+ Y
	|/      |/
  W +-------+ Z

  0 - center

*/


ImVec2 RotatePoint(const ImVec2& point, const ImVec2& pivot, float angle)
{
	auto angleRadians = angle * 3.1415956535 / 180;
	ImVec2 translated = point - pivot;

	float sinAngle = sinf(angleRadians);
	float cosAngle = cosf(angleRadians);

	float x = translated.x * cosAngle - translated.y * sinAngle;
	float y = translated.x * sinAngle + translated.y * cosAngle;

	return ImVec2(x, y) + pivot;
}

/*
	   A
	  /\
	 /X \
	/ /\ \
   /_/  \_\
 C	  	    B

*/

void DrawArrow(float degree, std::vector<float> color) {
	auto& io = ImGui::GetIO();

	// Defines
	ImVec2 center = { io.DisplaySize.x / 2, io.DisplaySize.y / 2 };
	float distanceFromCenter = 75.f; // distance from center to O
	float arrowHeight = 30.f;
	float arrowWidth = 20.f;

	ImVec2 A = { center.x, center.y + distanceFromCenter + arrowHeight };
	ImVec2 B = { center.x + arrowWidth / 2, center.y + distanceFromCenter };
	ImVec2 C = { center.x - arrowWidth / 2, center.y + distanceFromCenter };
	//ImVec2 X = { center.x, center.y + distanceFromCenter + (arrowHeight / 2) };
	//ImVec2 points[4] = { A,B,C,X };

	// Filling
	ImGui::GetBackgroundDrawList()->AddTriangleFilled(RotatePoint(A, center, degree), RotatePoint(B, center, degree), RotatePoint(C, center, degree), ImColor(ESPBase::ColorVecToImVec({ color[0], color[1], color[2], color[3] / 2 })));
	//ImGui::GetBackgroundDrawList()->AddConvexPolyFilled(points, 4, ImColor(ESPBase::ColorVecToImVec(color)));

	// Border
	ImGui::GetBackgroundDrawList()->AddTriangle(RotatePoint(A, center, degree), RotatePoint(B, center, degree), RotatePoint(C, center, degree), ImColor(ESPBase::ColorVecToImVec(color)));
}
//
// GetBoundsFromActor
// WorldToScreen
// WorldToScreen
//
void ESPBase::DrawActor(MoleMole::BaseEntity* actor, MoleMole::BaseEntity* avatar, Unity::Camera* camera, ESPBase::DrawMode drawmode, ESPBase::PointMode pointmode, std::vector<float> borderColor, std::vector<float> boxColor, std::function<void(MoleMole::BaseEntity*)> onClickCallback) {
	switch (drawmode) {
	case ESPBase::DrawMode::Box: {
		auto& io = ImGui::GetIO();
		ImVec2 center = { io.DisplaySize.x / 2, io.DisplaySize.y / 2 };

		auto bounds = GetBoundsFromActor(actor);
		if (bounds.center.zero()) return;

		auto centerToScreen = WorldToScreen(actor->get_GameObject()->GetTransform()->getPosition(), camera);
		//auto minToScreen = WorldToScreen(bounds.p_min(), camera);

		if (centerToScreen.x == 0 && centerToScreen.y == 0);

		ImVec2 p_min = ClampToScreen(centerToScreen);

		if (centerToScreen.x <= 0 || centerToScreen.x >= io.DisplaySize.x || centerToScreen.y <= 0 || centerToScreen.y >= io.DisplaySize.y) {

		}
		else {
			DrawBox(bounds, camera, boxColor, borderColor, onClickCallback, actor);
		}

		if (pointmode == ESPBase::PointMode::Line) {
			ImGui::GetBackgroundDrawList()->AddLine(center, { ClampToScreen(centerToScreen).x, ClampToScreen(centerToScreen).y }, ImColor(ColorVecToImVec(borderColor)));
		}

		auto avatarPos = avatar->getPosition();
		if (avatarPos.zero() == true) return;

		auto targetPos = actor->getPosition();
		if (targetPos.zero() == true) return;

		float distance = avatarPos.distance(targetPos);
		std::string text = std::to_string(distance) + " | " + std::to_string(actor->type()) + " | " + "actor->name()";

		ImGui::GetBackgroundDrawList()->AddText(p_min, ImColor(ColorVecToImVec({ 255,255,255,100 })), text.c_str());
	}
	break;
	}
}