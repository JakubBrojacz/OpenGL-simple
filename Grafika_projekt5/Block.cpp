#include "Block.h"

#include "HousePos.h"
#include "HouseParams.h"

Block::Block()
{
	HouseParams params{};
	params.width = 3.7;
	params.height = 3;
	params.depth = 1;
	params.window_horizontal = 6;
	params.window_vertical = 4;
	params.window_width = 0.2;
	params.window_height = 0.4;
	params.door_width = 0.3;
	params.door_height = 0.6;
	params.door_offset = 0;
	params.window_bot = false;
	params.smaller_window_over_door;
	params.window_type = 1;
	params.x = -1.5;
	params.z = -0.5;
	params.y_rot = 0;

	houses[0] = House(params);

	params.width = 2.4;
	params.height = 3;
	params.depth = 1;
	params.window_horizontal = 6;
	params.window_vertical = 4;
	params.window_width = 0.2;
	params.window_height = 0.4;
	params.door_width = 0.3;
	params.door_height = 0.6;
	params.door_offset = 0;
	params.window_bot = false;
	params.smaller_window_over_door;
	params.window_type = 1;
	params.x = -5.6;
	params.z = -0.5;
	params.y_rot = 0;

	houses[1] = House(params);

	params.width = 3.6;
	params.height = 3;
	params.depth = 1;
	params.window_horizontal = 6;
	params.window_vertical = 4;
	params.window_width = 0.2;
	params.window_height = 0.4;
	params.door_width = 0.3;
	params.door_height = 0.6;
	params.door_offset = 0;
	params.window_bot = false;
	params.smaller_window_over_door;
	params.window_type = 1;
	params.x = -11;
	params.z = -0.5;
	params.y_rot = 0;

	houses[2] = House(params);

	params.width = 2.6;
	params.height = 3;
	params.depth = 1;
	params.window_horizontal = 6;
	params.window_vertical = 4;
	params.window_width = 0.2;
	params.window_height = 0.4;
	params.door_width = 0.3;
	params.door_height = 0.6;
	params.door_offset = 0;
	params.window_bot = false;
	params.smaller_window_over_door;
	params.window_type = 1;
	params.x = -10.5;
	params.z = 2.5;
	params.y_rot = glm::pi<float>()/2;

	houses[3] = House(params);

	params.width = 2.2;
	params.height = 3;
	params.depth = 1;
	params.window_horizontal = 6;
	params.window_vertical = 4;
	params.window_width = 0.2;
	params.window_height = 0.4;
	params.door_width = 0.3;
	params.door_height = 0.6;
	params.door_offset = 0;
	params.window_bot = false;
	params.smaller_window_over_door;
	params.window_type = 1;
	params.x = -10.5;
	params.z = 5.2;
	params.y_rot = glm::pi<float>() / 2;

	houses[4] = House(params);

	params.width = 4.1;
	params.height = 3;
	params.depth = 1;
	params.window_horizontal = 6;
	params.window_vertical = 4;
	params.window_width = 0.2;
	params.window_height = 0.4;
	params.door_width = 0.3;
	params.door_height = 0.6;
	params.door_offset = 0;
	params.window_bot = false;
	params.smaller_window_over_door;
	params.window_type = 1;
	params.x = -7.4;
	params.z = 6.4;
	params.y_rot = glm::pi<float>();

	houses[5] = House(params);

	params.width = 2.5;
	params.height = 3;
	params.depth = 1;
	params.window_horizontal = 6;
	params.window_vertical = 4;
	params.window_width = 0.2;
	params.window_height = 0.4;
	params.door_width = 0.3;
	params.door_height = 0.6;
	params.door_offset = 0;
	params.window_bot = false;
	params.smaller_window_over_door;
	params.window_type = 1;
	params.x = -2.8;
	params.z = 6.4;
	params.y_rot = glm::pi<float>();

	houses[6] = House(params);

	params.width = 4.5;
	params.height = 3;
	params.depth = 1;
	params.window_horizontal = 6;
	params.window_vertical = 4;
	params.window_width = 0.2;
	params.window_height = 0.4;
	params.door_width = 0.3;
	params.door_height = 0.6;
	params.door_offset = 0;
	params.window_bot = false;
	params.smaller_window_over_door;
	params.window_type = 1;
	params.x = 2;
	params.z = 6.4;
	params.y_rot = glm::pi<float>();

	houses[7] = House(params);

	params.width = 2.2;
	params.height = 3;
	params.depth = 1;
	params.window_horizontal = 6;
	params.window_vertical = 4;
	params.window_width = 0.2;
	params.window_height = 0.4;
	params.door_width = 0.3;
	params.door_height = 0.6;
	params.door_offset = 0;
	params.window_bot = false;
	params.smaller_window_over_door;
	params.window_type = 1;
	params.x = 1.5;
	params.z = 3.6;
	params.y_rot = 3*glm::pi<float>()/2;

	houses[8] = House(params);

	params.width = 2.8;
	params.height = 3;
	params.depth = 1;
	params.window_horizontal = 6;
	params.window_vertical = 4;
	params.window_width = 0.2;
	params.window_height = 0.4;
	params.door_width = 0.3;
	params.door_height = 0.6;
	params.door_offset = 0;
	params.window_bot = false;
	params.smaller_window_over_door;
	params.window_type = 1;
	params.x = 1.5;
	params.z = 0.3;
	params.y_rot = 3 * glm::pi<float>() / 2;

	houses[9] = House(params);

	params.width = 2.8;
	params.height = 3;
	params.depth = 1.8;
	params.window_horizontal = 6;
	params.window_vertical = 4;
	params.window_width = 0.2;
	params.window_height = 0.4;
	params.door_width = 0.3;
	params.door_height = 0.6;
	params.door_offset = 0;
	params.window_bot = false;
	params.smaller_window_over_door;
	params.window_type = 1;
	params.x = -8.3;
	params.z = 2.2;
	params.y_rot = 3 * glm::pi<float>() / 2;

	houses[10] = House(params);

	params.width = 3;
	params.height = 3;
	params.depth = 1.1;
	params.window_horizontal = 6;
	params.window_vertical = 4;
	params.window_width = 0.2;
	params.window_height = 0.4;
	params.door_width = 0.3;
	params.door_height = 0.6;
	params.door_offset = 0;
	params.window_bot = false;
	params.smaller_window_over_door;
	params.window_type = 1;
	params.x = -5.5;
	params.z = 0.6;
	params.y_rot = glm::pi<float>();

	houses[11] = House(params);

	params.width = 4;
	params.height = 3;
	params.depth = 1.8;
	params.window_horizontal = 6;
	params.window_vertical = 4;
	params.window_width = 0.2;
	params.window_height = 0.4;
	params.door_width = 0.3;
	params.door_height = 0.6;
	params.door_offset = 0;
	params.window_bot = false;
	params.smaller_window_over_door;
	params.window_type = 1;
	params.x = -6;
	params.z = 4.8;
	params.y_rot = 0;

	houses[12] = House(params);

	params.width = 4.1;
	params.height = 3;
	params.depth = 1;
	params.window_horizontal = 6;
	params.window_vertical = 4;
	params.window_width = 0.2;
	params.window_height = 0.4;
	params.door_width = 0.3;
	params.door_height = 0.6;
	params.door_offset = 0;
	params.window_bot = false;
	params.smaller_window_over_door;
	params.window_type = 1;
	params.x = -0.1;
	params.z = 4.9;
	params.y_rot = glm::pi<float>() / 2;

	houses[13] = House(params);

	params.width = 1.5;
	params.height = 3;
	params.depth = 1.5;
	params.window_horizontal = 6;
	params.window_vertical = 4;
	params.window_width = 0.2;
	params.window_height = 0.4;
	params.door_width = 0.3;
	params.door_height = 0.6;
	params.door_offset = 0;
	params.window_bot = false;
	params.smaller_window_over_door;
	params.window_type = 1;
	params.x = -2.5;
	params.z = 0.6;
	params.y_rot = glm::pi<float>();

	houses[14] = House(params);
}

void Block::Draw(glm::mat4& model, Shader& shader)
{
	glm::mat4 model_tmp = glm::translate(model, glm::vec3{ 0,0,0 });
	for (int i = 0; i < 15; i++)
	{
		auto model_tmp1 = glm::translate(model_tmp, glm::vec3{ 0,0,0 });
		model_tmp1 = glm::translate(model_tmp1, glm::vec3{ houses[i].params.x, houses[i].params.y, houses[i].params.z });
		model_tmp1 = glm::rotate(model_tmp1, houses[i].params.y_rot,  glm::vec3{ 0,1, 0});
		houses[i].Draw(model_tmp1, shader);
	}
}

Block::~Block()
{
}



