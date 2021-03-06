//-------------------------------------------------------------------
//タイトル画面
//-------------------------------------------------------------------
#include  "MyPG.h"
#include  "Task_Title.h"
#include "Task_cursor.h"
#include "Task_Tutorial.h"
#include  "easing.h"

namespace  Title
{
	Resource::WP  Resource::instance;
	//-------------------------------------------------------------------
	//リソースの初期化
	bool  Resource::Initialize()
	{
		this->select_Guide_Image = "SGI";
		this->press_Any_Key_Image = "PAKI";
		this->start_Image = "SI";
		this->tutorial_Image = "TI";
		this->Title_Name_Image[0] = "Title_S";
		this->Title_Name_Image[1] = "Title_N";
		this->Title_Name_Image[2] = "Title_A";
		this->Title_Name_Image[3] = "Title_K";
		this->Title_Name_Image[4] = "Title_E";
		this->Title_Name_Image[5] = "Title_G";
		this->Title_Name_Image[6] = "Title_A";
		this->Title_Name_Image[7] = "Title_M";
		this->Title_Name_Image[8] = "Title_E";		
		this->BG_ImageName = "BG";
		
		DG::Image_Create(this->select_Guide_Image, "./data/image/moveSelect.png");
		DG::Image_Create(this->press_Any_Key_Image, "./data/image/preaaAny.png");
		DG::Image_Create(this->start_Image, "./data/image/start.png");
		DG::Image_Create(this->tutorial_Image, "./data/image/tutorial.png");
		DG::Image_Create(this->BG_ImageName, "./data/image/TItleBG.jpg");
		DG::Image_Create(this->Title_Name_Image[0], "./data/image/S.png");
		DG::Image_Create(this->Title_Name_Image[1], "./data/image/N.png");
		DG::Image_Create(this->Title_Name_Image[2], "./data/image/A.png");
		DG::Image_Create(this->Title_Name_Image[3], "./data/image/K.png");
		DG::Image_Create(this->Title_Name_Image[4], "./data/image/E.png");
		DG::Image_Create(this->Title_Name_Image[5], "./data/image/G.png");
		DG::Image_Create(this->Title_Name_Image[6], "./data/image/A.png");
		DG::Image_Create(this->Title_Name_Image[7], "./data/image/M.png");
		DG::Image_Create(this->Title_Name_Image[8], "./data/image/E.png");

		return true;
	}
	//-------------------------------------------------------------------
	//リソースの解放
	bool  Resource::Finalize()
	{
		DG::Image_Erase(this->select_Guide_Image);
		DG::Image_Erase(this->press_Any_Key_Image);
		DG::Image_Erase(this->start_Image);
		DG::Image_Erase(this->tutorial_Image);
		DG::Image_Erase(this->BG_ImageName);
		for (int i = 0; i < 9; i++)
		{
			DG::Image_Erase(this->Title_Name_Image[i]);
		}

		return true;
	}
	//-------------------------------------------------------------------
	//「初期化」タスク生成時に１回だけ行う処理
	bool  Object::Initialize()
	{
		//スーパークラス初期化
		__super::Initialize(defGroupName, defName, true);
		//リソースクラス生成orリソース共有
		this->res = Resource::Create();

		//★データ初期化
		this->select_now = false;
		this->timeCnt = 0;
		this->next_Task_Index = 0;

		for (int i = 0; i < 9; i++)
		{
			this->Title_Name[i].x = -140;
			this->Title_Name[i].y = -140;
		}

		//easing function set
		//SNAKE
		easing::Set("Title_0_x", easing::QUARTINOUT, 1280, 100, 100);
		easing::Set("Title_1_x", easing::QUARTINOUT, 1280, 240, 110);
		easing::Set("Title_2_x", easing::QUARTINOUT, 1280, 380, 120);
		easing::Set("Title_3_x", easing::QUARTINOUT, 1280, 520, 130);
		easing::Set("Title_4_x", easing::QUARTINOUT, 1280, 660, 140);
		easing::Set("Title_0_y", easing::QUINTOUT, 720, 40, 100);

		//GAME
		easing::Set("Title_5_x", easing::QUARTINOUT, -140, 640, 180);
		easing::Set("Title_6_x", easing::QUARTINOUT, -140, 780, 170);
		easing::Set("Title_7_x", easing::QUARTINOUT, -140, 920, 160);
		easing::Set("Title_8_x", easing::QUARTINOUT, -140, 1060, 150);
		easing::Set("Title_1_y", easing::QUINTOUT, 720, 220, 150);

		easing::Start("Title_0_x");
		easing::Start("Title_1_x");
		easing::Start("Title_2_x");
		easing::Start("Title_3_x");
		easing::Start("Title_4_x");
		easing::Start("Title_0_y");
		easing::Start("Title_5_x");
		easing::Start("Title_6_x");
		easing::Start("Title_7_x");
		easing::Start("Title_8_x");
		easing::Start("Title_1_y");


		//カメラの設定
		ge->camera[0] = MyPG::Camera::Create(
			ML::Vec3(1000.0f, 0.0f, 1000.0f),				//	ターゲット位置
			ML::Vec3(1000.0f, 1400.0f, -1000.0f),			//	カメラ位置
			ML::Vec3(0.0f, 1.0f, 0.0f),					//	カメラの上方向ベクトル
			ML::ToRadian(35), 10.0f, 4000.0f,	//	視野角・視野距離
			(float)ge->screenWidth / (float)ge->screenHeight);		//	画面比率		
		DG::EffectState().param.bgColor = ML::Color(1, 0, 0, 0);
		//★タスクの生成

		return  true;
	}
	//-------------------------------------------------------------------
	//「終了」タスク消滅時に１回だけ行う処理
	bool  Object::Finalize()
	{
		//★データ＆タスク解放


		if (!ge->QuitFlag() && this->nextTaskCreate)
		{
			//★引き継ぎタスクの生成
			if (this->next_Task_Index == -1)
			{
				//ゲームタスクに移る
				auto nextTask = Game::Object::Create(true);
			}
			else if (this->next_Task_Index == 1)
			{
				//テュートリアルタスクに移る
				auto nextTask = Tutorial::Object::Create(true);
			}
		}

		return  true;
	}
	//-------------------------------------------------------------------
	//「更新」１フレーム毎に行う処理
	void  Object::UpDate()
	{
		auto in = DI::GPad_GetState("P1");
		easing::UpDate();
		this->UpDate_Title_Name();
		
		if (this->Press_Any_Key() && this->select_now == false)
		{
			auto cursor = Cursor::Object::Create(true);
			this->select_now = true;
		}
		

		this->timeCnt++;
	}
	//-------------------------------------------------------------------
	//「２Ｄ描画」１フレーム毎に行う処理
	void  Object::Render2D_AF()
	{
		

		ML::Box2D draw_BG(0, 0, 1280, 720);
		ML::Box2D src_BG(0, 0, 2560, 1600);
		DG::Image_Draw(this->res->BG_ImageName, draw_BG, src_BG);
		this->Draw_Title_Name();
		this->Draw_PAK();
		this->Draw_Menu();
	}

