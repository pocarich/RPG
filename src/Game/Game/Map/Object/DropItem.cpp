#include"../header/DropItem.h"

GHandle DropItem::graph;

DropItem::DropItem(vector<int> itemList, Vector2<int> masuPosition,Vector2<double>& camera) :itemList(itemList), masuPosition(masuPosition),camera(camera)
{
	deleteFlag = false;
}

void DropItem::Load()
{
	graph = LoadGraph("data/graph/map/dropItem.png");
	assert(graph != 0 && "DropItem::Load()");
}

void DropItem::Update()
{

}

void DropItem::Draw()
{
	DrawRotaGraphF(masuPosition.x*Define::MASU_SIZE + Define::MASU_SIZE / 2 - camera.x, masuPosition.y*Define::MASU_SIZE + Define::MASU_SIZE / 2 - camera.y, 1.0, 0.0, graph, TRUE);
}

void DropItem::Picked()
{
	deleteFlag = true;
}