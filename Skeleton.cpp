#include "StdAfx.h"
#include "Skeleton.h"

//----------------------------------------------------------------
// define
//----------------------------------------------------------------
#define	WIN_WIDTH	640		// 出力ウィンドウ・幅
#define	WIN_HEIGHT	480		// 出力ウィンドウ・高さ

//----------------------------------------------------------------
// global
//----------------------------------------------------------------
CvPoint	joints[NUI_SKELETON_POSITION_COUNT];	// 関節のx, y座標

//--------------------------------------------------------------
Skeleton::Skeleton(void)
{
}


//------------------------------------------------------------------
// 関節のxy座標を取得
//------------------------------------------------------------------
void Skeleton::SetJointsXY(NUI_SKELETON_DATA* skeleton) {
	int		scaleX = WIN_WIDTH;		// スケーリング係数・x軸
	int		scaleY = WIN_HEIGHT;	// スケーリング係数・y軸
	float	fx = 0;		// 関節のx座標
	float	fy = 0;		// 関節のy座標

	for (int i = 0; i < NUI_SKELETON_POSITION_COUNT; i++){
		// 奥行き画像の座標系に変換
		NuiTransformSkeletonToDepthImageF(skeleton->SkeletonPositions[i],
		                                     &fx, &fy);

		// 描画用の座標に変換
		joints[i].x = (int)(fx * scaleX + 0.5f);
		joints[i].y = (int)(fy * scaleY + 0.5f);
	}
}

//------------------------------------------------------------------
// 骨格を描画
//------------------------------------------------------------------
void Skeleton::DrawSkeleton(IplImage* img, NUI_SKELETON_DATA* skeleton, int id) {
	// 脊柱
	DrawSkeletonLine(img, joints[NUI_SKELETON_POSITION_HIP_CENTER],
	                      joints[NUI_SKELETON_POSITION_SPINE]);
	DrawSkeletonLine(img, joints[NUI_SKELETON_POSITION_SPINE],
	                      joints[NUI_SKELETON_POSITION_SHOULDER_CENTER]);
	DrawSkeletonLine(img, joints[NUI_SKELETON_POSITION_SHOULDER_CENTER],
	                      joints[NUI_SKELETON_POSITION_HEAD]);

	// 左腕
	DrawSkeletonLine(img, joints[NUI_SKELETON_POSITION_SHOULDER_CENTER], 
	                      joints[NUI_SKELETON_POSITION_SHOULDER_LEFT]);
	DrawSkeletonLine(img, joints[NUI_SKELETON_POSITION_SHOULDER_LEFT], 
	                      joints[NUI_SKELETON_POSITION_ELBOW_LEFT]);
	DrawSkeletonLine(img, joints[NUI_SKELETON_POSITION_ELBOW_LEFT], 
	                      joints[NUI_SKELETON_POSITION_WRIST_LEFT]);
	DrawSkeletonLine(img, joints[NUI_SKELETON_POSITION_WRIST_LEFT], 
	                      joints[NUI_SKELETON_POSITION_HAND_LEFT]);

	// 右腕
	DrawSkeletonLine(img, joints[NUI_SKELETON_POSITION_SHOULDER_CENTER], 
	                      joints[NUI_SKELETON_POSITION_SHOULDER_RIGHT]);
	DrawSkeletonLine(img, joints[NUI_SKELETON_POSITION_SHOULDER_RIGHT],
	                      joints[NUI_SKELETON_POSITION_ELBOW_RIGHT]);
	DrawSkeletonLine(img, joints[NUI_SKELETON_POSITION_ELBOW_RIGHT],
	                      joints[NUI_SKELETON_POSITION_WRIST_RIGHT]);
	DrawSkeletonLine(img, joints[NUI_SKELETON_POSITION_WRIST_RIGHT],
	                      joints[NUI_SKELETON_POSITION_HAND_RIGHT]);

	// 左足
	DrawSkeletonLine(img, joints[NUI_SKELETON_POSITION_HIP_CENTER],
	                      joints[NUI_SKELETON_POSITION_HIP_LEFT]);
	DrawSkeletonLine(img, joints[NUI_SKELETON_POSITION_HIP_LEFT], 
	                      joints[NUI_SKELETON_POSITION_KNEE_LEFT]);
	DrawSkeletonLine(img, joints[NUI_SKELETON_POSITION_KNEE_LEFT], 
	                      joints[NUI_SKELETON_POSITION_ANKLE_LEFT]);
	DrawSkeletonLine(img, joints[NUI_SKELETON_POSITION_ANKLE_LEFT],
	                      joints[NUI_SKELETON_POSITION_FOOT_LEFT]);
	
	// 右足
	DrawSkeletonLine(img, joints[NUI_SKELETON_POSITION_HIP_CENTER],
	                      joints[NUI_SKELETON_POSITION_HIP_RIGHT]);
	DrawSkeletonLine(img, joints[NUI_SKELETON_POSITION_HIP_RIGHT],
	                      joints[NUI_SKELETON_POSITION_KNEE_RIGHT]);
	DrawSkeletonLine(img, joints[NUI_SKELETON_POSITION_KNEE_RIGHT], 
	                      joints[NUI_SKELETON_POSITION_ANKLE_RIGHT]);
	DrawSkeletonLine(img, joints[NUI_SKELETON_POSITION_ANKLE_RIGHT],
	                      joints[NUI_SKELETON_POSITION_FOOT_RIGHT]);

	// 関節を描画
	for (int i = 0; i <NUI_SKELETON_POSITION_COUNT; i++){
		cvCircle(img, joints[i], 5, cvScalar(0, 255, 0), -1);
	}

	// ウィンドウに出力
	cvShowImage("Skeleton View", img);
}

//------------------------------------------------------------------
// 関節を結ぶ線を描画
//------------------------------------------------------------------
void Skeleton::DrawSkeletonLine(IplImage* img, CvPoint st, CvPoint ed ) {
	cvLine(img, st, ed, cvScalar(0, 0, 255), 4);
}