	void  Object::Render3D_L0()
	{
		
	}
	//----------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------
	//追加メソッド
	//スティック以外のボタンを押すのかを判別
	bool Object::Press_Any_Key()
	{
		auto in1 = DI::GPad_GetState("P1");

		if (in1.B1.down || in1.B2.down || in1.B3.down || in1.B4.down ||
			in1.HD.down || in1.HL.down || in1.HR.down || in1.HU.down ||
			in1.L1.down || in1.L2.down || in1.L3.down ||
			in1.R1.down || in1.R2.down || in1.R3.down ||
			in1.SE.down || in1.ST.down)
		{
			return true;
		}

		return false;
	}
	//-------------------------------------------------------------------------------
	//タイトル名を表示
	void Object::Draw_Title_Name()
	{
		ML::Box2D draw(0, 0, 140, 140);
		ML::Box2D src(0, 0, 140, 140);

		for (int i = 0; i < 9; i++)
		{
			DG::Image_Draw(this->res->Title_Name_Image[i], draw.OffsetCopy(this->Title_Name[i]), src);
		}
	}
	//-----------------------------------------------------------------------------------
	//タイトル名の位置を更新
	void Object::UpDate_Title_Name()
	{
		//X座標更新
		this->Title_Name[0].x = easing::GetPos("Title_0_x");
		this->Title_Name[1].x = easing::GetPos("Title_1_x");
		this->Title_Name[2].x = easing::GetPos("Title_2_x");
		this->Title_Name[3].x = easing::GetPos("Title_3_x");
		this->Title_Name[4].x = easing::GetPos("Title_4_x");
		this->Title_Name[5].x = easing::GetPos("Title_5_x");
		this->Title_Name[6].x = easing::GetPos("Title_6_x");
		this->Title_Name[7].x = easing::GetPos("Title_7_x");
		this->Title_Name[8].x = easing::GetPos("Title_8_x");

		for (int i = 0; i < 5; i++)
		{
			this->Title_Name[i].y = easing::GetPos("Title_0_y");
		}
		for (int i = 5; i < 9; i++)
		{
			this->Title_Name[i].y = easing::GetPos("Title_1_y");
		}
	}
	//----------------------------------------------------------------------------------
	//press any key を表示
	void Object::Draw_PAK()
	{
		if (this->timeCnt < 200 || this->select_now)
		{
			return;
		}
		ML::Box2D draw(250, 500, 750, 100);
		ML::Box2D src(0, 0, 900, 140);

		DG::Image_Draw(this->res->press_Any_Key_Image, draw, src);
	}

