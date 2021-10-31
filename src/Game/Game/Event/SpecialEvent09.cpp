#include"../header/SpecialEvent09.h"
#include"../header/MapInfoList.h"
#include"../header/Function.h"
#include"../header/ColorMgr.h"

SpecialEvent09::SpecialEvent09()
{
	playerDirection = Direction::UP;
	playerPosition = Vector2<int>(32 * 12 + Define::MASU_SIZE / 2, 32 * 9 + Define::MASU_SIZE / 2);
	peopleDirection = Direction::DOWN;
	peoplePosition = Vector2<int>(32 * 12 + Define::MASU_SIZE / 2, 32 * 8 + Define::MASU_SIZE / 2);
	darkAlpha = 255;
}

SpecialEvent09::~SpecialEvent09()
{

}

void SpecialEvent09::UpdateEvent()
{
	if (0 < eventTimer&&eventTimer < 100)
	{
		darkAlpha -= 3;
		darkAlpha = max(0, darkAlpha);
	}
	if (eventTimer == 100)
	{
		vector<string> messages;
		messages.push_back("あ、いらっしゃいましたね。");
		messages.push_back("橋の件なんですが、実は思った以上に魔王による魔力の浸食が深刻で、並の木材ではすぐに腐敗してしまい修復が困難な状態なのです。");
		messages.push_back("技術があってもものが悪くてはどうしようもありません。");
		messages.push_back("浸食に耐えうる木材といったらタッパー森林の奥にあるルティラ樹でしょうか。");
		messages.push_back("あの木には神聖な力が備わっていると聞きます。きっと魔力による腐敗にも耐えられることでしょう。");
		messages.push_back("そこでです。何度も頼ってばかりで申し訳ないのですが、タッパー森林に行ってルティラ樹の木材を採ってきていただきたいのです。");
		messages.push_back("タッパー森林は峡谷を下りてしばらく行ったところにあります。どうかよろしくお願いします。");
		windowList.push_back(make_shared<MessageWindow>("村人", messages));
	}
	if (eventTimer == 130)
	{
		vector<string> messages;
		messages.push_back("あ、大事なことを言うのを忘れていました。");
		messages.push_back("タッパー森林は似たような地形が続く森で、一部では迷いの森などと呼ばれています。");
		messages.push_back("おそらく何の情報もなしに森に入るのは得策とは言えないでしょう。");
		messages.push_back("森へと向かう前にしっかりと情報収集をすることをおすすめします。");
		windowList.push_back(make_shared<MessageWindow>("村人", messages));
	}
	if (160 < eventTimer)
	{
		darkAlpha += 5;
	}
	if (eventTimer == 260)
	{
		endFlag = true;
	}
}

void SpecialEvent09::Draw()
{
	Vector2<int> offset = Vector2<int>(50, 4);
	int lengthY = Define::WINDOW_HEIGHT / Define::MASU_SIZE;
	int lengthX = Define::WINDOW_WIDTH / Define::MASU_SIZE;
	lengthX += 2;
	lengthY += 2;

	for (int i = 0; i < lengthY; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[15].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[15].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j, (float)Define::MASU_SIZE*i, mapBackChip[MapInfoList::GetMapInfoList()[15].mapChip[pos.y][pos.x]], TRUE);
		}
	}

	for (int i = 0; i < lengthY; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[15].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[15].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j, (float)Define::MASU_SIZE*i, mapObjectChip[MapInfoList::GetMapInfoList()[15].mapObject[0][pos.y][pos.x]], TRUE);
		}
	}

	for (int i = 0; i < lengthY; i++)for (int j = 0; j < lengthX; j++)
	{
		Vector2<int> pos = offset + Vector2<int>(j, i);
		if (0 <= (pos.y) && (pos.y) < MapInfoList::GetMapInfoList()[15].heightNum && 0 <= (pos.x) && (pos.x) < MapInfoList::GetMapInfoList()[15].widthNum)
		{
			DrawGraphF((float)Define::MASU_SIZE*j, (float)Define::MASU_SIZE*i, mapObjectChip[MapInfoList::GetMapInfoList()[15].mapObject[1][pos.y][pos.x]], TRUE);
		}
	}

	DrawRotaGraph(playerPosition.x, playerPosition.y, 1.0, 0.0, playerGraph[0][(int)playerDirection * 3 + 1], TRUE);
	DrawRotaGraph(peoplePosition.x, peoplePosition.y, 1.0, 0.0, peopleGraph[1][(int)peopleDirection * 3 + 1], TRUE);

	Function::Alpha(darkAlpha);
	DrawFillBox(0, 0, Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
	Function::Alpha(255);

	if (windowList.size() != 0)
	{
		windowList.front()->Draw();
	}
}