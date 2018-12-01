#include <iostream>
#include <time.h>
#include "InputManager.h"
#include "Game.h"
#include "MenuState.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
MenuState::MenuState(GameState* state) : GameState(state){



}

void MenuState::SetUpWalls() {
	WallOne.SetVecs(glm::vec3(-10.0f, -0.5f, -5.0f), glm::vec3(10.0f, -0.5f, 5.0f));
	WallTwo.SetVecs(glm::vec3(-10.0f, -0.5f, -5.0f), glm::vec3(10.0f, -0.5f, 5.0f));
	WallThree.SetVecs(glm::vec3(-10.0f, -0.5f, -5.0f), glm::vec3(10.0f, -0.5f, 5.0f));
	WallFour.SetVecs(glm::vec3(-10.0f, -0.5f, -5.0f), glm::vec3(10.0f, -0.5f, 5.0f));
	WallOne.CreateWallIds();
	WallTwo.CreateWallIds();
	WallThree.CreateWallIds();
	WallFour.CreateWallIds();
	WallOne.SetTexture("Textures\\WoodText.jpg");
	WallTwo.SetTexture("Textures\\WoodText.jpg");
	WallThree.SetTexture("Textures\\WoodText.jpg");
	WallFour.SetTexture("Textures\\WoodText.jpg");
	WallOne.RotateX(90);
	WallTwo.RotateX(90);
	WallThree.RotateX(90);
	WallFour.RotateX(90);
	WallThree.RotateZ(90);
	WallFour.RotateZ(90);
	WallOne.MoveQuad(glm::vec3(0, 10.5f, 0));
	WallTwo.MoveQuad(glm::vec3(0, -9.5f, 0));
	WallThree.MoveQuad(glm::vec3(0, 10.5f, 0));
	WallFour.MoveQuad(glm::vec3(0, -9.5f, 0));
}

void MenuState::SetUpObjects(){
	// createing the table.
	mod_Table.Create();
	mod_Table.SetAmbient(0.19125f, 0.0735f, 0.0225f);
	mod_Table.SetDiffuse(0.7038f, 0.27048f, 0.0828f);
	mod_Table.SetSpecular(0.256777f, 0.137622f, 0.086014f);
	mod_Table.SetShininess(12.8f);
	mod_Table.SetPosition(2.0f, -0.5f, 2.0f);
	mod_Table.SetScale(0.5f, 0.5f, 0.5f);
	mod_Table.SetTexture("3DAssessts\\Textures\\Copper.jpg");
	mod_Table.IsTextured() = true;
	mod_Table.LoadModel("3DAssessts\\Models\\Table.obj");
	//creating chair one
	mod_ChairOne.Create();
	mod_ChairOne.SetAmbient(1.0f, 1.0f, 1.0f);
	mod_ChairOne.SetDiffuse(0.78f, 0.57f, 0.11f);
	mod_ChairOne.SetSpecular(0.99f, 0.94f, 0.81f);
	mod_ChairOne.SetShininess(100.0f);
	mod_ChairOne.SetPosition(0.0f, -0.5f, 2.0f);
	mod_ChairOne.SetScale(0.5f, 0.5f, 0.5f);
	mod_ChairOne.SetTexture("3DAssessts\\Textures\\Chair.png");
	mod_ChairOne.IsTextured() = true;
	mod_ChairOne.LoadModel("3DAssessts\\Models\\Chair.obj");
	//creating char two
	mod_ChairTwo.Create();
	mod_ChairTwo.SetAmbient(0.0215f, 0.1745f, 0.0215f);
	mod_ChairTwo.SetDiffuse(0.07568f, 0.61424f, 0.07568f);
	mod_ChairTwo.SetSpecular(0.633f, 0.727811f, 0.633f);
	mod_ChairTwo.SetShininess(76.8f);
	mod_ChairTwo.SetPosition(4.0f, -0.5f, 2.0f);
	mod_ChairTwo.SetScale(0.5f, 0.5f, 0.5f);
	mod_ChairTwo.SetRotation(0, 180, 0);
	mod_ChairTwo.SetTexture("3DAssessts\\Textures\\Emerald.jpg");
	mod_ChairTwo.IsTextured() = true;
	mod_ChairTwo.LoadModel("3DAssessts\\Models\\Stool.obj");
	//creating a gecko
	mod_Gecko.Create();
	mod_Gecko.SetAmbient(1.0f, 1.0f, 1.0f);
	mod_Gecko.SetDiffuse(0.78f, 0.57f, 0.11f);
	mod_Gecko.SetSpecular(0.99f, 0.94f, 0.81f);
	mod_Gecko.SetShininess(100.0f);
	mod_Gecko.SetPosition(2.0f, 1.2f, 2.0f);
	mod_Gecko.SetScale(0.08f, 0.08f, 0.08f);
	mod_Gecko.SetTexture("3DAssessts\\Textures\\Gecko.png");
	mod_Gecko.IsTextured() = true;
	mod_Gecko.LoadModel("3DAssessts\\Models\\Gecko.obj");
	//creating a fridge.
	mod_Fridge.Create();
	mod_Fridge.SetAmbient(0.25f, 0.25f, 0.25f);
	mod_Fridge.SetDiffuse(0.4f, 0.4f, 0.4f);
	mod_Fridge.SetSpecular(0.774597f, 0.774597f, 0.774597f);
	mod_Fridge.SetShininess(76.8f);
	mod_Fridge.SetPosition(8.0f, -0.5f, -6.0f);
	mod_Fridge.SetScale(0.5f, 0.5f, 0.5f);
	mod_Fridge.SetRotation(0, 180, 0);
	mod_Fridge.SetTexture("3DAssessts\\Textures\\Chrome.jpg");
	mod_Fridge.IsTextured() = true;
	mod_Fridge.LoadModel("3DAssessts\\Models\\Fridge.obj");



}
	
