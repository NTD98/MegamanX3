#pragma once
namespace Define
{
	const float PLAYER_MAX_JUMP_VELOCITY = 350.0f; //van toc nhay lon nhat
	const float PLAYER_MIN_JUMP_VELOCITY = -350.0f; //van toc nhay thap nhat
	const float PLAYER_MAX_DASHING_SPEED = 800.0f; //van toc luot lon nhat
	const float PLAYER_MAX_RUNNING_SPEED = 350.0f; //toc do chay nhanh nhat cua player
	const float PLAYER_BOTTOM_RANGE_FALLING = 6.0f; // do dai va cham voi bottom neu nhu va cham bottom nho hon thi player se bi roi xuong
	const float ELEVATOR_POSITION_STOP = 700.0f;
	const float ELEVATOR_UP_VELOCITY = -70.0f;
}
namespace GunnerDefine {
	const float BULLET_SPEED_X_1 = 70.0f;
	const float BULLET_SPEED_Y_1 = 100.0f;
	const float BULLET_SPEED_X_2 = 150.0f;
	const float BULLET_SPEED_Y_2 = 50.0f;
	const float BULLET_ACCELERATOR_Y = 3.0f;
	const float ACCELERATOR_Y = 10.0f;
	const float JUMP_SPEED_Y = 200;
	const float JUMP_SPEED_X = 50;
}
namespace GenjiboDefine {
	const float SPEED_X = 150.0f;
	const float SPEED_Y = 150.0f;
}
namespace HelitDefine {
	const float SPEED_Y = 50.0f;
	const float BULLET_SPEED_X = 150.0f;
	const float BULLET_SPEED_Y = 40.0f;
	const float BULLET_ACCELERATOR_Y = 3.0f;
}
namespace HornetDefine {
	const float SPEED_X = 100.0f;
	const float SPEED_Y = 50.0f;
}
namespace ChildHornetDefine {
	const float TIME_DELAY = 2.0f;
}