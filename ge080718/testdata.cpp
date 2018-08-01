#include "testdata.h"
#include "globals.h"

	
TestData::TestData()
{
	Renderer* renderer = globals::renderer;
	surfaces = new GraphicsPool();
	//GraphicsComponent* background = renderer->createGraphicsComponent(800, 600);
	//background->clear(0x550000);
	//backgroundSurface = surfaces->addComponent(background);

	GraphicsComponent* defaultImage = renderer->createGraphicsComponent(32, 32);
	defaultImage->clear(0x880088);
	defaultSurface = surfaces->addComponent(defaultImage);

	GraphicsComponent* grass = GraphicsComponent::loadGraphicsComponent("grasstile.png");
	grassSurface = surfaces->addComponent(grass);

	GraphicsComponent* actor = renderer->createGraphicsComponent(32, 32);
	actor->clear(0x63d3b1);
	actorSurface = surfaces->addComponent(actor);

	GraphicsComponent* dude = GraphicsComponent::loadGraphicsComponent("dude.png");
	dudeSurface = surfaces->addComponent(dude);

	GraphicsComponent* water = GraphicsComponent::loadGraphicsComponent("watertile.png");
	waterSurface = surfaces->addComponent(water);


	grassMat = new Material(grass, 2.0f, 1.0f);
	waterMat = new Material(water, 5.0f, 5.0f);
	nullMat = new Material(nullptr, 1.0f, 1.0f);
	dudeMat = new Material(dude, 1.0f, 1.0f);

	grassTile = new Tile(grassMat, false);
	waterTile = new Tile(waterMat, false);
	nullTile = new Tile(nullMat, true);
}

TestData::~TestData()
{
	delete surfaces;
	delete grassTile;
	delete waterTile;
	delete nullTile;
	delete grassMat;
	delete waterMat;
	delete nullMat;
	delete dudeMat;

	grassTile = nullptr;
	surfaces = nullptr;
	grassMat = nullptr;
	waterMat = nullptr;
	nullMat = nullptr;
	waterTile = nullptr;
	nullTile = nullptr;
	dudeMat = nullptr;
}