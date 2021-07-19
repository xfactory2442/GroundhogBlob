#pragma once
class SceneManager
{
public:
	enum class Scene {
		Training,
		Quests,
		Travel,
		Log,
		ResetInfo,
		Options
	};

	void ChangeScene(Scene scene_);
	void ChangeScene(int index);
	Scene GetScene();

private:
	Scene scene = Scene::Training;
};