	//---------------------------------------------------------------------
	//メニューの表示
	void Object::Draw_Menu()
	{
		if(!this->select_now)
		{
			return;
		}

		ML::Box2D draw_Start(400, 410, 380, 100);
		ML::Box2D src_Start(0, 0, 420, 140);
		ML::Box2D draw_Tutorial(400, 500, 520, 100);
		ML::Box2D src_Tutorial(0, 0, 560, 140);
		ML::Box2D draw_Guide(400, 650, 500, 64);
		ML::Box2D src_Guide(0, 0, 1400, 140);

		DG::Image_Draw(this->res->start_Image, draw_Start, src_Start);
		DG::Image_Draw(this->res->tutorial_Image, draw_Tutorial, src_Tutorial);
		DG::Image_Draw(this->res->select_Guide_Image, draw_Guide, src_Guide);
	}
	//----------------------------------------------------------------------------
	//次のタスクを決める関数
	void Object::I_Select(int select)
	{
		//-1ならゲーム本編
		//1ならテュートリアル
		this->next_Task_Index = select;

		this->Kill();
	}
	//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
	//以下は基本的に変更不要なメソッド
	//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
	//-------------------------------------------------------------------
	//タスク生成窓口
	Object::SP  Object::Create(bool  flagGameEnginePushBack_)
	{
		Object::SP  ob = Object::SP(new  Object());
		if (ob) {
			ob->me = ob;
			if (flagGameEnginePushBack_) {
				ge->PushBack(ob);//ゲームエンジンに登録
			}
			if (!ob->B_Initialize()) {
				ob->Kill();//イニシャライズに失敗したらKill
			}
			return  ob;
		}
		return nullptr;
	}
	//-------------------------------------------------------------------
	bool  Object::B_Initialize()
	{
		return  this->Initialize();
	}
	//-------------------------------------------------------------------
	Object::~Object() { this->B_Finalize(); }
	bool  Object::B_Finalize()
	{
		auto  rtv = this->Finalize();
		return  rtv;
	}
	//-------------------------------------------------------------------
	Object::Object() {	}
	//-------------------------------------------------------------------
	//リソースクラスの生成
	Resource::SP  Resource::Create()
	{
		if (auto sp = instance.lock()) {
			return sp;
		}
		else {
			sp = Resource::SP(new  Resource());
			if (sp) {
				sp->Initialize();
				instance = sp;
			}
			return sp;
		}
	}
	//-------------------------------------------------------------------
	Resource::Resource() {}
	//-------------------------------------------------------------------
	Resource::~Resource() { this->Finalize(); }
}