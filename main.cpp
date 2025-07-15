#include <raylib.h>
#include <string>
#include <sstream>
#include <cstdio>

#include "graph.hpp"

int main() {
	Viewport vp = Viewport(800, 800);

	// Anti-aliasing
	SetConfigFlags(FLAG_MSAA_4X_HINT); 
	vp.init();

	Vec2 p1 = Vec2(1, 1);
	Vec2 p2 = Vec2(1, -1);
	Vec2 p3 = Vec2(-1, 1);
	Vec2 p4 = Vec2(-1, -1);

	std::stringstream coordinates;
	Vec2 mouse_screen_pos = Vec2(0, 0);
	Vec2 mouse_pos = Vec2(0, 0);
	SetTargetFPS(60);


	while (!WindowShouldClose()) {
		if (IsKeyDown(KEY_LEFT)) {
			vp.center.x -= 0.1;
		}
		if (IsKeyDown(KEY_RIGHT)) {
			vp.center.x += 0.1;
		}
		if (IsKeyDown(KEY_UP)) {
			vp.center.y += 0.1;
		}
		if (IsKeyDown(KEY_DOWN)) {
			vp.center.y -= 0.1;
		}
		if (IsKeyDown(KEY_PAGE_UP)) {
			vp.resolution += 5;
		}
		if (IsKeyDown(KEY_PAGE_DOWN)) {
			vp.resolution -= 5;
		}

		if (IsKeyPressed(KEY_SPACE)) {
				printf("%f, %f, %f, %f\n", vp.left_border(), vp.right_border(), vp.top_border(), vp.bottom_border());
		}

		mouse_screen_pos.x = GetMouseX();
		mouse_screen_pos.y = GetMouseY();

		mouse_pos = vp.screen_to_coord(mouse_screen_pos);

		coordinates.clear();
		coordinates.str("");
		coordinates << "(" << mouse_pos.x << ", " << mouse_pos.y << ")";

		BeginDrawing();
		
		ClearBackground(BLACK);
		vp.draw_axes();
		DrawFPS(0, 0);
		//DrawCircle(origin_screen.x, origin_screen.y, 10, RAYWHITE);
		vp.draw_point(p1, 5, RED);
		vp.draw_point(p2, 5, GREEN);
		vp.draw_point(p3, 5, BLUE);
		vp.draw_point(p4, 5, YELLOW);

		DrawText(coordinates.str().c_str(), mouse_screen_pos.x, mouse_screen_pos.y - 20, 20, RAYWHITE);
		
		EndDrawing();
	}

	return 0;
}
