#include "Animation.h"
D3DCOLOR check;

Animation::Animation(const char* filePath, int totalFrame, int rows, int columns, float timePerFrame, D3DCOLOR colorKey)
{
	InitWithAnimation(filePath, totalFrame, rows, columns, timePerFrame, colorKey);
}
Animation::Animation(const char * filePath, int totalFrame, int rows, int columns, float timePerFrame, bool repeat, D3DCOLOR colorKey)
{
	InitWithAnimation(filePath, totalFrame, rows, columns, timePerFrame, repeat, colorKey);
}
void Animation::InitWithAnimation(const char* filePath, int totalFrame, int rows, int columns, float timePerFrame, bool repeat, D3DCOLOR colorKey)
{
	//GAMELOG("animation: frame: %d, row: %d, column: %d, time: %f", totalFrame, rows, columns, timePerFrame);
	this->InitWithSprite(filePath);
	mCurrentColumn = 0;
	mCurrentRow = 0;
	mTimePerFrame = timePerFrame;
	mTotalFrame = totalFrame;
	mRows = rows;
	mColumns = columns;


	//width - height luc nay la cua spritesheet
	mFrameWidth = GetWidth() / mColumns;
	mFrameHeight = GetHeight() / mRows;

	SetWidth(mFrameWidth);
	SetHeight(mFrameHeight);

	mRect.top = 0;
	mRect.left = 0;
	mRect.right = mFrameWidth;
	mRect.bottom = mFrameHeight;

	SetSourceRect(mRect);
}
void Animation::LoadSpriteInfo(const char* fileInfoPath) {

	FILE* file;
	file = fopen(fileInfoPath, "r");
	if (file)
	{

		while (!feof(file))
		{
			int width, height;
			RECT rect;
			fscanf(file, "%d %d %d %d", &rect.left, &rect.top, &width, &height);
			rect.right = rect.left + width;
			rect.bottom = rect.top + height;
			AddFrameRect(rect);
		}
	}

	fclose(file);
}
void Animation::AddFrameRect(RECT rect)
{
	if (mFrameRectList.empty())
	{
		mCurrentRect = rect;
	}
	mFrameRectList.push_back(rect);
	mTotalFrames = mFrameRectList.size();

	mEndFrame = mTotalFrames - 1;
}
void Animation::AddFrameRect(float left, float top, float right, float bottom)
{
	RECT rect;
	rect.left = left;
	rect.top = top;
	rect.right = right;
	rect.bottom = bottom;

	this->AddFrameRect(rect);
}
Animation::Animation(const char* filePath, const char* filePathInfo, float timePerFrame, bool loop) {

	//Init Sprite nguyên sheet
	this->InitWithSprite(filePath);
	LoadSpriteInfo(filePathInfo);
	mTimePerFrame = timePerFrame;
	mTotalFrame = mFrameRectList.size();
	mIsLoop = loop;
	mEndAnimate = false;
	this->Start();
}
void Animation::Start()
{
	mEndAnimate = false;
	mCanAnimate = true;
	mCurrentIndex = 0;
	//Set kich thuoc sprie ban dau (sprite)
	SetWidth((mFrameRectList[0].right - mFrameRectList[0].left));
	SetHeight((mFrameRectList[0].bottom - mFrameRectList[0].top));
	//Source Rect (Sprite)
	SetSourceRect(mFrameRectList[0]);
}

void Animation::Stop()
{
	mCanAnimate = false;
	mEndAnimate = true;
	mCurrentIndex = mEndFrame;
}
//Load ảnh 1 hàng, tự động cắt frame bằng nhau (không dùng)

Animation::Animation()
{
}


void Animation::InitWithAnimation(const char* filePath, int totalFrame, int rows, int columns, float timePerFrame, D3DCOLOR colorKey)
{
	//GAMELOG("animation: frame: %d, row: %d, column: %d, time: %f", totalFrame, rows, columns, timePerFrame);
	this->InitWithSprite(filePath);
	check = colorKey;
	mCurrentColumn = 0;
	mCurrentRow = 0;
	mTimePerFrame = timePerFrame;
	mTotalFrame = totalFrame;
	mRows = rows;
	mColumns = columns;

	//width - height luc nay la cua spritesheet
	mFrameWidth = GetWidth() / mColumns;
	mFrameHeight = GetHeight() / mRows;

	SetWidth(mFrameWidth);
	SetHeight(mFrameHeight);

	mRect.top = 0;
	mRect.left = 0;
	mRect.right = mFrameWidth;
	mRect.bottom = mFrameHeight;
	SetSourceRect(mRect);
}

