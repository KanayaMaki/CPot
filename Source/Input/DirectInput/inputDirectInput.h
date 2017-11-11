///////////////////////////////////////
//
//	ファイル名	:	inputJoystick.h
//	作者		:	齊藤芳紀
//	作成日時	:	2017/03/18
//	更新日時	:	2017/03/18
//	内容		:	キーボードの入力クラス
//
///////////////////////////////////////

#pragma once

#include "./Atom/atom.h"
#include "./Usefull/singleton.h"

#include <dinput.h>

namespace cpot {

namespace directInput {


//仮想のJoystickコントローラーのボタンを定義
class CJoystickCode {
public:
	enum {
		cLStickLeft,
		cLStickRight,
		cLStickUp,
		cLStickDown,
		cRStickLeft,
		cRStickRight,
		cRStickUp,
		cRStickDown,
		cLButtonLeft,
		cLButtonRight,
		cLButtonUp,
		cLButtonDown,
		cRButtonLeft,
		cRButtonRight,
		cRButtonUp,
		cRButtonDown,
		cLButton1,
		cLButton2,
		cLButton3,
		cRButton1,
		cRButton2,
		cRButton3,
		cNull,
		cMax,
	};
};


//実際のデバイスのボタンを定義
class CJoystickButton {
public:
	enum {
		cStickAxis1Plus,
		cStickAxis1Minus,
		cStickAxis2Plus,
		cStickAxis2Minus,
		cStickAxis3Plus,
		cStickAxis3Minus,
		cStickAxis4Plus,
		cStickAxis4Minus,
		cStickAxis5Plus,
		cStickAxis5Minus,
		cStickAxis6Plus,
		cStickAxis6Minus,
		cPOV1XPlus,
		cPOV1XMinus,
		cPOV1YPlus,
		cPOV1YMinus,
		cPOV2XPlus,
		cPOV2XMinus,
		cPOV2YPlus,
		cPOV2YMinus,
		cPOV3XPlus,
		cPOV3XMinus,
		cPOV3YPlus,
		cPOV3YMinus,
		cPOV4XPlus,
		cPOV4XMinus,
		cPOV4YPlus,
		cPOV4YMinus,
		cButton1,
		cButton2,
		cButton3,
		cButton4,
		cButton5,
		cButton6,
		cButton7,
		cButton8,
		cButton9,
		cButton10,
		cButton11,
		cButton12,
		cButton13,
		cButton14,
		cButton15,
		cButton16,
		cButton17,
		cButton18,
		cButton19,
		cButton20,
		cNull,
		cMax,
	};
};


//仮想のJoystickコントローラーのコードをデバイスごとのボタンに変換する
struct Translater {
public:
	Translater() {
		for (u32 i = 0; i < CJoystickCode::cMax; i++) {
			//初期値は全て空入力
			mTranse[i] = CJoystickButton::cNull;
		}
	}

public:
	//変換する対応付けを設定する
	void SetButton(u32 aCode, u32 aButton) {
		//範囲チェック
		CPOT_ASSERT(aCode < CJoystickCode::cMax);
		CPOT_ASSERT(aButton < CJoystickButton::cMax);
		mTranse[aCode] = aButton;
	}

	//変換後のボタンを取得する
	u32 GetButton(u32 aCode) const {
		CPOT_ASSERT(aCode < CJoystickCode::cMax);
		return mTranse[aCode];
	}

	u32 mTranse[CJoystickCode::cMax];


	//コントローラーの種類ごとの設定を返す
	#pragma region DeviceConfig

public:
	static Translater PS4() {
		Translater res;
		//TODO PS4の設定を返す
		res.SetButton(CJoystickCode::cLStickLeft, CJoystickButton::cStickAxis1Minus);
		res.SetButton(CJoystickCode::cLStickRight, CJoystickButton::cStickAxis1Plus);
		res.SetButton(CJoystickCode::cLStickUp, CJoystickButton::cStickAxis2Minus);
		res.SetButton(CJoystickCode::cLStickDown, CJoystickButton::cStickAxis2Plus);
		res.SetButton(CJoystickCode::cRButtonRight, CJoystickButton::cButton1);
		return res;
	}

	#pragma endregion

};


class JoystickInstance {
	friend class JoystickDevice;

	//初期化
	#pragma region Init

private:
	//コンストラクタ。ユーザーにインスタンスを作らせたくないため、private
	JoystickInstance() {
		mJoystick = nullptr;
		mAleradyAcquire = false;
	}

	#pragma endregion


	//終了
	#pragma region Final

public:
	//インスタンスの解放
	void Release();

	#pragma endregion


	//取得
	#pragma region Getter

public:
	//ボタンの値を取得
	f32 GetValue(u32 aCode) const {
		CPOT_ASSERT(aCode < CJoystickCode::cMax);
		return mValue[mTranslater.GetButton(aCode)];
	}

	//このインスタンスは有効か
	BOOL IsValid() const {
		return mJoystick != nullptr;
	}

	#pragma endregion


	//設定
	#pragma region Setter

public:
	//ボタンとコードとの変換を設定
	void SetTranslater(const Translater& aTranslater) {
		mTranslater = aTranslater;
	}

	#pragma endregion


private:
	BOOL mAleradyAcquire;
	IDirectInputDevice8A* mJoystick;
	GUID mInstanceGUID;

	f32 mValue[CJoystickButton::cMax];
	Translater mTranslater;
};


class JoystickDevice : public Singleton<JoystickDevice> {
	friend Singleton<JoystickDevice>;

private:
	IDirectInput8A* mInput;
	static constexpr s32 cJoystickMaxNum = 4;
	JoystickInstance mJoystick[cJoystickMaxNum];
	HWND mHwnd;
	HINSTANCE mHInstance;

	//初期化
	#pragma region Init

private:
	JoystickDevice() {
		mInput = nullptr;
		for (s32 i = 0; i < cJoystickMaxNum; i++) {
			mJoystick[i].mJoystick = nullptr;
		}
	}

public:
	void Init(HINSTANCE aHInstance, HWND aHwnd);
	void Reset();

	#pragma endregion


	//終了処理
	#pragma region Final

public:
	~JoystickDevice();
	void Final();

	#pragma endregion


	//更新
	#pragma region Update

public:
	//入力の更新
	void Update();

	#pragma endregion


	//取得
	#pragma region Getter

	//値の取得
	f32 GetValue(u32 aCount, u32 aJoystickCode) const {
		CPOT_ASSERT(aJoystickCode < CJoystickCode::cMax);
		CPOT_ASSERT(aCount < cJoystickMaxNum);
		return mJoystick[aCount].GetValue(aJoystickCode);
	}

	BOOL IsValid(u32 aCount) const {
		CPOT_ASSERT(aCount < cJoystickMaxNum);
		return mJoystick[aCount].IsValid();
	}

	#pragma endregion


	//設定
	#pragma region Setter

public:
	//ボタンとコードとの変換を設定
	void SetTranslater(u32 aCount, const Translater& aTranslater) {
		CPOT_ASSERT(aCount < cJoystickMaxNum);
		mJoystick[aCount].SetTranslater(aTranslater);
	}

	#pragma endregion

private:
	//デバイスの接続に使用する
	static ::BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCEA*, VOID*);
	BOOL IsAlreadyUse(GUID aInstanceGUID);
	JoystickInstance* FindNoUseJoystickInstance();
};


}

}