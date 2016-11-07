#ifndef CAMERA_HPP_INCLUDED
#define CAMERA_HPP_INCLUDED

#include "GameEngine.hpp"
#include "ResourceManager.hpp"
#include "Object.hpp"

enum class CameraType
{
	GAMEPLAY,
	MINIMAP
};

class Camera
{
	public:
		sf::View view;

		Camera()
		{

		}

		Camera(const sf::FloatRect& rect, CameraType cameratype)
			: Camera()
		{
			Init(rect, cameratype);
		}

		void Init(const sf::FloatRect& rect, CameraType cameratype)
		{
			if(cameratype == CameraType::GAMEPLAY)
			{
				zoom_min = resources->GetVariable("camera_zoom_min");
				zoom_max = resources->GetVariable("camera_zoom_max");
				zoom_default = resources->GetVariable("camera_zoom_default");
				zoom_speed = resources->GetVariable("camera_zoom_speed");
			}
			else if(cameratype == CameraType::MINIMAP)
			{
				zoom_min = resources->GetVariable("minimap_zoom_min");
				zoom_max = resources->GetVariable("minimap_zoom_max");
				zoom_default = resources->GetVariable("minimap_zoom_default");
				zoom_speed = resources->GetVariable("minimap_zoom_speed");
			}

			centershift = resources->GetVariable("camera_vertical_shift");

			defaultrect = rect;


			ResetZoom();
		}

		void ResetZoom()
		{
			view.reset(defaultrect);
			view.zoom(zoom_default);
		}

		void Zoom(float value) // +/- 1 from events
		{
			float zoom = 1.0f - value * zoom_speed;
			if(zoom >= 1.0f)
			{
				if(view.getSize().x * zoom < defaultrect.width * zoom_max)
					view.zoom(zoom);
			}
			else
			{
				if(view.getSize().x * zoom > defaultrect.width * zoom_min)
					view.zoom(zoom);
			}
		}

		void FollowObject(bool enable, Object* obj = nullptr)
		{
			follow = enable;

			follow_object = follow ? obj : nullptr;
		}

		void SetRotate(bool enable) //require correct follow object
		{
			rotate = enable;

			if( !rotate)
				view.setRotation(0.0f);
		}

		void Update()
		{
			if(follow && follow_object)
			{
				sf::Vector2f pos = follow_object->GetPosition();
				pos.y -= centershift;
				view.setCenter(pos);
			}

			if(rotate)
			{
				view.setRotation(follow_object->sprite.getRotation() + 90.0f);
			}

			if(shaketimer > fpscounter.GetTime())
			{
				view.move(rand()%40-20, rand()%40-20);
			}
		}

		bool IsFollowing()
		{
			return follow;
		}

		void AddShakingEffect(int length) //length in ms
		{
			shaketimer = fpscounter.GetTime() + length;
		}

	protected:
		sf::FloatRect defaultrect;
		float zoom_max;
		float zoom_min;
		float zoom_default;
		float zoom_speed;

		float centershift;

		bool follow = false;
		bool rotate = false;
		Object* follow_object = nullptr;

		int shaketimer = 0;
};



#endif