//------------------------------------------------------------------------------------------------------
//function that creates a new background screen object and menu
//------------------------------------------------------------------------------------------------------
bool MenuState::OnEnter(){
	DrawHelp = true;
	

	TheFloor.SetVecs(glm::vec3(-10.0f, -0.5f, -10.0f), glm::vec3(10.0f, -0.5f, 10.0f));
	TheFloor.MakeFloorIDs();
	TheFloor.SetTexture("Textures\\Floor.jpg");

	SpritTesting.SetVecs(glm::vec3(-1.0f, 1.0f, 0.5f), glm::vec3(1.0f, -1.0f, -0.5f));
	SpritTesting.SimpleHUDIDs();
	SpritTesting.SetTexture("Textures\\HUDTwo.png");
	SpritTesting.SetDimension(380/2, 88/2);
	SpritTesting.SetPosition2D(glm::vec2(1024/2, 768/2));
	

	HelpingHUD.SetVecs(glm::vec3(-1.0f, 1.0f, 0.5f), glm::vec3(1.0f, -1.0f, -0.5f));
	HelpingHUD.SimpleHUDIDs();
	HelpingHUD.SetTexture("Textures\\HelpScreen.jpg");
	HelpingHUD.SetDimension(1024/2, 768/2);
	HelpingHUD.SetPosition2D(glm::vec2(1, 1));


	SetUpWalls();
	SetUpObjects();

	FakeWaterFall.SetVecs(glm::vec3(-2.0f, 2.0f, 0.5f), glm::vec3(2.0f, -2.0f, 0.5f));
	FakeWaterFall.FakeWaterFallEffect();
	FakeWaterFall.SetPosition3D(glm::vec3(2,2,9.4));
	
	CrossHatchText.SetVecs(glm::vec3(-2.0f, 2.0f, 0.5f), glm::vec3(2.0f, -2.0f, 0.5f));
	CrossHatchText.SetTexture("Textures\\karsten.jpg");
	CrossHatchText.GslCrossHatchIDs();
	CrossHatchText.SetPosition3D(glm::vec3(2, 2, -10.4));

	SkyBox.SetVecs(glm::vec3(-50.0f, 50.0f, 50.0f), glm::vec3(50.0f, -1.0f, -50.0f));
	SkyBox.SetSkyBoxIDs();

	theLighter.LoadIds();
	return true;

}
//------------------------------------------------------------------------------------------------------
//function that waits for a key to be pressed before transitioning to a different state
//------------------------------------------------------------------------------------------------------
bool MenuState::Update()
{
	const Uint8* keys = TheInput::Instance()->GetKeyStates();
	int button = TheInput::Instance()->GetbuttonStatesFinal();
	int trigger = TheInput::Instance()->GetTriggerState();
	int mouseButton = TheInput::Instance()->GetMouseClickState();
	
	if (keys[SDL_SCANCODE_ESCAPE]) {
		m_isActive = m_isAlive = false;
		std::cout << "Escape is being pressed " << std::endl;
	}
	else if (button == SDL_CONTROLLER_BUTTON_BACK) {
		m_isActive = m_isAlive = false;
	}
	else if (button == SDL_CONTROLLER_BUTTON_START) {
		DrawHelp = false;
	}
	else if (keys[SDL_SCANCODE_X]) {
		CrossHatchText.SetEverythingCrossHatch(false);
	}
	else if (keys[SDL_SCANCODE_RETURN]) {
		DrawHelp = false;
	}
	else if (keys[SDL_SCANCODE_Z]) {
		CrossHatchText.SetEverythingCrossHatch(true);
	}
	else if (trigger == 1) {
		CrossHatchText.SetEverythingCrossHatch(false);
	}
	else if (trigger == 2) {
		CrossHatchText.SetEverythingCrossHatch(true);
	}
	else if (mouseButton == 1) {
		DrawHelp = false;
	}
	else if (mouseButton == 2) {
		DrawHelp = true;
	}
	theLighter.Update();
	mod_Table.Update();
	mod_ChairOne.Update();
	mod_ChairTwo.Update();
	mod_Gecko.Update();
	mod_Fridge.Update();

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that renders the background splash image and menu
//------------------------------------------------------------------------------------------------------
bool MenuState::Draw(){
	TheCamera::Instance()->SwitchTo3D();
	TheCamera::Instance()->Update();
	SkyBox.DrawSkyBox();
	FakeWaterFall.FakeWaterFallEffectDraw();
	CrossHatchText.GslCrossHatchDraw();

	WallOne.DrawWall();
	WallTwo.DrawWall();
	WallThree.DrawWall();
	WallFour.DrawWall();
	TheFloor.DrawWall();

	//drawing objects
	mod_Table.Draw();
	mod_ChairOne.Draw();
	mod_ChairTwo.Draw();
	mod_Gecko.Draw();
	mod_Fridge.Draw();

	theLighter.DrawTest();

	TheCamera::Instance()->SwitchTo2D();
	TheCamera::Instance()->NoMovementCam();
	if (DrawHelp) {
		HelpingHUD.SimpleHUDTurtoralDraw();
	}
	SpritTesting.SimpleHUDDraw();

	return true;
}
//------------------------------------------------------------------------------------------------------
//function that removes splash screen background object and menu from memory
//------------------------------------------------------------------------------------------------------
void MenuState::OnExit()
{
	theLighter.deleteIds();
}