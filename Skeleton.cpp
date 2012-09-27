#include "StdAfx.h"
#include "Skeleton.h"

//----------------------------------------------------------------
// define
//----------------------------------------------------------------
#define	WIN_WIDTH	640		// �o�̓E�B���h�E�E��
#define	WIN_HEIGHT	480		// �o�̓E�B���h�E�E����

//----------------------------------------------------------------
// global
//----------------------------------------------------------------
CvPoint	joints[NUI_SKELETON_POSITION_COUNT];	// �֐߂�x, y���W

//--------------------------------------------------------------
Skeleton::Skeleton(void)
{
}


//------------------------------------------------------------------
// �֐߂�xy���W���擾
//------------------------------------------------------------------
void Skeleton::SetJointsXY(NUI_SKELETON_DATA* skeleton) {
	int		scaleX = WIN_WIDTH;		// �X�P�[�����O�W���Ex��
	int		scaleY = WIN_HEIGHT;	// �X�P�[�����O�W���Ey��
	float	fx = 0;		// �֐߂�x���W
	float	fy = 0;		// �֐߂�y���W

	for (int i = 0; i < NUI_SKELETON_POSITION_COUNT; i++){
		// ���s���摜�̍��W�n�ɕϊ�
		NuiTransformSkeletonToDepthImageF(skeleton->SkeletonPositions[i],
		                                     &fx, &fy);

		// �`��p�̍��W�ɕϊ�
		joints[i].x = (int)(fx * scaleX + 0.5f);
		joints[i].y = (int)(fy * scaleY + 0.5f);
	}
}

//------------------------------------------------------------------
// ���i��`��
//------------------------------------------------------------------
void Skeleton::DrawSkeleton(IplImage* img, NUI_SKELETON_DATA* skeleton, int id) {
	// �Ғ�
	DrawSkeletonLine(img, joints[NUI_SKELETON_POSITION_HIP_CENTER],
	                      joints[NUI_SKELETON_POSITION_SPINE]);
	DrawSkeletonLine(img, joints[NUI_SKELETON_POSITION_SPINE],
	                      joints[NUI_SKELETON_POSITION_SHOULDER_CENTER]);
	DrawSkeletonLine(img, joints[NUI_SKELETON_POSITION_SHOULDER_CENTER],
	                      joints[NUI_SKELETON_POSITION_HEAD]);

	// ���r
	DrawSkeletonLine(img, joints[NUI_SKELETON_POSITION_SHOULDER_CENTER], 
	                      joints[NUI_SKELETON_POSITION_SHOULDER_LEFT]);
	DrawSkeletonLine(img, joints[NUI_SKELETON_POSITION_SHOULDER_LEFT], 
	                      joints[NUI_SKELETON_POSITION_ELBOW_LEFT]);
	DrawSkeletonLine(img, joints[NUI_SKELETON_POSITION_ELBOW_LEFT], 
	                      joints[NUI_SKELETON_POSITION_WRIST_LEFT]);
	DrawSkeletonLine(img, joints[NUI_SKELETON_POSITION_WRIST_LEFT], 
	                      joints[NUI_SKELETON_POSITION_HAND_LEFT]);

	// �E�r
	DrawSkeletonLine(img, joints[NUI_SKELETON_POSITION_SHOULDER_CENTER], 
	                      joints[NUI_SKELETON_POSITION_SHOULDER_RIGHT]);
	DrawSkeletonLine(img, joints[NUI_SKELETON_POSITION_SHOULDER_RIGHT],
	                      joints[NUI_SKELETON_POSITION_ELBOW_RIGHT]);
	DrawSkeletonLine(img, joints[NUI_SKELETON_POSITION_ELBOW_RIGHT],
	                      joints[NUI_SKELETON_POSITION_WRIST_RIGHT]);
	DrawSkeletonLine(img, joints[NUI_SKELETON_POSITION_WRIST_RIGHT],
	                      joints[NUI_SKELETON_POSITION_HAND_RIGHT]);

	// ����
	DrawSkeletonLine(img, joints[NUI_SKELETON_POSITION_HIP_CENTER],
	                      joints[NUI_SKELETON_POSITION_HIP_LEFT]);
	DrawSkeletonLine(img, joints[NUI_SKELETON_POSITION_HIP_LEFT], 
	                      joints[NUI_SKELETON_POSITION_KNEE_LEFT]);
	DrawSkeletonLine(img, joints[NUI_SKELETON_POSITION_KNEE_LEFT], 
	                      joints[NUI_SKELETON_POSITION_ANKLE_LEFT]);
	DrawSkeletonLine(img, joints[NUI_SKELETON_POSITION_ANKLE_LEFT],
	                      joints[NUI_SKELETON_POSITION_FOOT_LEFT]);
	
	// �E��
	DrawSkeletonLine(img, joints[NUI_SKELETON_POSITION_HIP_CENTER],
	                      joints[NUI_SKELETON_POSITION_HIP_RIGHT]);
	DrawSkeletonLine(img, joints[NUI_SKELETON_POSITION_HIP_RIGHT],
	                      joints[NUI_SKELETON_POSITION_KNEE_RIGHT]);
	DrawSkeletonLine(img, joints[NUI_SKELETON_POSITION_KNEE_RIGHT], 
	                      joints[NUI_SKELETON_POSITION_ANKLE_RIGHT]);
	DrawSkeletonLine(img, joints[NUI_SKELETON_POSITION_ANKLE_RIGHT],
	                      joints[NUI_SKELETON_POSITION_FOOT_RIGHT]);

	// �֐߂�`��
	for (int i = 0; i <NUI_SKELETON_POSITION_COUNT; i++){
		cvCircle(img, joints[i], 5, cvScalar(0, 255, 0), -1);
	}

	// �E�B���h�E�ɏo��
	cvShowImage("Skeleton View", img);
}

//------------------------------------------------------------------
// �֐߂����Ԑ���`��
//------------------------------------------------------------------
void Skeleton::DrawSkeletonLine(IplImage* img, CvPoint st, CvPoint ed ) {
	cvLine(img, st, ed, cvScalar(0, 0, 255), 4);
}