Animation::~Animation()
{

}
void Animation::NextFrame()
{
	this->SetIndex(mCurrentIndex + 1);
}

int Animation::GetIndex()
{
	return mCurrentIndex;
}

void Animation::SetIndex(int index)
{
	if (index == mCurrentIndex || mTotalFrames == 0)
		return;

	mCurrentIndex = index;

	if (mCurrentIndex > mEndFrame)
		mCurrentIndex = mStartFrame;

	mCurrentRect = mFrameRectList[mCurrentIndex];

	if (!mIsLoop && mCurrentIndex == mEndFrame)
	{
		this->Stop();
	}
}

void Animation::Update(float dt)
{
	if (mTotalFrame <= 1)
		return;

	if (mCurrentTotalTime >= mTimePerFrame)
	{
		mCurrentTotalTime = 0;
		mCurrentIndex++;
		mCurrentColumn++;

		if (mCurrentIndex >= mTotalFrame)
		{
			isEndAnimate = true;
			mCurrentIndex = 0;
			mCurrentColumn = 0;
			mCurrentRow = 0;
		}

		if (mCurrentColumn >= mColumns)
		{
			mCurrentColumn = 0;
			mCurrentRow++;

			if (mCurrentRow >= mRows)
				mCurrentRow = 0;
		}

		mRect.left = mCurrentColumn * mFrameWidth;
		mRect.right = mRect.left + mFrameWidth;
		mRect.top = mCurrentRow * mFrameHeight;
		mRect.bottom = mRect.top + mFrameHeight;

		SetSourceRect(mRect);
	}
	else
	{
		mCurrentTotalTime += dt;
	}

}
void Animation::Update(float dt, int fake)
{
	if (mCanAnimate) {
		if (mTotalFrame <= 1)
			return;

		if (mCurrentTotalTime >= mTimePerFrame)
		{

			if (mCurrentIndex > mEndFrame)
			{
				if (mIsLoop) {
					mCurrentIndex = 0;
				}
				else {
					Stop();
				}
			}
			//if (mFrameRectList.size() != 0) {
			SetSourceRect(mFrameRectList[mCurrentIndex]);
			SetWidth((mFrameRectList[mCurrentIndex].right - mFrameRectList[mCurrentIndex].left));
			SetHeight((mFrameRectList[mCurrentIndex].bottom - mFrameRectList[mCurrentIndex].top));
			//}	
			mCurrentTotalTime = 0;
			mCurrentIndex++;
		}
		else
		{
			mCurrentTotalTime += dt;
		}
	}
}
void Animation::UpdateS(float dt)
{
	if (mTotalFrame <= 1)
		return;

	if (mCurrentTotalTime >= mTimePerFrame)
	{
		mCurrentTotalTime = 0;
		if (mCurrentIndex < mTotalFrame - 1)
		{
			mCurrentIndex++;
			mCurrentColumn++;

			/*if (mCurrentIndex >= mTotalFrame)
			{
			mCurrentIndex = 0;
			mCurrentColumn = 0;
			mCurrentRow = 0;
			}*/

			if (mCurrentColumn >= mColumns)
			{
				mCurrentColumn = 0;
				mCurrentRow++;

				if (mCurrentRow >= mRows)
					mCurrentRow = 0;
			}

			mRect.left = mCurrentColumn * mFrameWidth;
			mRect.right = mRect.left + mFrameWidth;
			mRect.top = mCurrentRow * mFrameHeight;
			mRect.bottom = mRect.top + mFrameHeight;
		}
		else
		{
			mRect.left = mCurrentColumn * mFrameWidth;
			mRect.right = mRect.left + mFrameWidth;
			mRect.top = mCurrentRow * mFrameHeight;
			mRect.bottom = mRect.top + mFrameHeight;
		}
		SetSourceRect(mRect);
	}
	else
	{
		mCurrentTotalTime += dt;
	}
}
void Animation::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale,
	D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{

	Sprite::Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}

void Animation::Draw(D3DXVECTOR2 translate)
{
	Sprite::Draw(D3DXVECTOR3(), RECT(), D3DXVECTOR2(), translate);
}