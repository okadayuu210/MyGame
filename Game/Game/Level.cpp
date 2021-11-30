#include "stdafx.h"
#include "Level.h"

#include "RedButton.h"
#include "GreenButton.h"
#include "BlueButton.h"
#include "Door.h"
#include "Stage.h"

Level::Level()
{
	//レベルを構築する。
	m_levelRender.Init("Assets/modelData/Stage.tkl", [&](LevelObjectData& objData)
		{
			//↓3dsMaxの時の名前
			if (objData.ForwardMatchName(L"RedButton") == true)
			{
				RedButton* redButton = NewGO<RedButton>(0, "redButton");
				redButton->SetPosition(objData.position);
				redButton->SetScale(objData.scale);
				redButton->SetRotation(objData.rotation);
				redButton->SetredButtonNum(objData.number);

				return true;
			}

			else if (objData.ForwardMatchName(L"BlueButton") == true)
			{
				BlueButton* blueButton = NewGO<BlueButton>(0, "blueButton");
				blueButton->SetPosition(objData.position);
				blueButton->SetScale(objData.scale);
				blueButton->SetRotation(objData.rotation);
				blueButton->SetredButtonNum(objData.number);

				return true;
			}

			else if (objData.ForwardMatchName(L"GreenButton") == true)
			{
				GreenButton* greenButton = NewGO<GreenButton>(0, "greenButton");
				greenButton->SetPosition(objData.position);
				greenButton->SetScale(objData.scale);
				greenButton->SetRotation(objData.rotation);
				greenButton->SetredButtonNum(objData.number);

				return true;
			}

			else if (objData.ForwardMatchName(L"door") == true)
			{
				Door* door = NewGO<Door>(0, "door");
				door->m_position = objData.position;
				door->m_scale = objData.scale;
				door->m_rotation = objData.rotation;
				door->SetDoorNumber(objData.number);

				return true;
			}

			else if (objData.EqualObjectName(L"Stage") == true)
			{
				Stage* stage = NewGO<Stage>(0, "stage");
				stage->m_position = objData.position;
				stage->m_scale = objData.scale;
				stage->m_rotation = objData.rotation;

				return true;
			}

			else
			{
				//auto name = objData.name;
				//Vector3 pos = objData.position;
			}

			return true;
		});
}

Level::~Level()
{
	//削除。
	DeleteGO(redButton);
	DeleteGO(greenButton);
	DeleteGO(blueButton);
	DeleteGO(stage);

	//レベルで複数実装したブロックのDeleteGOのコード。
	const auto& doors = FindGOs<Door>("door");
	int aa = doors.size();

	for (int i = 0; i < aa; i++)
	{
		DeleteGO(doors[i]);
	}

}

void Level::Update()
{

}