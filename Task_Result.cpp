//-------------------------------------------------------------------
//^CgζΚ
//-------------------------------------------------------------------
#include  "MyPG.h"
#include  "Task_Result.h"
#include  "Task_Title.h"

namespace  Result
{
	Resource::WP  Resource::instance;
	//-------------------------------------------------------------------
	//\[XΜϊ»
	bool  Resource::Initialize()
	{
		this->thisTime = "thisTime";
		this->yourScore = "yourScore";
		this->result = "result";
		this->Number_Image = "resultNumber";
		this->presS = "pressS";
		DG::Image_Create(this->thisTime, "./data/image/thisTime.png");
		DG::Image_Create(this->yourScore, "./data/image/yourScore.png");
		DG::Image_Create(this->result, "./data/image/result.png");
		DG::Image_Create(this->Number_Image, "./data/image/Number.png");
		DG::Image_Create(this->presS, "./data/image/pressS.png");

		return true;
	}
	//-------------------------------------------------------------------
	//\[XΜπϊ
	bool  Resource::Finalize()
	{
		DG::Image_Erase(this->thisTime);
		DG::Image_Erase(this->yourScore);
		DG::Image_Erase(this->result);
		DG::Image_Erase(this->Number_Image);
		return true;
	}
	//-------------------------------------------------------------------
	//uϊ»v^XNΆ¬ΙPρΎ―s€
	bool  Object::Initialize(int game_score)
	{
		//X[p[NXϊ»
		__super::Initialize(defGroupName, defName, true);
		//\[XNXΆ¬or\[X€L
		this->res = Resource::Create();

		//f[^ϊ»
		this->score = game_score;
		this->timeCnt = 0;
		for (int i = 0; i < 10; i++)
		{
			this->src_Number[i].x = (140 * i);
			this->src_Number[i].y = 0;
			this->src_Number[i].w = 140;
			this->src_Number[i].h = 140;
		}

		//JΜέθ
		
		DG::EffectState().param.bgColor = ML::Color(1, 0, 0, 0);
		//^XNΜΆ¬

		return  true;
	}
	//-------------------------------------------------------------------
	//uIΉv^XNΑΕΙPρΎ―s€
	bool  Object::Finalize()
	{
		//f[^^XNπϊ


		if (!ge->QuitFlag() && this->nextTaskCreate)
		{
			//ψ«p¬^XNΜΆ¬
			auto NextTask = Title::Object::Create(true);
		}

		return  true;
	}
	//-------------------------------------------------------------------
	//uXVvPt[Ιs€
	void  Object::UpDate()
	{
		auto in = DI::GPad_GetState("P1");

		if (in.ST.down)
		{
			this->Kill();
		}

		this->timeCnt++;
	}
	//-------------------------------------------------------------------
	//uQc`ζvPt[Ιs€
	void  Object::Render2D_AF()
	{
		//result
		ML::Box2D draw_Result(30, 30, 400, 100);
		ML::Box2D src_Result(0, 0, 500, 140);
		DG::Image_Draw(this->res->result, draw_Result, src_Result);
		//this time
		if (this->timeCnt > 60)
		{
			ML::Box2D draw_ThisTime(500, 70, 700, 140);
			ML::Box2D src_ThisTime(0, 0, 700, 140);
			DG::Image_Draw(this->res->thisTime, draw_ThisTime, src_ThisTime);
		}
		//your score
		if (this->timeCnt > 120)
		{
			ML::Box2D draw_YourScore(450, 300, 770, 140);
			ML::Box2D src_YourScore(0, 0, 770, 140);
			DG::Image_Draw(this->res->yourScore, draw_YourScore, src_YourScore);
		}
		//XRA[\¦
		if (this->timeCnt > 180)
		{
			this->Draw_Score();
		}
		//press S to return title
		if (this->timeCnt > 240)
		{
			ML::Box2D draw_pressS(200, 650, 700, 70);
			ML::Box2D src_pressS(0, 0, 1400, 140);
			DG::Image_Draw(this->res->presS, draw_pressS, src_pressS);
		}

	}

	void  Object::Render3D_L0()
	{
		
	}

	//------------------------------------------------------------------------------------
	//ΗΑ\bh
	void Object::Draw_Score()
	{
		int score1000, score100, score10, score1;
		score1000 = this->score / 1000;
		score100 = (this->score / 100) % 10;
		score10 = (this->score / 10) % 10;
		score1 = this->score % 10;

		ML::Box2D draw1000(400, 450, 140, 140);
		ML::Box2D draw100(520, 450, 140, 140);
		ML::Box2D draw10(640, 450, 140, 140);
		ML::Box2D draw1(760, 450, 140, 140);

		//`ζ
		DG::Image_Draw(this->res->Number_Image, draw1000, this->src_Number[score1000]);
		DG::Image_Draw(this->res->Number_Image, draw100, this->src_Number[score100]);
		DG::Image_Draw(this->res->Number_Image, draw10, this->src_Number[score10]);
		DG::Image_Draw(this->res->Number_Image, draw1, this->src_Number[score1]);
	}
	//
	//ΘΊΝξ{IΙΟXsvΘ\bh
	//
	//-------------------------------------------------------------------
	//^XNΆ¬ϋ
	Object::SP  Object::Create(bool  flagGameEnginePushBack_, int game_score)
	{
		Object::SP  ob = Object::SP(new  Object());
		if (ob) {
			ob->me = ob;
			if (flagGameEnginePushBack_) {
				ge->PushBack(ob);//Q[GWΙo^
			}
			if (!ob->B_Initialize(game_score)) {
				ob->Kill();//CjVCYΙΈs΅½ηKill
			}
			return  ob;
		}
		return nullptr;
	}
	//-------------------------------------------------------------------
	bool  Object::B_Initialize(int game_score)
	{
		return  this->Initialize(game_score);
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
	//\[XNXΜΆ¬
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