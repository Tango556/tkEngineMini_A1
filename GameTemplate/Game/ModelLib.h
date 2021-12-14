#pragma once

class ModelLib : public IGameObject
{
public:
	ModelLib();
	~ModelLib();
	enum enModel
	{
		enTeapot, enVal
	};
	void Inits();
	Model* GetModel(enModel enAny);
	
private:
	Model Models[enVal];
	ModelInitData Datas[enVal];
};